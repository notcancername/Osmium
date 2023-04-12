#include <stdio.h>
#include <stdlib.h>
#ifdef __MINGW32__
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#include "gui.h"
#include "globals.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <pthread.h>
#include <time.h>
#include <png.h>
#include <math.h>
#include "entity.h"
#include "world.h"
#include <errno.h>
#include "render.h"
#include "models.h"
#ifdef __MINGW32__
# include <winsock2.h>
#else
# include <sys/socket.h>
#endif
#include "network.h"
#include "ingame.h"
#include "block.h"
#include <unistd.h>
#include <fcntl.h>
#include "bmodel.h"
#include "xstring.h"

int fr = 30;
int rr = 0;
int b1d = 0;
float chx = 0.;
float chy = 0.;

void tick() {
	gui_tick();
	ingame_tick();
}

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	gui_keyboardCallback(key, scancode, action, mods);
}

void textCallback(GLFWwindow* window, unsigned int codepoint) {
	gui_textCallback(codepoint);
}

struct timespec ts;
double lt;
double lf;
int frames;

void displayCallback() {
	frames++;
	glfwGetFramebufferSize(window, &width, &height);
	int v5 = 1000;
	int sf = 1;
	swidth = width;
	sheight = height;
	while (sf < v5 && swidth / (sf + 1) >= 320 && sheight / (sf + 1) >= 240) {
		sf++;
	}
	swidth = (int) ceil(swidth / sf);
	sheight = (int) ceil(sheight / sf);
	csf = sf;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	double ms2 = (double) ts.tv_sec * 1000. + (double) ts.tv_nsec / 1000000.;
	while (ms2 > lt + 50.) {
		lt += 50.;
		tick();
	}
	if (ms2 > lf + 1000.) {
		double t = ms2 - lf;
		lf = ms2;
		printf("FPS: %f\n", (float) frames / (t / 1000.));
		frames = 0;
	}

	//struct timespec ts2;
	//clock_gettime(CLOCK_MONOTONIC, &ts2);
	//printf("tick-time: %f\n", ((double) ts2.tv_sec * 1000. + (double) ts2.tv_nsec / 1000000.) - ms2);
	float partialTick = ((ms2 - lt) / 50.);
	//ppitch = ourPlayer->pitch * (1. - partialTick) + ourPlayer->lpitch * partialTick;
	//pyaw = ourPlayer->yaw * (1. - partialTick) + ourPlayer->lyaw * partialTick;
	//px = ourPlayer->x * (1. - partialTick) + ourPlayer->lx * partialTick;
	//py = ourPlayer->y * (1. - partialTick) + ourPlayer->ly * partialTick;
	//pz = ourPlayer->z * (1. - partialTick) + ourPlayer->lz * partialTick;
	glEnable (GL_TEXTURE_2D);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0., swidth, sheight, 0., 1000., 3000.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0., 0., -2000.);
	//glMatrixMode (GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(-1., 1., -1., 1., 1., 20.);
	//gluPerspective((sprinting && moveForward > 0) ? 105 : 95., (double) width / (double) height, 0.01, 10.);
	//glMatrixMode (GL_MODELVIEW);
	//glLoadIdentity();
	//float v3 = cos(-pyaw * 0.017453292 - PI);
	//float v4 = sin(-pyaw * 0.017453292 - PI);
	//float v5 = -cos(-ppitch * 0.017453292);
	//float ly = sin(-ppitch * 0.017453292) + py;
	//float lx = px + v4 * v5;
	//float lz = pz + v3 * v5;
	//gluLookAt(px, py, pz, lx, ly, lz, 0., 1., 0.);
	//drawScreen(partialTick);
	//glMatrixMode (GL_PROJECTION);
	//glLoadIdentity();
	//double wp = (double) width / 600.;
	//double hp = (double) height / 600.;
	//glOrtho(-1. * wp, 1. * wp, -1. * hp, 1. * hp, -20., 20.);
	//glMatrixMode (GL_MODELVIEW);
	//glLoadIdentity();
	//glDisable (GL_DEPTH_TEST);
	drawGUI(partialTick);
	//
	size_t error = glGetError();
	if (error) {
		char* es;
		if (error == GL_INVALID_ENUM) {
			es = "GL_INVALID_ENUM";
		} else if (error == GL_INVALID_VALUE) {
			es = "GL_INVALID_VALUE";
		} else if (error == GL_INVALID_OPERATION) {
			es = "GL_INVALID_OPERATION";
#ifdef GL_INVALID_FRAMEBUFFER_OPERATION
		} else if (error == GL_INVALID_FRAMEBUFFER_OPERATION) {
			es = "GL_INVALID_FRAMEBUFFER_OPERATION";
#endif
		} else if (error == GL_STACK_OVERFLOW) {
			es = "GL_STACK_OVERFLOW";
		} else if (error == GL_STACK_UNDERFLOW) {
			es = "GL_STACK_UNDERFLOW";
		} else if (error == GL_OUT_OF_MEMORY) {
			es = "GL_OUT_OF_MEMORY";
		} else es = "UNKNOWN";
		printf("GLError: %s\n", es);
	}
	glFlush();
	mouseButton = -1;
	//clock_gettime(CLOCK_MONOTONIC, &ts2);
	//printf("render-time: %f\n", ((double) ts2.tv_sec * 1000. + (double) ts2.tv_nsec / 1000000.) - ms2);
}

void mouseMotionCallback(GLFWwindow* window, double x, double y) {
	gui_mouseMotionCallback(x, y);
	mouseX = x / (csf == 0 ? 1 : csf);
	mouseY = y / (csf == 0 ? 1 : csf);
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == 3 || button == 4) {
		//if (state == GLUT_UP) return;
		//if (button == 3) {
		//	heldItem++;
		//	if (heldItem == 9) heldItem = 0;
		//} else {
		//	heldItem--;
		//	if (heldItem == -1) heldItem = 8;
		//}
	}
	if (action == GLFW_PRESS) mouseButton = button;
}

void scrollCallback(GLFWwindow* window, double x, double y) {
	ingame_scrollCallback(x, y);
}

void error_callback(int error, const char* description) {
	printf("GLFW error: %s\n", description);
}

void cursorEnterCallback(GLFWwindow* window, int entered) {
	hasMouse = entered;
}

int main(int argc, char *argv[]) {
	int cs = 0;
	for (int i = 1; i < argc; i++) {
		if (cs == 0) {
			if (streq_nocase(argv[i], "--username")) {
				cs = 1;
			} else if (streq_nocase(argv[i], "--uuid")) {
				cs = 2;
			} else if (streq_nocase(argv[i], "--accessToken")) {
				cs = 3;
			}
		} else if (cs == 1) {
			username = argv[i];
			cs = 0;
		} else if (cs == 2) {
			uuid = argv[i];
			cs = 0;
		} else if (cs == 3) {
			accessToken = argv[i];
			cs = 0;
		}
	}
	if (username == NULL) {
		username = malloc(10);
		snprintf(username, 9, "Player%i", rand() % 1000);
	}
#ifdef __MINGW32__
	WORD versionWanted = MAKEWORD(1, 1);
	WSADATA wsaData;
	WSAStartup(versionWanted, &wsaData);
#endif
	char ncwd[strlen(argv[0]) + 1];
	memcpy(ncwd, argv[0], strlen(argv[0]) + 1);
	char* ecwd =
#ifdef __MINGW32__
			strrchr(ncwd, '\\');
#else
			strrchr(ncwd, '/');
#endif
	ecwd++;
	ecwd[0] = 0;
	chdir(ncwd);
	printf("Loading... [FROM=%s]\n", strlen(INSTALLDIR) == 0 ? ncwd : INSTALLDIR);
	width = 800;
	height = 600;
	if (!glfwInit()) return -1;
	glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
	//glfwWindowHint(GLFW_SAMPLES, 4); //TODO: use shaders and a 2D texture array so we can antialias.
	glfwSetErrorCallback(error_callback);
	window = glfwCreateWindow(800, 600, "Minecraft 1.9.4 (C Version)", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent (window);
#ifdef __MINGW32__
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(err != GLEW_OK) {
		printf("GLEW Init error: %s\n", glewGetErrorString(err));
		glfwTerminate();
		return -1;
	}
	if(!glewIsSupported("GL_VERSION_2_1") || !glewIsSupported("GL_ARB_vertex_program")) {
		printf("OpenGL version 2.1+ or GL_ARB_vertex_program not satisfied.\n");
		glfwTerminate();
		return -1;
	}
#endif
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	//glEnable (GL_MULTISAMPLE);
	//glEnable (GL_MULTISAMPLE_ARB);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_TEXTURE_2D);
	glEnable (GL_CULL_FACE);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable (GL_ALPHA_TEST);
	loadGUI();
	loadIngame();
	loadBlocks();
	load_entities();
	gbns = malloc(sizeof(struct bnamespace*) * 2);
	gbn_count = 2;
	gbns[0] = malloc(sizeof(struct bnamespace));
	gbns[0]->name = "block";
	gbns[0]->bmodels = NULL;
	gbns[0]->bmodel_count = 0;
	gbns[1] = malloc(sizeof(struct bnamespace));
	gbns[1]->name = "item";
	gbns[1]->bmodels = NULL;
	gbns[1]->bmodel_count = 0;
	readAllBmodels(INSTALLDIR "assets/minecraft/models/block/", &gbns[0]->bmodels, &gbns[0]->bmodel_count);
	//TODO: read items
	resolveBmodels(gbns, gbn_count);
	//for (int i = 0; i < gbns[0]->bmodel_count; i++)
	//	printf("%s %s %i %i\n", gbns[0]->bmodels[i]->name, gbns[0]->bmodels[i]->parent, gbns[0]->bmodels[i]->element_count, gbns[0]->bmodels[i]->texture_count);
	loadBaseModels();
	def_wrap = 32;
	blockMapLength = 410;
	blockMap = malloc(blockMapLength * sizeof(char*));
	blockMap[0] = "flower_tulip_white.png";
	blockMap[1] = "repeating_command_block_front.png";
	blockMap[2] = "coal_block.png";
	blockMap[3] = "grass_side_overlay.png";
	blockMap[4] = "sandstone_carved.png";
	blockMap[5] = "endframe_side.png";
	blockMap[6] = "vine.png";
	blockMap[7] = "glass_red.png";
	blockMap[8] = "dropper_front_horizontal.png";
	blockMap[9] = "anvil_top_damaged_2.png";
	blockMap[10] = "iron_ore.png";
	blockMap[11] = "wool_colored_cyan.png";
	blockMap[12] = "wheat_stage_7.png";
	blockMap[13] = "sapling_oak.png";
	blockMap[14] = "destroy_stage_8.png";
	blockMap[15] = "door_birch_upper.png";
	blockMap[16] = "enchanting_table_top.png";
	blockMap[17] = "purpur_pillar_top.png";
	blockMap[18] = "stone_diorite.png";
	blockMap[19] = "beetroots_stage_0.png";
	blockMap[20] = "nether_wart_stage_0.png";
	blockMap[21] = "glass_cyan.png";
	blockMap[22] = "red_sandstone_carved.png";
	blockMap[23] = "door_wood_lower.png";
	blockMap[24] = "daylight_detector_top.png";
	blockMap[25] = "repeating_command_block_back.png";
	blockMap[26] = "potatoes_stage_1.png";
	blockMap[27] = "clay.png";
	blockMap[28] = "dirt.png";
	blockMap[29] = "bed_feet_side.png";
	blockMap[30] = "hay_block_side.png";
	blockMap[31] = "hardened_clay_stained_magenta.png";
	blockMap[32] = "stonebrick_cracked.png";
	blockMap[33] = "wheat_stage_3.png";
	blockMap[34] = "destroy_stage_6.png";
	blockMap[35] = "planks_big_oak.png";
	blockMap[36] = "glass_pane_top_light_blue.png";
	blockMap[37] = "stone_andesite_smooth.png";
	blockMap[38] = "command_block_conditional.png";
	blockMap[39] = "brewing_stand_base.png";
	blockMap[40] = "double_plant_fern_bottom.png";
	blockMap[41] = "wheat_stage_1.png";
	blockMap[42] = "sapling_birch.png";
	blockMap[43] = "structure_block_save.png";
	blockMap[44] = "dirt_podzol_top.png";
	blockMap[45] = "wool_colored_silver.png";
	blockMap[46] = "dispenser_front_horizontal.png";
	blockMap[47] = "red_sandstone_bottom.png";
	blockMap[48] = "door_acacia_upper.png";
	blockMap[49] = "rail_activator_powered.png";
	blockMap[50] = "ice_packed.png";
	blockMap[51] = "carrots_stage_2.png";
	blockMap[52] = "chorus_flower_dead.png";
	blockMap[53] = "wheat_stage_2.png";
	blockMap[54] = "nether_wart_stage_2.png";
	blockMap[55] = "tnt_top.png";
	blockMap[56] = "flower_tulip_red.png";
	blockMap[57] = "dispenser_front_vertical.png";
	blockMap[58] = "planks_jungle.png";
	blockMap[59] = "double_plant_fern_top.png";
	blockMap[60] = "grass_side_snowed.png";
	blockMap[61] = "grass_side.png";
	blockMap[62] = "jukebox_top.png";
	blockMap[63] = "itemframe_background.png";
	blockMap[64] = "netherrack.png";
	blockMap[65] = "chain_command_block_front.png";
	blockMap[66] = "red_sandstone_normal.png";
	blockMap[67] = "double_plant_rose_top.png";
	blockMap[68] = "hardened_clay_stained_red.png";
	blockMap[69] = "daylight_detector_inverted_top.png";
	blockMap[70] = "double_plant_sunflower_front.png";
	blockMap[71] = "sea_lantern.png";
	blockMap[72] = "red_sandstone_top.png";
	blockMap[73] = "glass_purple.png";
	blockMap[74] = "dragon_egg.png";
	blockMap[75] = "glass_pane_top_brown.png";
	blockMap[76] = "leaves_birch.png";
	blockMap[77] = "glass_silver.png";
	blockMap[78] = "emerald_block.png";
	blockMap[79] = "end_stone.png";
	blockMap[80] = "door_iron_lower.png";
	blockMap[81] = "piston_top_sticky.png";
	blockMap[82] = "frosted_ice_1.png";
	blockMap[83] = "comparator_on.png";
	blockMap[84] = "potatoes_stage_0.png";
	blockMap[85] = "glass_pane_top_blue.png";
	blockMap[86] = "hardened_clay_stained_lime.png";
	blockMap[87] = "lava_flow.png";
	blockMap[88] = "log_big_oak.png";
	blockMap[89] = "stonebrick_carved.png";
	blockMap[90] = "glass_pane_top_cyan.png";
	blockMap[91] = "quartz_block_chiseled_top.png";
	blockMap[92] = "fern.png";
	blockMap[93] = "fire_layer_0.png";
	blockMap[94] = "glass_magenta.png";
	blockMap[95] = "bedrock.png";
	blockMap[96] = "sandstone_bottom.png";
	blockMap[97] = "quartz_block_chiseled.png";
	blockMap[98] = "trapdoor.png";
	blockMap[99] = "destroy_stage_3.png";
	blockMap[100] = "anvil_base.png";
	blockMap[101] = "iron_trapdoor.png";
	blockMap[102] = "hardened_clay_stained_purple.png";
	blockMap[103] = "wool_colored_blue.png";
	blockMap[104] = "coal_ore.png";
	blockMap[105] = "nether_wart_stage_1.png";
	blockMap[106] = "door_jungle_lower.png";
	blockMap[107] = "pumpkin_stem_disconnected.png";
	blockMap[108] = "wool_colored_purple.png";
	blockMap[109] = "sapling_roofed_oak.png";
	blockMap[110] = "log_acacia.png";
	blockMap[111] = "wool_colored_light_blue.png";
	blockMap[112] = "water_overlay.png";
	blockMap[113] = "hardened_clay.png";
	blockMap[114] = "piston_side.png";
	blockMap[115] = "bed_head_top.png";
	blockMap[116] = "wheat_stage_0.png";
	blockMap[117] = "furnace_front_off.png";
	blockMap[118] = "log_oak_top.png";
	blockMap[119] = "double_plant_grass_bottom.png";
	blockMap[120] = "comparator_off.png";
	blockMap[121] = "redstone_dust_overlay.png";
	blockMap[122] = "glass_pane_top_magenta.png";
	blockMap[123] = "beacon.png";
	blockMap[124] = "log_birch_top.png";
	blockMap[125] = "cactus_bottom.png";
	blockMap[126] = "chain_command_block_conditional.png";
	blockMap[127] = "double_plant_paeonia_top.png";
	blockMap[128] = "beetroots_stage_3.png";
	blockMap[129] = "glass_pink.png";
	blockMap[130] = "wool_colored_magenta.png";
	blockMap[131] = "flower_oxeye_daisy.png";
	blockMap[132] = "mushroom_red.png";
	blockMap[133] = "double_plant_syringa_top.png";
	blockMap[134] = "rail_normal_turned.png";
	blockMap[135] = "flower_blue_orchid.png";
	blockMap[136] = "hopper_inside.png";
	blockMap[137] = "piston_top_normal.png";
	blockMap[138] = "command_block_back.png";
	blockMap[139] = "glass_lime.png";
	blockMap[140] = "glass_yellow.png";
	blockMap[141] = "glass_pane_top_silver.png";
	blockMap[142] = "chain_command_block_back.png";
	blockMap[143] = "double_plant_sunflower_back.png";
	blockMap[144] = "rail_normal.png";
	blockMap[145] = "glowstone.png";
	blockMap[146] = "stone_granite_smooth.png";
	blockMap[147] = "torch_on.png";
	blockMap[148] = "wool_colored_lime.png";
	blockMap[149] = "command_block_side.png";
	blockMap[150] = "door_birch_lower.png";
	blockMap[151] = "glass_pane_top_white.png";
	blockMap[152] = "hardened_clay_stained_light_blue.png";
	blockMap[153] = "diamond_ore.png";
	blockMap[154] = "anvil_top_damaged_1.png";
	blockMap[155] = "repeating_command_block_conditional.png";
	blockMap[156] = "rail_detector_powered.png";
	blockMap[157] = "glass_pane_top_purple.png";
	blockMap[158] = "glass_gray.png";
	blockMap[159] = "lava_still.png";
	blockMap[160] = "glass_pane_top_lime.png";
	blockMap[161] = "log_birch.png";
	blockMap[162] = "hardened_clay_stained_blue.png";
	blockMap[163] = "cobblestone.png";
	blockMap[164] = "pumpkin_face_on.png";
	blockMap[165] = "wool_colored_brown.png";
	blockMap[166] = "mushroom_brown.png";
	blockMap[167] = "ladder.png";
	blockMap[168] = "waterlily.png";
	blockMap[169] = "destroy_stage_0.png";
	blockMap[170] = "red_sandstone_smooth.png";
	blockMap[171] = "purpur_pillar.png";
	blockMap[172] = "cake_inner.png";
	blockMap[173] = "door_spruce_upper.png";
	blockMap[174] = "cauldron_top.png";
	blockMap[175] = "door_dark_oak_upper.png";
	blockMap[176] = "bed_head_end.png";
	blockMap[177] = "gold_ore.png";
	blockMap[178] = "redstone_ore.png";
	blockMap[179] = "double_plant_rose_bottom.png";
	blockMap[180] = "leaves_spruce.png";
	blockMap[181] = "pumpkin_top.png";
	blockMap[182] = "sponge.png";
	blockMap[183] = "snow.png";
	blockMap[184] = "iron_block.png";
	blockMap[185] = "prismarine_dark.png";
	blockMap[186] = "quartz_ore.png";
	blockMap[187] = "trip_wire_source.png";
	blockMap[188] = "hardened_clay_stained_brown.png";
	blockMap[189] = "door_jungle_upper.png";
	blockMap[190] = "frosted_ice_2.png";
	blockMap[191] = "diamond_block.png";
	blockMap[192] = "glass_pane_top_gray.png";
	blockMap[193] = "bed_head_side.png";
	blockMap[194] = "log_jungle.png";
	blockMap[195] = "mushroom_block_inside.png";
	blockMap[196] = "log_jungle_top.png";
	blockMap[197] = "endframe_eye.png";
	blockMap[198] = "hardened_clay_stained_orange.png";
	blockMap[199] = "cake_side.png";
	blockMap[200] = "crafting_table_side.png";
	blockMap[201] = "redstone_dust_line0.png";
	blockMap[202] = "glass_black.png";
	blockMap[203] = "cocoa_stage_2.png";
	blockMap[204] = "grass_top.png";
	blockMap[205] = "log_oak.png";
	blockMap[206] = "glass_pane_top.png";
	blockMap[207] = "anvil_top_damaged_0.png";
	blockMap[208] = "sapling_spruce.png";
	blockMap[209] = "ice.png";
	blockMap[210] = "log_big_oak_top.png";
	blockMap[211] = "portal.png";
	blockMap[212] = "nether_brick.png";
	blockMap[213] = "door_wood_upper.png";
	blockMap[214] = "glass_light_blue.png";
	blockMap[215] = "chain_command_block_side.png";
	blockMap[216] = "door_iron_upper.png";
	blockMap[217] = "pumpkin_face_off.png";
	blockMap[218] = "sapling_jungle.png";
	blockMap[219] = "piston_inner.png";
	blockMap[220] = "brewing_stand.png";
	blockMap[221] = "bed_feet_top.png";
	blockMap[222] = "stonebrick.png";
	blockMap[223] = "debug2.png";
	blockMap[224] = "furnace_side.png";
	blockMap[225] = "hardened_clay_stained_cyan.png";
	blockMap[226] = "hardened_clay_stained_white.png";
	blockMap[227] = "noteblock.png";
	blockMap[228] = "glass_pane_top_red.png";
	blockMap[229] = "stone_slab_side.png";
	blockMap[230] = "flower_pot.png";
	blockMap[231] = "planks_acacia.png";
	blockMap[232] = "hardened_clay_stained_gray.png";
	blockMap[233] = "water_flow.png";
	blockMap[234] = "furnace_top.png";
	blockMap[235] = "quartz_block_top.png";
	blockMap[236] = "rail_activator.png";
	blockMap[237] = "farmland_dry.png";
	blockMap[238] = "stone.png";
	blockMap[239] = "sponge_wet.png";
	blockMap[240] = "mushroom_block_skin_stem.png";
	blockMap[241] = "glass_pane_top_yellow.png";
	blockMap[242] = "stone_andesite.png";
	blockMap[243] = "crafting_table_front.png";
	blockMap[244] = "leaves_jungle.png";
	blockMap[245] = "cauldron_inner.png";
	blockMap[246] = "iron_bars.png";
	blockMap[247] = "glass_pane_top_pink.png";
	blockMap[248] = "wheat_stage_4.png";
	blockMap[249] = "crafting_table_top.png";
	blockMap[250] = "frosted_ice_3.png";
	blockMap[251] = "door_acacia_lower.png";
	blockMap[252] = "glass_green.png";
	blockMap[253] = "stone_granite.png";
	blockMap[254] = "prismarine_rough.png";
	blockMap[255] = "debug.png";
	blockMap[256] = "melon_top.png";
	blockMap[257] = "hardened_clay_stained_silver.png";
	blockMap[258] = "glass_pane_top_black.png";
	blockMap[259] = "frosted_ice_0.png";
	blockMap[260] = "destroy_stage_4.png";
	blockMap[261] = "repeater_on.png";
	blockMap[262] = "hay_block_top.png";
	blockMap[263] = "redstone_block.png";
	blockMap[264] = "brick.png";
	blockMap[265] = "repeater_off.png";
	blockMap[266] = "flower_tulip_pink.png";
	blockMap[267] = "door_spruce_lower.png";
	blockMap[268] = "trip_wire.png";
	blockMap[269] = "structure_block_load.png";
	blockMap[270] = "hardened_clay_stained_green.png";
	blockMap[271] = "quartz_block_side.png";
	blockMap[272] = "potatoes_stage_2.png";
	blockMap[273] = "hardened_clay_stained_pink.png";
	blockMap[274] = "destroy_stage_9.png";
	blockMap[275] = "melon_stem_disconnected.png";
	blockMap[276] = "stone_slab_top.png";
	blockMap[277] = "bookshelf.png";
	blockMap[278] = "cake_bottom.png";
	blockMap[279] = "chorus_plant.png";
	blockMap[280] = "grass_path_top.png";
	blockMap[281] = "glass_pane_top_green.png";
	blockMap[282] = "cauldron_side.png";
	blockMap[283] = "gold_block.png";
	blockMap[284] = "glass_brown.png";
	blockMap[285] = "redstone_lamp_on.png";
	blockMap[286] = "glass.png";
	blockMap[287] = "double_plant_sunflower_bottom.png";
	blockMap[288] = "cake_top.png";
	blockMap[289] = "tnt_bottom.png";
	blockMap[290] = "wheat_stage_5.png";
	blockMap[291] = "quartz_block_lines_top.png";
	blockMap[292] = "fire_layer_1.png";
	blockMap[293] = "wool_colored_black.png";
	blockMap[294] = "destroy_stage_2.png";
	blockMap[295] = "lever.png";
	blockMap[296] = "destroy_stage_7.png";
	blockMap[297] = "leaves_big_oak.png";
	blockMap[298] = "wool_colored_green.png";
	blockMap[299] = "mycelium_side.png";
	blockMap[300] = "leaves_oak.png";
	blockMap[301] = "melon_stem_connected.png";
	blockMap[302] = "daylight_detector_side.png";
	blockMap[303] = "quartz_block_lines.png";
	blockMap[304] = "double_plant_syringa_bottom.png";
	blockMap[305] = "emerald_ore.png";
	blockMap[306] = "flower_allium.png";
	blockMap[307] = "double_plant_sunflower_top.png";
	blockMap[308] = "rail_golden.png";
	blockMap[309] = "sandstone_smooth.png";
	blockMap[310] = "sapling_acacia.png";
	blockMap[311] = "redstone_torch_on.png";
	blockMap[312] = "beetroots_stage_1.png";
	blockMap[313] = "hopper_top.png";
	blockMap[314] = "stone_diorite_smooth.png";
	blockMap[315] = "destroy_stage_5.png";
	blockMap[316] = "structure_block_data.png";
	blockMap[317] = "command_block_front.png";
	blockMap[318] = "mushroom_block_skin_brown.png";
	blockMap[319] = "reeds.png";
	blockMap[320] = "gravel.png";
	blockMap[321] = "sand.png";
	blockMap[322] = "end_rod.png";
	blockMap[323] = "carrots_stage_3.png";
	blockMap[324] = "glass_orange.png";
	blockMap[325] = "sandstone_top.png";
	blockMap[326] = "leaves_acacia.png";
	blockMap[327] = "repeating_command_block_side.png";
	blockMap[328] = "red_sand.png";
	blockMap[329] = "enchanting_table_bottom.png";
	blockMap[330] = "mycelium_top.png";
	blockMap[331] = "prismarine_bricks.png";
	blockMap[332] = "structure_block.png";
	blockMap[333] = "purpur_block.png";
	blockMap[334] = "cocoa_stage_1.png";
	blockMap[335] = "pumpkin_side.png";
	blockMap[336] = "quartz_block_bottom.png";
	blockMap[337] = "flower_dandelion.png";
	blockMap[338] = "stonebrick_mossy.png";
	blockMap[339] = "wool_colored_yellow.png";
	blockMap[340] = "potatoes_stage_3.png";
	blockMap[341] = "redstone_dust_dot.png";
	blockMap[342] = "carrots_stage_0.png";
	blockMap[343] = "cocoa_stage_0.png";
	blockMap[344] = "redstone_lamp_off.png";
	blockMap[345] = "log_acacia_top.png";
	blockMap[346] = "wool_colored_pink.png";
	blockMap[347] = "cactus_top.png";
	blockMap[348] = "hardened_clay_stained_yellow.png";
	blockMap[349] = "log_spruce_top.png";
	blockMap[350] = "glass_white.png";
	blockMap[351] = "rail_detector.png";
	blockMap[352] = "wool_colored_red.png";
	blockMap[353] = "glass_pane_top_orange.png";
	blockMap[354] = "dropper_front_vertical.png";
	blockMap[355] = "coarse_dirt.png";
	blockMap[356] = "cactus_side.png";
	blockMap[357] = "redstone_torch_off.png";
	blockMap[358] = "lapis_ore.png";
	blockMap[359] = "farmland_wet.png";
	blockMap[360] = "web.png";
	blockMap[361] = "slime.png";
	blockMap[362] = "log_spruce.png";
	blockMap[363] = "hopper_outside.png";
	blockMap[364] = "hardened_clay_stained_black.png";
	blockMap[365] = "lapis_block.png";
	blockMap[366] = "piston_bottom.png";
	blockMap[367] = "jukebox_side.png";
	blockMap[368] = "beetroots_stage_2.png";
	blockMap[369] = "wool_colored_white.png";
	blockMap[370] = "redstone_dust_line1.png";
	blockMap[371] = "deadbush.png";
	blockMap[372] = "flower_paeonia.png";
	blockMap[373] = "rail_golden_powered.png";
	blockMap[374] = "structure_block_corner.png";
	blockMap[375] = "pumpkin_stem_connected.png";
	blockMap[376] = "double_plant_paeonia_bottom.png";
	blockMap[377] = "mob_spawner.png";
	blockMap[378] = "end_bricks.png";
	blockMap[379] = "planks_spruce.png";
	blockMap[380] = "cobblestone_mossy.png";
	blockMap[381] = "mushroom_block_skin_red.png";
	blockMap[382] = "wool_colored_orange.png";
	blockMap[383] = "dirt_podzol_side.png";
	blockMap[384] = "flower_houstonia.png";
	blockMap[385] = "grass_path_side.png";
	blockMap[386] = "planks_birch.png";
	blockMap[387] = "destroy_stage_1.png";
	blockMap[388] = "double_plant_grass_top.png";
	blockMap[389] = "planks_oak.png";
	blockMap[390] = "wool_colored_gray.png";
	blockMap[391] = "water_still.png";
	blockMap[392] = "soul_sand.png";
	blockMap[393] = "flower_rose.png";
	blockMap[394] = "bed_feet_end.png";
	blockMap[395] = "sandstone_normal.png";
	blockMap[396] = "cauldron_bottom.png";
	blockMap[397] = "obsidian.png";
	blockMap[398] = "enchanting_table_side.png";
	blockMap[399] = "chorus_flower.png";
	blockMap[400] = "tallgrass.png";
	blockMap[401] = "melon_side.png";
	blockMap[402] = "endframe_top.png";
	blockMap[403] = "flower_tulip_orange.png";
	blockMap[404] = "wheat_stage_6.png";
	blockMap[405] = "tnt_side.png";
	blockMap[406] = "furnace_front_on.png";
	blockMap[407] = "carrots_stage_1.png";
	blockMap[408] = "door_dark_oak_lower.png";
	blockMap[409] = "glass_blue.png";
	blockSizeMap = malloc(blockMapLength * sizeof(int));
	//&def_width, &def_height
	loadTexturesPNG2(INSTALLDIR "assets/minecraft/textures/blocks/", def_wrap, TX_DEFAULT, 1, blockMap, 410, blockSizeMap);
	clock_gettime(CLOCK_MONOTONIC, &ts);
	lt = (double) ts.tv_sec * 1000. + (double) ts.tv_nsec / 1000000.;
	lf = lt;
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetCursorEnterCallback(window, cursorEnterCallback);
	glfwSetCharCallback(window, textCallback);
	glfwSetCursorPosCallback(window, mouseMotionCallback);
	glfwSetMouseButtonCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);
	printf("Loaded.\n");
	while (!glfwWindowShouldClose(window)) {
		displayCallback();
		glfwSwapBuffers(window);
		glfwSwapInterval(1);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
//glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);

//glutKeyboardFunc(keyboardCallback);
//glutKeyboardUpFunc(keyboardUpCallback);
//glutSpecialFunc(keyboardSpecCallback);
//glutDisplayFunc(displayCallback);
//glutMotionFunc(mouseMotionCallback);
//glutMouseFunc(mouseCallback);
//glutPassiveMotionFunc(mouseMotionCallback);
//glutSetKeyRepeat (GLUT_KEY_REPEAT_OFF);
}
