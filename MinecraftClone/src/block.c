/*
 * block.c
 *
 *  Created on: Mar 12, 2016
 *      Author: root
 */

#include "world.h"
#include "render.h"
#include <GL/gl.h>
#include "block.h"
#include "globals.h"
#include "xstring.h"
#include "models.h"

void getTextureCoordinates(const char* name, float* tx1, float* ty1, float* tx2, float* ty2) {
	float tw = 1. / (float) def_wrap;
	float th = 1. / ((float) def_height / ((float) def_width / (float) def_wrap));
	float tx = 2.;
	float ty = 1.;
	for (int tci = 0; tci < blockMapLength; tci++) {
		char* tc = blockMap[tci];
		if (streq_nocase(tc, name)) {
			tx = blockSizeMap[tci] % def_wrap;
			ty = blockSizeMap[tci] / def_wrap;
			break;
		}
	}
	*tx1 = tw * tx + (float) TEXTURE_BUFFER / (float) def_width;
	*ty1 = th * ty + (float) TEXTURE_BUFFER / (float) def_height;
	*tx2 = tw * (tx + 1) - (float) TEXTURE_BUFFER / (float) def_width;
	*ty2 = th * (ty + 1) - (float) TEXTURE_BUFFER / (float) def_height;
}

void drawBlock(struct vertex_tex** vex, size_t* vexs, block block, unsigned char faceMask, float x, float y, float z) {
	unsigned char fc = 0;
	if (faceMask & 0x01) fc++;
	if (faceMask & 0x02) fc++;
	if (faceMask & 0x04) fc++;
	if (faceMask & 0x08) fc++;
	if (faceMask & 0x10) fc++;
	if (faceMask & 0x20) fc++;
	if (block == BLK_SAPLINGOAK) {

	} else if (block == BLK_SAPLINGSPRUCE) {

	} else if (block == BLK_SAPLINGBIRCH) {

	} else if (block == BLK_SAPLINGJUNGLE) {

	} else if (block == BLK_SAPLINGACACIA) {

	} else if (block == BLK_SAPLINGDARKOAK) {

	} else if (block == BLK_WATER) {

	} else if (block == BLK_WATERNOSPREAD) {

	} else if (block == BLK_LAVA) {

	} else if (block == BLK_LAVANOSPREAD) {

	} else if (block == BLK_RAILPOWERED) {

	} else if (block == BLK_STICKYPISTON) {

	} else if (block == BLK_COBWEB) {

	} else if (block == BLK_TALLGRASSDEADSHRUB) {

	} else if (block == BLK_TALLGRASSFERN) {

	} else if (block == BLK_DEADSHRUB) {

	} else if (block == BLK_PISTON) {

	} else if (block == BLK_PISTONHEAD) {

	} else if (block == BLK_PISTONMOVING) {

	} else if (block == BLK_DANDELION) {

	} else if (block == BLK_POPPY) {

	} else if (block == BLK_BLUEORCHID) {

	} else if (block == BLK_ALLIUM) {

	} else if (block == BLK_AZUREBLUET) {

	} else if (block == BLK_REDTULIP) {

	} else if (block == BLK_ORANGETULIP) {

	} else if (block == BLK_WHITETULIP) {

	} else if (block == BLK_PINKTULIP) {

	} else if (block == BLK_OXEYEDAISY) {

	} else if (block == BLK_STONESLAB) {

	} else if (block == BLK_SANDSTONESLAB) {

	} else if (block == BLK_WOODENSLAB) {

	} else if (block == BLK_COBBLESTONESLAB) {

	} else if (block == BLK_BRICKSLAB) {

	} else if (block == BLK_STONEBRICKSLAB) {

	} else if (block == BLK_NETHERBRICKSLAB) {

	} else if (block == BLK_QUARTZSLAB) {

	} else if (block == BLK_TORCH) {

	} else if (block == BLK_FIRE) {

	} else if (block == BLK_WOODENSTAIRSOAK) {

	} else if (block == BLK_CHEST) {

	} else if (block == BLK_REDSTONEWIRE) {

	} else if (block == BLK_WHEATCROP) {

	} else if (block >> 4 == BLK_FARMLAND >> 4) {
		if (*vex == NULL) {
			*vex = malloc(6 * 4 * sizeof(struct vertex_tex));
			*vexs = 0;
		} else {
			*vex = realloc(*vex, ((6 * 4) + *vexs) * sizeof(struct vertex_tex));
		}
		int meta = block & 0x0f;
		float dof = (1. / 16.);
		float tx1[6];
		float tx2[6];
		float ty1[6];
		float ty2[6];
		getTextureCoordinates("dirt.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
		tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
		ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
		tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
		ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1] - (dof / (float) def_wrap);
		getTextureCoordinates(meta ? "farmland_wet.png" : "farmland_dry.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
		createMultSub(0.5, (dof * 15.) / 2., 0.5, &((*vex)[*vexs]), x + 0.5, y + 0.5 - (dof / 2.), z + 0.5, 0xFF, tx1, ty1, tx2, ty2);
		*vexs += 6 * 4;
	} else if (block == BLK_SIGNBLOCK) {

	} else if (block == BLK_WOODDOORBLOCK) {

	} else if (block == BLK_RAIL) {

	} else if (block == BLK_COBBLESTONESTAIRS) {

	} else if (block == BLK_SIGNWALLBLOCK) {

	} else if (block == BLK_STONEPRESSUREPLATE) {

	} else if (block == BLK_IRONDOORBLOCK) {

	} else if (block == BLK_WOODENPRESSUREPLATE) {

	} else if (block == BLK_REDSTONETORCH) {

	} else if (block == BLK_BUTTONSTONE) {

	} else if (block == BLK_CACTUS) {

	} else if (block == BLK_SUGARCANEBLOCK) {

	} else if (block == BLK_FENCEOAK) {

	} else if (block == BLK_PUMPKIN) {

	} else if (block == BLK_JACK_O_LANTERN) {

	} else if (block == BLK_CAKEBLOCK) {

	} else if (block == BLK_REDSTONEREPEATERBLOCKOFF) {

	} else if (block == BLK_REDSTONEREPEATERBLOCKON) {

	} else if (block == BLK_BROWNMUSHROOM) {

	} else if (block == BLK_REDMUSHROOM) {

	} else if (block == BLK_GLASSPANE) {

	} else if (block == BLK_PUMPKINVINE) {

	} else if (block == BLK_MELONVINE) {

	} else if (block == BLK_VINES) {

	} else if (block == BLK_FENCEGATEOAK) {

	} else if (block == BLK_BRICKSTAIRS) {

	} else if (block == BLK_STONEBRICKSTAIRS) {

	} else if (block == BLK_LILYPAD) {

	} else if (block == BLK_NETHERBRICKFENCE) {

	} else if (block == BLK_NETHERBRICKSTAIRS) {

	} else if (block == BLK_NETHERWART) {

	} else if (block == BLK_ENCHANTMENTTABLE) {

	} else if (block == BLK_BREWINGSTANDBLOCK) {

	} else if (block == BLK_CAULDRONBLOCK) {

	} else if (block == BLK_ENDPORTAL) {

	} else if (block == BLK_ENDPORTALFRAME) {

	} else if (block == BLK_OAK_WOODSLAB) {

	} else if (block == BLK_SPRUCE_WOODSLAB) {

	} else if (block == BLK_BIRCH_WOODSLAB) {

	} else if (block == BLK_JUNGLE_WOODSLAB) {

	} else if (block == BLK_ACACIAWOODSLAB) {

	} else if (block == BLK_DARKOAKWOODSLAB) {

	} else if (block == BLK_COCOAPLANT) {

	} else if (block == BLK_SANDSTONESTAIRS) {

	} else if (block == BLK_ENDERCHEST) {

	} else if (block == BLK_TRIPWIREHOOK) {

	} else if (block == BLK_WOODENSTAIRSSPRUCE) {

	} else if (block == BLK_WOODENSTAIRSBIRCH) {

	} else if (block == BLK_WOODENSTAIRSJUNGLE) {

	} else if (block == BLK_COBBLESTONEWALL) {

	} else if (block == BLK_MOSSYCOBBLESTONEWALL) {

	} else if (block == BLK_FLOWERPOTBLOCK) {

	} else if (block == BLK_CARROTCROP) {

	} else if (block == BLK_POTATOESCROP) {

	} else if (block == BLK_BUTTONWOOD) {

	} else if (block == BLK_HEADBLOCKSKELETON) {

	} else if (block == BLK_HEADBLOCKWITHER) {

	} else if (block == BLK_HEADBLOCKZOMBIE) {

	} else if (block == BLK_HEADBLOCKSTEVE) {

	} else if (block == BLK_HEADBLOCKCREEPER) {

	} else if (block == BLK_ANVIL) {

	} else if (block == BLK_ANVILSLIGHTLYDAMAGED) {

	} else if (block == BLK_ANVILVERYDAMAGED) {

	} else if (block == BLK_TRAPPEDCHEST) {

	} else if (block == BLK_WEIGHTEDPRESSUREPLATELIGHT) {

	} else if (block == BLK_WEIGHTEDPRESSUREPLATEHEAVY) {

	} else if (block == BLK_REDSTONECOMPARATOROFF) {

	} else if (block == BLK_REDSTONECOMPARATORON) {

	} else if (block == BLK_DAYLIGHTSENSOR) {

	} else if (block == BLK_HOPPER) {

	} else if (block == BLK_QUARTZSTAIRS) {

	} else if (block == BLK_STAINEDGLASSPANEWHITE) {

	} else if (block == BLK_STAINEDGLASSPANEORANGE) {

	} else if (block == BLK_STAINEDGLASSPANEMAGENTA) {

	} else if (block == BLK_STAINEDGLASSPANELIGHTBLUE) {

	} else if (block == BLK_STAINEDGLASSPANEYELLOW) {

	} else if (block == BLK_STAINEDGLASSPANELIME) {

	} else if (block == BLK_STAINEDGLASSPANEPINK) {

	} else if (block == BLK_STAINEDGLASSPANEGRAY) {

	} else if (block == BLK_STAINEDGLASSPANELIGHTGRAY) {

	} else if (block == BLK_STAINEDGLASSPANECYAN) {

	} else if (block == BLK_STAINEDGLASSPANEPURPLE) {

	} else if (block == BLK_STAINEDGLASSPANEBLUE) {

	} else if (block == BLK_STAINEDGLASSPANEBROWN) {

	} else if (block == BLK_STAINEDGLASSPANEGREEN) {

	} else if (block == BLK_STAINEDGLASSPANERED) {

	} else if (block == BLK_STAINEDGLASSPANEBLACK) {

	} else if (block == BLK_CARPETWHITE) {

	} else if (block == BLK_CARPETORANGE) {

	} else if (block == BLK_CARPETMAGENTA) {

	} else if (block == BLK_CARPETLIGHTBLUE) {

	} else if (block == BLK_CARPETYELLOW) {

	} else if (block == BLK_CARPETLIME) {

	} else if (block == BLK_CARPETPINK) {

	} else if (block == BLK_CARPETGREY) {

	} else if (block == BLK_CARPETLIGHTGRAY) {

	} else if (block == BLK_CARPETCYAN) {

	} else if (block == BLK_CARPETPURPLE) {

	} else if (block == BLK_CARPETBLUE) {

	} else if (block == BLK_CARPETBROWN) {

	} else if (block == BLK_CARPETGREEN) {

	} else if (block == BLK_CARPETRED) {

	} else if (block == BLK_CARPETBLACK) {

	} else if (block == BLK_SUNFLOWER) {

	} else if (block == BLK_LILAC) {

	} else if (block == BLK_DOUBLETALLGRASS) {

	} else if (block == BLK_LARGEFERN) {

	} else if (block == BLK_ROSEBUSH) {

	} else if (block == BLK_PEONY) {

	} else if (block == BLK_STANDINGBANNERBLOCK) {

	} else if (block == BLK_WALLBANNERBLOCK) {

	} else if (block == BLK_INVERTEDDAYLIGHTSENSOR) {

	} else if (block == BLK_REDSANDSTONESTAIRS) {

	} else if (block == BLK_REDSANDSTONESLAB) {

	} else if (block == BLK_FENCEGATESPRUCE) {

	} else if (block == BLK_FENCEGATEBIRCH) {

	} else if (block == BLK_FENCEGATEJUNGLE) {

	} else if (block == BLK_FENCEGATEDARKOAK) {

	} else if (block == BLK_FENCEGATEACACIA) {

	} else if (block == BLK_FENCESPRUCE) {

	} else if (block == BLK_FENCEBIRCH) {

	} else if (block == BLK_FENCEJUNGLE) {

	} else if (block == BLK_FENCEDARKOAK) {

	} else if (block == BLK_FENCEACACIA) {

	} else if (block == BLK_WOODENDOORBLOCKSPRUCE) {

	} else if (block == BLK_WOODENDOORBLOCKBIRCH) {

	} else if (block == BLK_WOODENDOORBLOCKJUNGLE) {

	} else if (block == BLK_WOODENDOORBLOCKACACIA) {

	} else if (block == BLK_WOODENDOORBLOCKDARKOAK) {

	} else if (block == BLK_PURPURSTAIRS) {

	} else if (block == BLK_PURPURSLAB) {

	} else if (block == BLK_ENDSTONEBRICKS) {

	} else if (block == BLK_GRASSPATH) {

	} else if (block == BLK_ENDGATEWAY) {

	} else if (block == BLK_RAILDETECTOR) {

	} else if (block == BLK_TALLGRASS) {

	} else if (block == BLK_BOOKSHELF) {

	} else if (block == BLK_LADDER) {

	} else if (block == BLK_LEVER) {

	} else if (block == BLK_REDSTONETORCHOFF) {

	} else if (block == BLK_SNOW) {

	} else if (block == BLK_PORTAL) {

	} else if (block == BLK_TRAPDOOR) {

	} else if (block == BLK_IRONBARS) {

	} else if (block == BLK_DRAGONEGG) {

	} else if (block == BLK_TRIPWIRE) {

	} else if (block == BLK_BEACON) {

	} else if (block == BLK_RAILACTIVATOR) {

	} else if (block == BLK_IRONTRAPDOOR) {

	} else if (block == BLK_ENDROD) {

	} else if (block == BLK_CHORUSPLANT) {

	} else if (block == BLK_CHORUSFLOWER) {

	} else if (block == BLK_STRUCTUREBLOCK) {

	} else if (block == BLK_BEDBLOCK) {

	} else if (block == BLK_WOODENSTAIRSACACIA) {

	} else if (block == BLK_WOODENSTAIRSDARKOAK) {

	} else {
		char* tn = NULL;
		if (block == BLK_AIR) {

		} else if (block == BLK_STONE) {
			tn = "stone.png";
		} else if (block == BLK_GRANITE) {
			tn = "stone_granite.png";
		} else if (block == BLK_POLISHEDGRANITE) {
			tn = "stone_granite_polished.png";
		} else if (block == BLK_DIORITE) {
			tn = "stone_diorite.png";
		} else if (block == BLK_POLISHEDDIORITE) {
			tn = "stone_diorite_polished.png";
		} else if (block == BLK_ANDESITE) {
			tn = "stone_andesite.png";
		} else if (block == BLK_POLISHEDANDESITE) {
			tn = "stone_andesite_polished.png";
		} else if (block == BLK_DIRT) {
			tn = "dirt.png";
		} else if (block == BLK_COARSEDIRT) {
			tn = "coarse_dirt.png";
		} else if (block == BLK_COBBLESTONE || block == BLK_COBBLESTONESLABDOUBLE) {
			tn = "cobblestone.png";
		} else if (block == BLK_WOODENPLANKOAK || block == BLK_WOODENSLABDOUBLE || block == BLK_OAK_WOODSLABDOUBLE) {
			tn = "planks_oak.png";
		} else if (block == BLK_WOODENPLANKSPRUCE || block == BLK_SPRUCE_WOODSLABDOUBLE) {
			tn = "planks_spruce.png";
		} else if (block == BLK_WOODENPLANKBIRCH || block == BLK_BIRCH_WOODSLABDOUBLE) {
			tn = "planks_birch.png";
		} else if (block == BLK_WOODENPLANKJUNGLE || block == BLK_JUNGLE_WOODSLABDOUBLE) {
			tn = "planks_jungle.png";
		} else if (block == BLK_WOODENPLANKACACIA || block == BLK_ACACIAWOODSLABDOUBLE) {
			tn = "planks_acacia.png";
		} else if (block == BLK_WOODENPLANKDARKOAK || block == BLK_DARKOAKWOODSLABDOUBLE) {
			tn = "planks_big_oak.png";
		} else if (block == BLK_BEDROCK) {
			tn = "bedrock.png";
		} else if (block == BLK_SAND) {
			tn = "sand.png";
		} else if (block == BLK_REDSAND) {
			tn = "red_sand.png";
		} else if (block == BLK_GRAVEL) {
			tn = "gravel.png";
		} else if (block == BLK_GOLDORE) {
			tn = "gold_ore.png";
		} else if (block == BLK_IRONORE) {
			tn = "iron_ore.png";
		} else if (block == BLK_COALORE) {
			tn = "coal_ore.png";
		} else if (block >> 4 == BLK_LEAVESOAK >> 4) {
			int meta = block & 0x0f;
			meta &= 0x03;
			if (meta == 0) tn = "leaves_oak.png";
			else if (meta == 1) tn = "leaves_spruce.png";
			else if (meta == 2) tn = "leaves_birch.png";
			else if (meta == 3) tn = "leaves_jungle.png";
		} else if (block == BLK_SPONGE) {
			tn = "sponge.png";
		} else if (block == BLK_WETSPONGE) {
			tn = "sponge_wet.png";
		} else if (block == BLK_GLASS) {
			tn = "glass.png";
		} else if (block == BLK_NOTEBLOCK) {
			tn = "noteblock.png";
		} else if (block == BLK_BRICK || block == BLK_BRICKSLABDOUBLE) {
			tn = "brick.png";
		} else if (block == BLK_OBSIDIAN) {
			tn = "obsidian.png";
		} else if (block == BLK_MOBSPAWNER) {
			tn = "mob_spawner.png";
		} else if (block == BLK_DIAMONDORE) {
			tn = "diamond_ore.png";
		} else if (block == BLK_REDSTONEORE) { //TODO: activated
			tn = "redstone_ore.png";
		} else if (block == BLK_ICE) {
			tn = "ice.png";
		} else if (block == BLK_NETHERRACK) {
			tn = "netherrack.png";
		} else if (block == BLK_SOULSAND) {
			tn = "netherrack.png";
		} else if (block == BLK_GLOWSTONE) {
			tn = "soul_sand.png";
		} else if (block == BLK_NETHERBRICK || block == BLK_NETHERBRICKSLABDOUBLE) {
			tn = "nether_brick.png";
		} else if (block == BLK_ENDSTONE) {
			tn = "end_stone.png";
		} else if (block == BLK_REDSTONELAMP) {
			tn = "redstone_lamp_off.png";
		} else if (block == BLK_REDSTONELAMPON) {
			tn = "redstone_lamp_on.png";
		} else if (block == BLK_EMERALDORE) {
			tn = "emerald_ore.png";
		} else if (block == BLK_PRISMARINEBRICKS) {
			tn = "prismarine_bricks.png";
		} else if (block == BLK_SEALANTERN) {
			tn = "sea_lantern.png";
		} else if (block == BLK_HARDENEDCLAY) {
			tn = "hardened_clay.png";
		} else if (block == BLK_HARDENEDCLAY_ORANGE) {
			tn = "hardened_clay_stained_orange.png";
		} else if (block == BLK_HARDENEDCLAY_MAGENTA) {
			tn = "hardened_clay_stained_magenta.png";
		} else if (block == BLK_HARDENEDCLAY_LIGHTBLUE) {
			tn = "hardened_clay_stained_light_blue.png";
		} else if (block == BLK_HARDENEDCLAY_YELLOW) {
			tn = "hardened_clay_stained_yellow.png";
		} else if (block == BLK_HARDENEDCLAY_LIME) {
			tn = "hardened_clay_stained_lime.png";
		} else if (block == BLK_HARDENEDCLAY_PINK) {
			tn = "hardened_clay_stained_pink.png";
		} else if (block == BLK_HARDENEDCLAY_GRAY) {
			tn = "hardened_clay_stained_gray.png";
		} else if (block == BLK_HARDENEDCLAY_LIGHTGRAY) {
			tn = "hardened_clay_stained_silver.png";
		} else if (block == BLK_HARDENEDCLAY_CYAN) {
			tn = "hardened_clay_stained_cyan.png";
		} else if (block == BLK_HARDENEDCLAY_PURPLE) {
			tn = "hardened_clay_stained_purple.png";
		} else if (block == BLK_HARDENEDCLAY_BLUE) {
			tn = "hardened_clay_stained_blue.png";
		} else if (block == BLK_HARDENEDCLAY_BROWN) {
			tn = "hardened_clay_stained_brown.png";
		} else if (block == BLK_HARDENEDCLAY_GREEN) {
			tn = "hardened_clay_stained_green.png";
		} else if (block == BLK_HARDENEDCLAY_RED) {
			tn = "hardened_clay_stained_red.png";
		} else if (block == BLK_HARDENEDCLAY_BLACK) {
			tn = "hardened_clay_stained_black.png";
		} else if (block == BLK_PURPURBLOCK) {
			tn = "purpur_block.png";
		} else if (block == BLK_LAPISLAZULIORE) {
			tn = "lapis_block.png";
		} else if (block == BLK_LAPISLAZULIBLOCK) {
			tn = "lapis_ore.png";
		} else if (block == BLK_WOOL) {
			tn = "wool_colored_white.png";
		} else if (block == BLK_ORANGEWOOL) {
			tn = "wool_colored_orange.png";
		} else if (block == BLK_MAGENTAWOOL) {
			tn = "wool_colored_magenta.png";
		} else if (block == BLK_LIGHTBLUEWOOL) {
			tn = "wool_colored_light_blue.png";
		} else if (block == BLK_YELLOWWOOL) {
			tn = "wool_colored_yellow.png";
		} else if (block == BLK_LIMEWOOL) {
			tn = "wool_colored_lime.png";
		} else if (block == BLK_PINKWOOL) {
			tn = "wool_colored_pink.png";
		} else if (block == BLK_GRAYWOOL) {
			tn = "wool_colored_gray.png";
		} else if (block == BLK_LIGHTGRAYWOOL) {
			tn = "wool_colored_silber.png";
		} else if (block == BLK_CYANWOOL) {
			tn = "wool_colored_cyan.png";
		} else if (block == BLK_PURPLEWOOL) {
			tn = "wool_colored_purple.png";
		} else if (block == BLK_BLUEWOOL) {
			tn = "wool_colored_blue.png";
		} else if (block == BLK_BROWNWOOL) {
			tn = "wool_colored_brown.png";
		} else if (block == BLK_GREENWOOL) {
			tn = "wool_colored_green.png";
		} else if (block == BLK_REDWOOL) {
			tn = "wool_colored_red.png";
		} else if (block == BLK_BLACKWOOL) {
			tn = "wool_colored_black.png";
		} else if (block == BLK_BLOCKOFGOLD) {
			tn = "gold_block.png";
		} else if (block == BLK_BLOCKOFIRON) {
			tn = "iron_block.png";
		} else if (block == BLK_MOSSSTONE) {
			tn = "cobblestone_mossy.png";
		} else if (block == BLK_BLOCKOFDIAMOND) {
			tn = "diamond_block.png";
		} else if (block == BLK_REDSTONEOREGLOWING) {
			tn = "redstone_ore.png"; // TODO glow effect?
		} else if (block == BLK_SNOWBLOCK) {
			tn = "snow.png";
		} else if (block == BLK_CLAYBLOCK) {
			tn = "clay.png";
		} else if (block == BLK_STAINEDGLASSWHITE) {
			tn = "glass.png";
		} else if (block == BLK_STAINEDGLASSORANGE) {
			tn = "glass_orange.png";
		} else if (block == BLK_STAINEDGLASSMAGENTA) {
			tn = "glass_magenta.png";
		} else if (block == BLK_STAINEDGLASSLIGHTBLUE) {
			tn = "glass_light_blue.png";
		} else if (block == BLK_STAINEDGLASSYELLOW) {
			tn = "glass_yellow.png";
		} else if (block == BLK_STAINEDGLASSLIME) {
			tn = "glass_lime.png";
		} else if (block == BLK_STAINEDGLASSPINK) {
			tn = "glass_pink.png";
		} else if (block == BLK_STAINEDGLASSGRAY) {
			tn = "glass_gray.png";
		} else if (block == BLK_STAINEDGLASSLIGHTGREY) {
			tn = "glass_silver.png";
		} else if (block == BLK_STAINEDGLASSCYAN) {
			tn = "glass_cyan.png";
		} else if (block == BLK_STAINEDGLASSPURPLE) {
			tn = "glass_purple.png";
		} else if (block == BLK_STAINEDGLASSBLUE) {
			tn = "glass_blue.png";
		} else if (block == BLK_STAINEDGLASSBROWN) {
			tn = "glass_brown.png";
		} else if (block == BLK_STAINEDGLASSGREEN) {
			tn = "glass_green.png";
		} else if (block == BLK_STAINEDGLASSRED) {
			tn = "glass_red.png";
		} else if (block == BLK_STAINEDGLASSBLACK) {
			tn = "glass_black.png";
		} else if (block == BLK_MONSTEREGGSTONE) {
			tn = "stone.png";
		} else if (block == BLK_MONSTEREGGCOBBLESTONE) {
			tn = "cobblestone.png";
		} else if (block == BLK_MONSTEREGGSTONEBRICK) {
			tn = "stonebrick.png";
		} else if (block == BLK_MONSTEREGGMOSSYSTONEBRICK) {
			tn = "stonebrick_mossy.png";
		} else if (block == BLK_MONSTEREGGCRACKEDSTONE) {
			tn = "stonebrick_cracked.png";
		} else if (block == BLK_MONSTEREGGCHISELEDSTONE) {
			tn = "stonebrick_carved.png";
		} else if (block == BLK_STONEBRICKS || block == BLK_STONEBRICKSLABDOUBLE) {
			tn = "stonebrick.png";
		} else if (block == BLK_MOSSYSTONEBRICKS) {
			tn = "stonebrick_mossy.png";
		} else if (block == BLK_CRACKEDSTONEBRICKS) {
			tn = "stonebrick_cracked.png";
		} else if (block == BLK_CHISELEDSTONEBRICK) {
			tn = "stonebrick_carved.png";
		} else if (block == BLK_BLOCKOFEMERALD) {
			tn = "emerald_block.png";
		} else if (block == BLK_BLOCKOFREDSTONE) {
			tn = "redstone_block.png";
		} else if (block == BLK_NETHERQUARTZORE) {
			tn = "quartz_ore.png";
		} else if (block == BLK_STAINEDCLAYWHITE) {
			tn = "hardened_clay_stained_white.png";
		} else if (block == BLK_STAINEDCLAYORANGE) {
			tn = "hardened_clay_stained_orange.png";
		} else if (block == BLK_STAINEDCLAYMAGENTA) {
			tn = "hardened_clay_stained_magenta.png";
		} else if (block == BLK_STAINEDCLAYLIGHTBLUE) {
			tn = "hardened_clay_stained_light_blue.png";
		} else if (block == BLK_STAINEDCLAYYELLOW) {
			tn = "hardened_clay_stained_yellow.png";
		} else if (block == BLK_STAINEDCLAYLIME) {
			tn = "hardened_clay_stained_lime.png";
		} else if (block == BLK_STAINEDCLAYPINK) {
			tn = "hardened_clay_stained_pink.png";
		} else if (block == BLK_STAINEDCLAYGRAY) {
			tn = "hardened_clay_stained_gray.png";
		} else if (block == BLK_STAINEDCLAYLIGHTGRAY) {
			tn = "hardened_clay_stained_silver.png";
		} else if (block == BLK_STAINEDCLAYCYAN) {
			tn = "hardened_clay_stained_cyan.png";
		} else if (block == BLK_STAINEDCLAYPURPLE) {
			tn = "hardened_clay_stained_purple.png";
		} else if (block == BLK_STAINEDCLAYBLUE) {
			tn = "hardened_clay_stained_blue.png";
		} else if (block == BLK_STAINEDCLAYBROWN) {
			tn = "hardened_clay_stained_brown.png";
		} else if (block == BLK_STAINEDCLAYGREEN) {
			tn = "hardened_clay_stained_green.png";
		} else if (block == BLK_STAINEDCLAYRED) {
			tn = "hardened_clay_stained_red.png";
		} else if (block == BLK_STAINEDCLAYBLACK) {
			tn = "hardened_clay_stained_black.png";
		} else if (block >> 4 == BLK_LEAVESDARKOAK >> 4) {
			int meta = block & 0x0f;
			if (meta & 0x01) {
				tn = "leaves_big_oak.png";
			} else {
				tn = "leaves_acacia.png";
			}

		} else if (block == BLK_SLIMEBLOCK) {
			tn = "slime.png";
		} else if (block == BLK_BARRIER) {
			return;
		} else if (block == BLK_PRISMARINE) {
			tn = "prismarine_rough.png"; //TODO: random textures
		} else if (block == BLK_DARKPRISMARINE) {
			tn = "prismarine_dark.png";
		} else if (block == BLK_BLOCKOFCOAL) {
			tn = "coal_block.png";
		} else if (block == BLK_PACKEDICE) {
			tn = "ice_packed.png";
		} else if (block == BLK_SMOOTHSTONESLABDOUBLE) {
			tn = "stone_slab_top.png";
		} else if (tn == NULL && block != BLK_AIR) {
			float tx1[6];
			float ty1[6];
			float tx2[6];
			float ty2[6];
			if (block == BLK_GRASS) {
				getTextureCoordinates("grass_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates("dirt.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates("grass_side.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_PODZOL) {
				getTextureCoordinates("dirt_podzol_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates("dirt.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates("dirt_podzol_side.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_MYCELIUM) {
				getTextureCoordinates("mycelium_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates("dirt.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates("mycelium_side.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block >> 4 == BLK_WOODOAK >> 4) {
				int meta = block & 0x0f;
				int bt = meta & 0x03;
				int dir = (meta & 12) >> 2;
				char* tt = NULL;
				char* st = NULL;
				if (bt == 0) { // BLK_WOODOAK
					tt = "log_oak_top.png";
					st = "log_oak.png";
				} else if (bt == 1) { // BLK_WOODSPRUCE
					tt = "log_spruce_top.png";
					st = "log_spruce.png";
				} else if (bt == 2) { // BLK_WOODBIRCH
					tt = "log_birch_top.png";
					st = "log_birch.png";
				} else if (bt == 3) { // BLK_WOODJUNGLE
					tt = "log_jungle_top.png";
					st = "log_jungle.png";
				}
				getTextureCoordinates(tt, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				tx1[1] = tx1[0];
				tx2[1] = tx2[0];
				ty1[1] = ty1[0];
				ty2[1] = ty2[0];
				if (dir == 0) {
					getTextureCoordinates(st, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2];
					ty1[3] = ty1[4] = ty1[5] = ty1[2];
					tx2[3] = tx2[4] = tx2[5] = tx2[2];
					ty2[3] = ty2[4] = ty2[5] = ty2[2];
				} else if (dir == 2) {
					tx1[2] = tx1[0];
					tx2[2] = tx2[0];
					ty1[2] = ty1[0];
					ty2[2] = ty2[0];
					tx1[3] = tx1[1];
					tx2[3] = tx2[1];
					ty1[3] = ty1[1];
					ty2[3] = ty2[1];
					getTextureCoordinates(st, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[1] = tx1[4] = tx1[5] = tx1[0];
					ty1[1] = ty1[4] = ty1[5] = ty1[0];
					tx2[1] = tx2[4] = tx2[5] = tx2[0];
					ty2[1] = ty2[4] = ty2[5] = ty2[0];
				} else if (dir == 1) {
					tx1[4] = tx1[0];
					tx2[4] = tx2[0];
					ty1[4] = ty1[0];
					ty2[4] = ty2[0];
					tx1[5] = tx1[1];
					tx2[5] = tx2[1];
					ty1[5] = ty1[1];
					ty2[5] = ty2[1];
					getTextureCoordinates(st, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[1] = tx1[3] = tx1[2] = tx1[0];
					ty1[1] = ty1[3] = ty1[2] = ty1[0];
					tx2[1] = tx2[3] = tx2[2] = tx2[0];
					ty2[1] = ty2[3] = ty2[2] = ty2[0];
				} else if (dir == 3) {
					getTextureCoordinates(st, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					tx1[1] = tx1[0] = tx1[3] = tx1[4] = tx1[5] = tx1[2];
					ty1[1] = ty1[0] = ty1[3] = ty1[4] = ty1[5] = ty1[2];
					tx2[1] = tx2[0] = tx2[3] = tx2[4] = tx2[5] = tx2[2];
					ty2[1] = ty2[0] = ty2[3] = ty2[4] = ty2[5] = ty2[2];
				}
			} else if (block >> 4 == BLK_WOODACACIAOAK >> 4) {
				int meta = block & 0x0f;
				int bt = meta & 0x03;
				int dir = (meta & 12) >> 2;
				char* tt = NULL;
				char* st = NULL;
				if (bt == 0) { // BLK_WOODOAK
					tt = "log_acacia_top.png";
					st = "log_acacia.png";
				} else if (bt == 1) { // BLK_WOODSPRUCE
					tt = "log_big_oak_top.png";
					st = "log_big_oak.png";
				}
				getTextureCoordinates(tt, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				tx1[1] = tx1[0];
				tx2[1] = tx2[0];
				ty1[1] = ty1[0];
				ty2[1] = ty2[0];
				if (dir == 0) {
					getTextureCoordinates(st, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2];
					ty1[3] = ty1[4] = ty1[5] = ty1[2];
					tx2[3] = tx2[4] = tx2[5] = tx2[2];
					ty2[3] = ty2[4] = ty2[5] = ty2[2];
				} else if (dir == 2) {
					tx1[2] = tx1[0];
					tx2[2] = tx2[0];
					ty1[2] = ty1[0];
					ty2[2] = ty2[0];
					tx1[3] = tx1[1];
					tx2[3] = tx2[1];
					ty1[3] = ty1[1];
					ty2[3] = ty2[1];
					getTextureCoordinates(st, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[1] = tx1[4] = tx1[5] = tx1[0];
					ty1[1] = ty1[4] = ty1[5] = ty1[0];
					tx2[1] = tx2[4] = tx2[5] = tx2[0];
					ty2[1] = ty2[4] = ty2[5] = ty2[0];
				} else if (dir == 1) {
					tx1[4] = tx1[0];
					tx2[4] = tx2[0];
					ty1[4] = ty1[0];
					ty2[4] = ty2[0];
					tx1[5] = tx1[1];
					tx2[5] = tx2[1];
					ty1[5] = ty1[1];
					ty2[5] = ty2[1];
					getTextureCoordinates(st, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[1] = tx1[3] = tx1[2] = tx1[0];
					ty1[1] = ty1[3] = ty1[2] = ty1[0];
					tx2[1] = tx2[3] = tx2[2] = tx2[0];
					ty2[1] = ty2[3] = ty2[2] = ty2[0];
				} else if (dir == 3) {
					getTextureCoordinates(st, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					tx1[1] = tx1[0] = tx1[3] = tx1[4] = tx1[5] = tx1[2];
					ty1[1] = ty1[0] = ty1[3] = ty1[4] = ty1[5] = ty1[2];
					tx2[1] = tx2[0] = tx2[3] = tx2[4] = tx2[5] = tx2[2];
					ty2[1] = ty2[0] = ty2[3] = ty2[4] = ty2[5] = ty2[2];
				}
			} else if (block >> 4 == BLK_DISPENSER >> 4) {
				int meta = block & 0x0f;
				int dir = meta & 0x07;
				int act = meta & 0x08;
				if (dir == 1) {
					getTextureCoordinates("dispenser_front_vertical.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					getTextureCoordinates("furnace_top.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[2] = tx1[3] = tx1[4] = tx1[5] = tx1[1];
					tx2[2] = tx2[3] = tx2[4] = tx2[5] = tx2[1];
					ty1[2] = ty1[3] = ty1[4] = ty1[5] = ty1[1];
					ty2[2] = ty2[3] = ty2[4] = ty2[5] = ty2[1];
				} else if (dir == 0) {
					getTextureCoordinates("dispenser_front_vertical.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					getTextureCoordinates("furnace_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[2] = tx1[3] = tx1[4] = tx1[5] = tx1[0];
					tx2[2] = tx2[3] = tx2[4] = tx2[5] = tx2[0];
					ty1[2] = ty1[3] = ty1[4] = ty1[5] = ty1[0];
					ty2[2] = ty2[3] = ty2[4] = ty2[5] = ty2[0];
				} else {
					getTextureCoordinates("furnace_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[1] = tx1[0];
					tx2[1] = tx2[0];
					ty1[1] = ty1[0];
					ty2[1] = ty2[0];
					getTextureCoordinates("furnace_side.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2];
					tx2[3] = tx2[4] = tx2[5] = tx2[2];
					ty1[3] = ty1[4] = ty1[5] = ty1[2];
					ty2[3] = ty2[4] = ty2[5] = ty2[2];
					if (dir == 2) getTextureCoordinates("dispenser_front_horizontal.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					else if (dir == 3) getTextureCoordinates("dispenser_front_horizontal.png", &tx1[3], &ty1[3], &tx2[3], &ty2[3]);
					else if (dir == 4) getTextureCoordinates("dispenser_front_horizontal.png", &tx1[4], &ty1[4], &tx2[4], &ty2[4]);
					else if (dir == 5) getTextureCoordinates("dispenser_front_horizontal.png", &tx1[5], &ty1[5], &tx2[5], &ty2[5]);
				}
			} else if (block == BLK_SANDSTONE || block == BLK_SANDSTONESLABDOUBLE) {
				getTextureCoordinates("sandstone_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates("sandstone_bottom.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates("sandstone_normal.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_PURPURPILLAR) {
				getTextureCoordinates("purpur_pillar_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				tx1[1] = tx1[0];
				tx2[1] = tx2[0];
				ty1[1] = ty1[0];
				ty2[1] = ty2[0];
				getTextureCoordinates("purpur_pillar.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_SANDSTONECHISELED) {
				getTextureCoordinates("sandstone_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates("sandstone_bottom.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates("sandstone_carved.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_SANDSTONESMOOTH || block == BLK_SMOOTHSANDSTONESLABDOUBLE) {
				getTextureCoordinates("sandstone_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates("sandstone_bottom.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates("sandstone_smooth.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_STONESLABDOUBLE) {
				getTextureCoordinates("stone_slab_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				tx1[1] = tx1[0];
				tx2[1] = tx2[0];
				ty1[1] = ty1[0];
				ty2[1] = ty2[0];
				getTextureCoordinates("stone_slab_side.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_TNT) {
				getTextureCoordinates("tnt_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates("tnt_bottom.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates("tnt_side.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_WORKBENCH) {
				getTextureCoordinates("crafting_table_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates("planks_oak.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates("crafting_table_front.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[2];
				ty1[3] = ty1[2];
				tx2[3] = tx2[2];
				ty2[3] = ty2[2];
				getTextureCoordinates("crafting_table_side.png", &tx1[5], &ty1[5], &tx2[5], &ty2[5]);
				tx1[4] = tx1[5];
				ty1[4] = ty1[5];
				tx2[4] = tx2[5];
				ty2[4] = ty2[5];
			} else if (block >> 4 == BLK_FURNACE >> 4) {
				int dir = (block & 0x0f) & 0x07;
				getTextureCoordinates("furnace_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				tx1[1] = tx1[0];
				tx2[1] = tx2[0];
				ty1[1] = ty1[0];
				ty2[1] = ty2[0];
				getTextureCoordinates("furnace_side.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
				if (dir == 3) getTextureCoordinates("furnace_front_off.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				else if (dir == 5) getTextureCoordinates("furnace_front_off.png", &tx1[4], &ty1[4], &tx2[4], &ty2[4]);
				else if (dir == 4) getTextureCoordinates("furnace_front_off.png", &tx1[5], &ty1[5], &tx2[5], &ty2[5]);
				else getTextureCoordinates("furnace_front_off.png", &tx1[3], &ty1[3], &tx2[3], &ty2[3]);
			} else if (block >> 4 == BLK_FURNACESMELTING >> 4) {
				int dir = (block & 0x0f) & 0x07;
				getTextureCoordinates("furnace_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				tx1[1] = tx1[0];
				tx2[1] = tx2[0];
				ty1[1] = ty1[0];
				ty2[1] = ty2[0];
				getTextureCoordinates("furnace_side.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
				if (dir == 3) getTextureCoordinates("furnace_front_on.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				else if (dir == 5) getTextureCoordinates("furnace_front_on.png", &tx1[4], &ty1[4], &tx2[4], &ty2[4]);
				else if (dir == 4) getTextureCoordinates("furnace_front_on.png", &tx1[5], &ty1[5], &tx2[5], &ty2[5]);
				else getTextureCoordinates("furnace_front_on.png", &tx1[3], &ty1[3], &tx2[3], &ty2[3]);
			} else if (block == BLK_JUKEBOX) {
				getTextureCoordinates("jukebox_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates("jukebox_side.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
				ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
				tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
				ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1];
			} else if (block >> 4 == BLK_BROWNMUSHROOMBLOCK >> 4 || block >> 4 == BLK_REDMUSHROOMBLOCK >> 4) {
				const char* txc = (block >> 4) == (BLK_BROWNMUSHROOMBLOCK >> 4) ? "mushroom_block_skin_brown.png" : "mushroom_block_skin_red.png";
				int meta = block & 0x0f;
				if (meta == 0) {
					getTextureCoordinates("mushroom_block_inside.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1] = tx1[0];
					ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1] = ty1[0];
					tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1] = tx2[0];
					ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1] = ty2[0];
				} else if (meta == 1) {
					getTextureCoordinates("mushroom_block_inside.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[4] = tx1[2] = tx1[1];
					ty1[4] = ty1[2] = ty1[1];
					tx2[4] = tx2[2] = tx2[1];
					ty2[4] = ty2[2] = ty2[1];
					getTextureCoordinates(txc, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[3] = tx1[5] = tx1[0];
					ty1[3] = ty1[5] = ty1[0];
					tx2[3] = tx2[5] = tx2[0];
					ty2[3] = ty2[5] = ty2[0];
				} else if (meta == 2) {
					getTextureCoordinates("mushroom_block_inside.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[4] = tx1[5] = tx1[2] = tx1[1];
					ty1[4] = ty1[5] = ty1[2] = ty1[1];
					tx2[4] = tx2[5] = tx2[2] = tx2[1];
					ty2[4] = ty2[5] = ty2[2] = ty2[1];
					getTextureCoordinates(txc, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[3] = tx1[0];
					ty1[3] = ty1[0];
					tx2[3] = tx2[0];
					ty2[3] = ty2[0];
				} else if (meta == 3) {
					getTextureCoordinates("mushroom_block_inside.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[5] = tx1[2] = tx1[1];
					ty1[5] = ty1[2] = ty1[1];
					tx2[5] = tx2[2] = tx2[1];
					ty2[5] = ty2[2] = ty2[1];
					getTextureCoordinates(txc, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[3] = tx1[4] = tx1[0];
					ty1[3] = ty1[4] = ty1[0];
					tx2[3] = tx2[4] = tx2[0];
					ty2[3] = ty2[4] = ty2[0];
				} else if (meta == 4) {
					getTextureCoordinates("mushroom_block_inside.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[4] = tx1[3] = tx1[2] = tx1[1];
					ty1[4] = ty1[3] = ty1[2] = ty1[1];
					tx2[4] = tx2[3] = tx2[2] = tx2[1];
					ty2[4] = ty2[3] = ty2[2] = ty2[1];
					getTextureCoordinates(txc, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[5] = tx1[0];
					ty1[5] = ty1[0];
					tx2[5] = tx2[0];
					ty2[5] = ty2[0];
				} else if (meta == 5) {
					getTextureCoordinates("mushroom_block_inside.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
					ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
					tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
					ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1];
					getTextureCoordinates(txc, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				} else if (meta == 6) {
					getTextureCoordinates("mushroom_block_inside.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[3] = tx1[5] = tx1[2] = tx1[1];
					ty1[3] = ty1[5] = ty1[2] = ty1[1];
					tx2[3] = tx2[5] = tx2[2] = tx2[1];
					ty2[3] = ty2[5] = ty2[2] = ty2[1];
					getTextureCoordinates(txc, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[4] = tx1[0];
					ty1[4] = ty1[0];
					tx2[4] = tx2[0];
					ty2[4] = ty2[0];
				} else if (meta == 7) {
					getTextureCoordinates("mushroom_block_inside.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[4] = tx1[3] = tx1[1];
					ty1[4] = ty1[3] = ty1[1];
					tx2[4] = tx2[3] = tx2[1];
					ty2[4] = ty2[3] = ty2[1];
					getTextureCoordinates(txc, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[5] = tx1[2] = tx1[0];
					ty1[5] = ty1[2] = ty1[0];
					tx2[5] = tx2[2] = tx2[0];
					ty2[5] = ty2[2] = ty2[0];
				} else if (meta == 8) {
					getTextureCoordinates("mushroom_block_inside.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[3] = tx1[5] = tx1[4] = tx1[1];
					ty1[3] = ty1[5] = ty1[4] = ty1[1];
					tx2[3] = tx2[5] = tx2[4] = tx2[1];
					ty2[3] = ty2[5] = ty2[4] = ty2[1];
					getTextureCoordinates(txc, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[2] = tx1[0];
					ty1[2] = ty1[0];
					tx2[2] = tx2[0];
					ty2[2] = ty2[0];
				} else if (meta == 9) {
					getTextureCoordinates("mushroom_block_inside.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[5] = tx1[3] = tx1[1];
					ty1[5] = ty1[3] = ty1[1];
					tx2[5] = tx2[3] = tx2[1];
					ty2[5] = ty2[3] = ty2[1];
					getTextureCoordinates(txc, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[4] = tx1[2] = tx1[0];
					ty1[4] = ty1[2] = ty1[0];
					tx2[4] = tx2[2] = tx2[0];
					ty2[4] = ty2[2] = ty2[0];
				} else if (meta == 10) {
					getTextureCoordinates("mushroom_block_inside.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[1] = tx1[0];
					tx2[1] = tx2[0];
					ty1[1] = ty1[0];
					ty2[1] = ty2[0];
					getTextureCoordinates("mushroom_block_skin_stem.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2];
					ty1[3] = ty1[4] = ty1[5] = ty1[2];
					tx2[3] = tx2[4] = tx2[5] = tx2[2];
					ty2[3] = ty2[4] = ty2[5] = ty2[2];
				} else if (meta == 14) {
					getTextureCoordinates(txc, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1] = tx1[0];
					ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1] = ty1[0];
					tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1] = tx2[0];
					ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1] = ty2[0];
				} else if (meta == 15) {
					getTextureCoordinates("mushroom_block_skin_stem.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1] = tx1[0];
					ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1] = ty1[0];
					tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1] = tx2[0];
					ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1] = ty2[0];
				}
			} else if (block == BLK_MELONBLOCK) {
				getTextureCoordinates("melon_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates("melon_side.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
				ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
				tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
				ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1];
			} else if (block == BLK_COMMANDBLOCK) {
				return; // TODO:
			} else if (block == BLK_QUARTZBLOCK || block == BLK_QUARTZSLABDOUBLE) {
				getTextureCoordinates("quartz_block_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates("quartz_block_bottom.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates("quartz_block_side.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_CHISELEDQUARTZBLOCK) {
				getTextureCoordinates("quartz_block_chiseled_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates("quartz_block_chiseled.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
				ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
				tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
				ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1];
			} else if (block == BLK_PILLARQUARTZBLOCK) {
				getTextureCoordinates("quartz_block_lines_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates("quartz_block_lines.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
				ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
				tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
				ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1];
			} else if (block == BLK_DROPPER) {
				int meta = block & 0x0f;
				int dir = meta & 0x07;
				int act = meta & 0x08;
				if (dir == 1) {
					getTextureCoordinates("dropper_front_vertical.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					getTextureCoordinates("furnace_top.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[2] = tx1[3] = tx1[4] = tx1[5] = tx1[1];
					tx2[2] = tx2[3] = tx2[4] = tx2[5] = tx2[1];
					ty1[2] = ty1[3] = ty1[4] = ty1[5] = ty1[1];
					ty2[2] = ty2[3] = ty2[4] = ty2[5] = ty2[1];
				} else if (dir == 0) {
					getTextureCoordinates("dropper_front_vertical.png", &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					getTextureCoordinates("furnace_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[2] = tx1[3] = tx1[4] = tx1[5] = tx1[0];
					tx2[2] = tx2[3] = tx2[4] = tx2[5] = tx2[0];
					ty1[2] = ty1[3] = ty1[4] = ty1[5] = ty1[0];
					ty2[2] = ty2[3] = ty2[4] = ty2[5] = ty2[0];
				} else {
					getTextureCoordinates("furnace_top.png", &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[1] = tx1[0];
					tx2[1] = tx2[0];
					ty1[1] = ty1[0];
					ty2[1] = ty2[0];
					getTextureCoordinates("furnace_side.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2];
					tx2[3] = tx2[4] = tx2[5] = tx2[2];
					ty1[3] = ty1[4] = ty1[5] = ty1[2];
					ty2[3] = ty2[4] = ty2[5] = ty2[2];
					if (dir == 2) getTextureCoordinates("ddropper_front_horizontal.png", &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					else if (dir == 3) getTextureCoordinates("dropper_front_horizontal.png", &tx1[3], &ty1[3], &tx2[3], &ty2[3]);
					else if (dir == 4) getTextureCoordinates("dropper_front_horizontal.png", &tx1[4], &ty1[4], &tx2[4], &ty2[4]);
					else if (dir == 5) getTextureCoordinates("dropper_front_horizontal.png", &tx1[5], &ty1[5], &tx2[5], &ty2[5]);
				}
			} else if (block == BLK_HAYBALE) {

			} else if (block == BLK_REDSANDSTONE) {

			} else if (block == BLK_REDSANDSTONECHISELED) {
			} else if (block == BLK_REDSANDSTONESLABDOUBLE) {
			} else if (block == BLK_PURPURSLABDOUBLE) {
			} else if (block == BLK_REDSANDSTONESMOOTH) {

			} else {
				return;
			}
			if (*vex == NULL) {
				*vex = malloc(fc * 4 * sizeof(struct vertex_tex));
				*vexs = 0;
			} else {
				*vex = realloc(*vex, ((fc * 4) + *vexs) * sizeof(struct vertex_tex));
			}
			createMultSubCube(0.5, &((*vex)[*vexs]), x + 0.5, y + 0.5, z + 0.5, faceMask, tx1, ty1, tx2, ty2);
			*vexs += fc * 4;
			return;
		}
		if (tn != NULL) {
			float tx1 = 0.;
			float ty1 = 0.;
			float tx2 = 1.;
			float ty2 = 1.;
			if (*vex == NULL) {
				*vex = malloc(fc * 4 * sizeof(struct vertex_tex));
				*vexs = 0;
			} else {
				*vex = realloc(*vex, ((fc * 4) + *vexs) * sizeof(struct vertex_tex));
			}
			getTextureCoordinates(tn, &tx1, &ty1, &tx2, &ty2);
			createSubCube(0.5, &((*vex)[*vexs]), x + 0.5, y + 0.5, z + 0.5, faceMask, tx1, ty1, tx2, ty2);
			*vexs += fc * 4;
		}
	}
}

int isBlockOpaque(block block) {
	int bs = block >> 4;
	bs <<= 4;
	return bs == BLK_STONE || bs == BLK_GRASS || bs == BLK_DIRT || bs == BLK_COBBLESTONE || bs == BLK_WOODENPLANKOAK || bs == BLK_BEDROCK || (bs >= BLK_SAND && bs <= BLK_NOTEBLOCK) || bs == BLK_WOOL || bs == BLK_BLOCKOFGOLD || bs == BLK_BLOCKOFIRON || bs == BLK_STONESLABDOUBLE || bs == BLK_BRICK || bs == BLK_TNT || bs == BLK_BOOKSHELF || bs == BLK_MOSSSTONE || bs == BLK_OBSIDIAN || bs == BLK_DIAMONDORE || bs == BLK_BLOCKOFDIAMOND || bs == BLK_WORKBENCH || bs == BLK_FURNACE || bs == BLK_FURNACESMELTING || bs == BLK_REDSTONEORE || bs == BLK_REDSTONEOREGLOWING || bs == BLK_SNOWBLOCK || bs == BLK_CLAYBLOCK || bs == BLK_JUKEBOX || bs == BLK_PUMPKIN || bs == BLK_NETHERRACK || bs == BLK_SOULSAND || bs == BLK_GLOWSTONE || bs == BLK_JACK_O_LANTERN || bs == BLK_MONSTEREGGSTONE || bs == BLK_STONEBRICKS || bs == BLK_MELONBLOCK || bs == BLK_MYCELIUM || bs == BLK_NETHERBRICK || bs == BLK_ENDSTONE || bs == BLK_REDSTONELAMP || bs == BLK_REDSTONELAMPON || bs == BLK_OAK_WOODSLABDOUBLE
			|| bs == BLK_EMERALDORE || bs == BLK_BLOCKOFEMERALD || bs == BLK_COMMANDBLOCK || bs == BLK_BLOCKOFREDSTONE || bs == BLK_NETHERQUARTZORE || bs == BLK_QUARTZBLOCK || bs == BLK_DROPPER || bs == BLK_STAINEDCLAYWHITE || bs == BLK_DISPENSER || bs == BLK_WOODOAK || bs == BLK_WOODACACIAOAK || bs == BLK_PRISMARINE || bs == BLK_PRISMARINEBRICKS || bs == BLK_DARKPRISMARINE || bs == BLK_SEALANTERN || bs == BLK_HAYBALE || bs == BLK_HARDENEDCLAY || bs == BLK_BLOCKOFCOAL || bs == BLK_PACKEDICE || bs == BLK_REDSANDSTONE || bs == BLK_REDSANDSTONESLABDOUBLE || bs == BLK_PURPURBLOCK || bs == BLK_PURPURPILLAR || bs == BLK_PURPURSLABDOUBLE || bs == BLK_ENDSTONEBRICKS;
}

int doesBlockCollide(block block) {
	return block != BLK_AIR;
}

struct boundingbox bb_cube;

struct boundingbox* getBlockCollision(block block) {
	return &bb_cube;
}

void loadBlocks() {
	bb_cube.maxX = 1.;
	bb_cube.maxY = 1.;
	bb_cube.maxZ = 1.;
}
