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
#include "ingame.h"

void getTextureCoordinates(int tx, int ty, float* tx1, float* ty1, float* tx2, float* ty2) {
	static float tw;
	if (!tw) tw = 1. / (float) def_wrap;
	static float th;
	if (!th) th = 1. / ((float) def_height / ((float) def_width / (float) def_wrap));
	*tx1 = tw * tx + ((float) TEXTURE_BUFFER + 0.01) / (float) def_width;
	*ty1 = th * ty + ((float) TEXTURE_BUFFER + 0.01) / (float) def_height;
	*tx2 = tw * (tx + 1) - ((float) TEXTURE_BUFFER + 0.01) / (float) def_width;
	*ty2 = th * (ty + 1) - ((float) TEXTURE_BUFFER + 0.01) / (float) def_height;
}

void drawBlock(struct vertex_tex** vex, size_t* vexs, size_t* cvec, block blk, unsigned char faceMask, float x, float y, float z, int32_t wx, int32_t wy, int32_t wz) {
	unsigned char fc = 0;
	if (faceMask & 0x01) fc++;
	if (faceMask & 0x02) fc++;
	if (faceMask & 0x04) fc++;
	if (faceMask & 0x08) fc++;
	if (faceMask & 0x10) fc++;
	if (faceMask & 0x20) fc++;
	goto pimpl;
	unimpl: ;
	{
		float tx1 = 0.;
		float ty1 = 0.;
		float tx2 = 1.;
		float ty2 = 1.;
		if (*vexs <= (*cvec * sizeof(struct vertex_tex)) + fc * 4 * sizeof(struct vertex_tex)) {
			*vexs += 2048 * 4 * 6 * sizeof(struct vertex_tex);
			*vex = realloc(*vex, *vexs);
		}
		getTextureCoordinates(19, 14, &tx1, &ty1, &tx2, &ty2);
		createSubCube(0.5, &((*vex)[*cvec]), x + 0.5, y + 0.5, z + 0.5, faceMask, tx1, ty1, tx2, ty2);
		*cvec += fc * 4;
		return;
	}
	pimpl: ;
	if (blk == BLK_WATER) {
		goto unimpl;
	} else if (blk == BLK_WATERNOSPREAD) {
		goto unimpl;
	} else if (blk == BLK_LAVA) {
		goto unimpl;
	} else if (blk == BLK_LAVANOSPREAD) {
		goto unimpl;
	} else if (blk == BLK_RAILPOWERED) {
		goto unimpl;
	} else if (blk == BLK_STICKYPISTON) {
		goto unimpl;
	} else if (blk == BLK_PISTON) {
		goto unimpl;
	} else if (blk == BLK_PISTONHEAD) {
		goto unimpl;
	} else if (blk == BLK_PISTONMOVING) {
		goto unimpl;

	} else if (blk == BLK_TORCH) {
		goto unimpl;
	} else if (blk == BLK_FIRE) {
		goto unimpl;
	} else if (blk == BLK_WOODENSTAIRSOAK) {
		goto unimpl;
	} else if (blk == BLK_CHEST) {
		goto unimpl;
	} else if (blk == BLK_REDSTONEWIRE) {
		goto unimpl;
	} else if (blk == BLK_WHEATCROP) {
		goto unimpl;
	} else if (blk >> 4 == BLK_FARMLAND >> 4) {
		if (*vexs <= (*cvec * sizeof(struct vertex_tex)) + 6 * 4 * sizeof(struct vertex_tex)) {
			*vexs += 2048 * 4 * 6 * sizeof(struct vertex_tex);
			*vex = realloc(*vex, *vexs);
		}
		int meta = blk & 0x0f;
		float dof = (1. / 16.);
		float tx1[6];
		float tx2[6];
		float ty1[6];
		float ty2[6];
		getTextureCoordinates(2, 1, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
		tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
		ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
		tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
		ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1] - (dof / (float) def_wrap);
		if (meta) getTextureCoordinates(0, 19, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
		else getTextureCoordinates(30, 13, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
		createMultSub(0.5, (dof * 15.) / 2., 0.5, &((*vex)[*cvec]), x + 0.5, y + 0.5 - (dof / 2.), z + 0.5, 0xFF, tx1, ty1, tx2, ty2);
		*cvec += 6 * 4;
	} else if (blk == BLK_SIGNBLOCK) {
		goto unimpl;
	} else if (blk == BLK_WOODDOORBLOCK) {
		goto unimpl;
	} else if (blk == BLK_RAIL) {
		goto unimpl;
	} else if (blk == BLK_COBBLESTONESTAIRS) {
		goto unimpl;
	} else if (blk == BLK_SIGNWALLBLOCK) {
		goto unimpl;
	} else if (blk == BLK_STONEPRESSUREPLATE) {
		goto unimpl;
	} else if (blk == BLK_IRONDOORBLOCK) {
		goto unimpl;
	} else if (blk == BLK_WOODENPRESSUREPLATE) {
		goto unimpl;
	} else if (blk == BLK_REDSTONETORCH) {
		goto unimpl;
	} else if (blk == BLK_BUTTONSTONE) {
		goto unimpl;
	} else if (blk == BLK_CACTUS) {
		goto unimpl;
	} else if (blk == BLK_FENCEOAK) {
		goto unimpl;
	} else if (blk == BLK_PUMPKIN) {
		goto unimpl;
	} else if (blk == BLK_JACK_O_LANTERN) {
		goto unimpl;
	} else if (blk == BLK_CAKEBLOCK) {
		goto unimpl;
	} else if (blk == BLK_REDSTONEREPEATERBLOCKOFF) {
		goto unimpl;
	} else if (blk == BLK_REDSTONEREPEATERBLOCKON) {
		goto unimpl;
	} else if (blk == BLK_GLASSPANE) {
		goto unimpl;
	} else if (blk == BLK_PUMPKINVINE) {
		goto unimpl;
	} else if (blk == BLK_MELONVINE) {
		goto unimpl;
	} else if (blk == BLK_VINES) {
		goto unimpl;
	} else if (blk == BLK_FENCEGATEOAK) {
		goto unimpl;
	} else if (blk == BLK_BRICKSTAIRS) {
		goto unimpl;
	} else if (blk == BLK_STONEBRICKSTAIRS) {
		goto unimpl;
	} else if (blk == BLK_LILYPAD) {
		goto unimpl;
	} else if (blk == BLK_NETHERBRICKFENCE) {
		goto unimpl;
	} else if (blk == BLK_NETHERBRICKSTAIRS) {
		goto unimpl;
	} else if (blk == BLK_NETHERWART) {
		goto unimpl;
	} else if (blk == BLK_ENCHANTMENTTABLE) {
		goto unimpl;
	} else if (blk == BLK_BREWINGSTANDBLOCK) {
		goto unimpl;
	} else if (blk == BLK_CAULDRONBLOCK) {
		goto unimpl;
	} else if (blk == BLK_ENDPORTAL) {
		goto unimpl;
	} else if (blk == BLK_ENDPORTALFRAME) {
		goto unimpl;
	} else if (blk == BLK_COCOAPLANT) {
		goto unimpl;
	} else if (blk == BLK_SANDSTONESTAIRS) {
		goto unimpl;
	} else if (blk == BLK_ENDERCHEST) {
		goto unimpl;
	} else if (blk == BLK_TRIPWIREHOOK) {
		goto unimpl;
	} else if (blk == BLK_WOODENSTAIRSSPRUCE) {
		goto unimpl;
	} else if (blk == BLK_WOODENSTAIRSBIRCH) {
		goto unimpl;
	} else if (blk == BLK_WOODENSTAIRSJUNGLE) {
		goto unimpl;
	} else if (blk == BLK_COBBLESTONEWALL) {
		goto unimpl;
	} else if (blk == BLK_MOSSYCOBBLESTONEWALL) {
		goto unimpl;
	} else if (blk == BLK_FLOWERPOTBLOCK) {
		goto unimpl;
	} else if (blk == BLK_CARROTCROP) {
		goto unimpl;
	} else if (blk == BLK_POTATOESCROP) {
		goto unimpl;
	} else if (blk == BLK_BUTTONWOOD) {
		goto unimpl;
	} else if (blk == BLK_HEADBLOCKSKELETON) {
		goto unimpl;
	} else if (blk == BLK_HEADBLOCKWITHER) {
		goto unimpl;
	} else if (blk == BLK_HEADBLOCKZOMBIE) {
		goto unimpl;
	} else if (blk == BLK_HEADBLOCKSTEVE) {
		goto unimpl;
	} else if (blk == BLK_HEADBLOCKCREEPER) {
		goto unimpl;
	} else if (blk == BLK_ANVIL) {
		goto unimpl;
	} else if (blk == BLK_ANVILSLIGHTLYDAMAGED) {
		goto unimpl;
	} else if (blk == BLK_ANVILVERYDAMAGED) {
		goto unimpl;
	} else if (blk == BLK_TRAPPEDCHEST) {
		goto unimpl;
	} else if (blk == BLK_WEIGHTEDPRESSUREPLATELIGHT) {
		goto unimpl;
	} else if (blk == BLK_WEIGHTEDPRESSUREPLATEHEAVY) {
		goto unimpl;
	} else if (blk == BLK_REDSTONECOMPARATOROFF) {
		goto unimpl;
	} else if (blk == BLK_REDSTONECOMPARATORON) {
		goto unimpl;
	} else if (blk == BLK_DAYLIGHTSENSOR) {
		goto unimpl;
	} else if (blk == BLK_HOPPER) {
		goto unimpl;
	} else if (blk == BLK_QUARTZSTAIRS) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANEWHITE) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANEORANGE) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANEMAGENTA) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANELIGHTBLUE) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANEYELLOW) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANELIME) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANEPINK) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANEGRAY) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANELIGHTGRAY) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANECYAN) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANEPURPLE) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANEBLUE) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANEBROWN) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANEGREEN) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANERED) {
		goto unimpl;
	} else if (blk == BLK_STAINEDGLASSPANEBLACK) {
		goto unimpl;
	} else if (blk == BLK_CARPETWHITE) {
		goto unimpl;
	} else if (blk == BLK_CARPETORANGE) {
		goto unimpl;
	} else if (blk == BLK_CARPETMAGENTA) {
		goto unimpl;
	} else if (blk == BLK_CARPETLIGHTBLUE) {
		goto unimpl;
	} else if (blk == BLK_CARPETYELLOW) {
		goto unimpl;
	} else if (blk == BLK_CARPETLIME) {
		goto unimpl;
	} else if (blk == BLK_CARPETPINK) {
		goto unimpl;
	} else if (blk == BLK_CARPETGREY) {
		goto unimpl;
	} else if (blk == BLK_CARPETLIGHTGRAY) {
		goto unimpl;
	} else if (blk == BLK_CARPETCYAN) {
		goto unimpl;
	} else if (blk == BLK_CARPETPURPLE) {
		goto unimpl;
	} else if (blk == BLK_CARPETBLUE) {
		goto unimpl;
	} else if (blk == BLK_CARPETBROWN) {
		goto unimpl;
	} else if (blk == BLK_CARPETGREEN) {
		goto unimpl;
	} else if (blk == BLK_CARPETRED) {
		goto unimpl;
	} else if (blk == BLK_CARPETBLACK) {
		goto unimpl;
	} else if (blk == BLK_STANDINGBANNERBLOCK) {
		goto unimpl;
	} else if (blk == BLK_WALLBANNERBLOCK) {
		goto unimpl;
	} else if (blk == BLK_INVERTEDDAYLIGHTSENSOR) {
		goto unimpl;
	} else if (blk == BLK_REDSANDSTONESTAIRS) {
		goto unimpl;
	} else if (blk == BLK_FENCEGATESPRUCE) {
		goto unimpl;
	} else if (blk == BLK_FENCEGATEBIRCH) {
		goto unimpl;
	} else if (blk == BLK_FENCEGATEJUNGLE) {
		goto unimpl;
	} else if (blk == BLK_FENCEGATEDARKOAK) {
		goto unimpl;
	} else if (blk == BLK_FENCEGATEACACIA) {
		goto unimpl;
	} else if (blk == BLK_FENCESPRUCE) {
		goto unimpl;
	} else if (blk == BLK_FENCEBIRCH) {
		goto unimpl;
	} else if (blk == BLK_FENCEJUNGLE) {
		goto unimpl;
	} else if (blk == BLK_FENCEDARKOAK) {
		goto unimpl;
	} else if (blk == BLK_FENCEACACIA) {
		goto unimpl;
	} else if (blk == BLK_WOODENDOORBLOCKSPRUCE) {
		goto unimpl;
	} else if (blk == BLK_WOODENDOORBLOCKBIRCH) {
		goto unimpl;
	} else if (blk == BLK_WOODENDOORBLOCKJUNGLE) {
		goto unimpl;
	} else if (blk == BLK_WOODENDOORBLOCKACACIA) {
		goto unimpl;
	} else if (blk == BLK_WOODENDOORBLOCKDARKOAK) {
		goto unimpl;
	} else if (blk == BLK_PURPURSTAIRS) {
		goto unimpl;
	} else if (blk == BLK_ENDSTONEBRICKS) {
		goto unimpl;
	} else if (blk == BLK_GRASSPATH) {
		goto unimpl;
	} else if (blk == BLK_ENDGATEWAY) {
		goto unimpl;
	} else if (blk == BLK_RAILDETECTOR) {
		goto unimpl;
	} else if (blk == BLK_BOOKSHELF) {
		goto unimpl;
	} else if (blk == BLK_LADDER) {
		goto unimpl;
	} else if (blk == BLK_LEVER) {
		goto unimpl;
	} else if (blk == BLK_REDSTONETORCHOFF) {
		goto unimpl;
	} else if (blk == BLK_SNOW) {
		goto unimpl;
	} else if (blk == BLK_PORTAL) {
		goto unimpl;
	} else if (blk == BLK_TRAPDOOR) {
		goto unimpl;
	} else if (blk == BLK_IRONBARS) {
		goto unimpl;
	} else if (blk == BLK_DRAGONEGG) {
		goto unimpl;
	} else if (blk == BLK_TRIPWIRE) {
		goto unimpl;
	} else if (blk == BLK_BEACON) {
		goto unimpl;
	} else if (blk == BLK_RAILACTIVATOR) {
		goto unimpl;
	} else if (blk == BLK_IRONTRAPDOOR) {
		goto unimpl;
	} else if (blk == BLK_ENDROD) {
		goto unimpl;
	} else if (blk == BLK_CHORUSPLANT) {
		goto unimpl;
	} else if (blk == BLK_CHORUSFLOWER) {
		goto unimpl;
	} else if (blk == BLK_STRUCTUREBLOCK) {
		goto unimpl;
	} else if (blk == BLK_BEDBLOCK) {
		goto unimpl;
	} else if (blk == BLK_WOODENSTAIRSACACIA) {
		goto unimpl;
	} else if (blk == BLK_WOODENSTAIRSDARKOAK) {
		goto unimpl;
	} else {
		int tx = -1;
		int ty = -1;
		if (blk == BLK_AIR) {
			return;
		} else if (blk == BLK_STONE) {
			tx = 31;
			ty = 13;
		} else if (blk == BLK_GRANITE) {
			tx = 14;
			ty = 14;
		} else if (blk == BLK_POLISHEDGRANITE) {
			tx = 9;
			ty = 7;
		} else if (blk == BLK_DIORITE) {
			tx = 21;
			ty = 0;
		} else if (blk == BLK_POLISHEDDIORITE) {
			tx = 13;
			ty = 17;
		} else if (blk == BLK_ANDESITE) {
			tx = 3;
			ty = 14;
		} else if (blk == BLK_POLISHEDANDESITE) {
			tx = 11;
			ty = 1;
		} else if (blk == BLK_DIRT) {
			tx = 2;
			ty = 1;
		} else if (blk == BLK_COARSEDIRT) {
			tx = 28;
			ty = 18;
		} else if (blk == BLK_COBBLESTONE || blk == BLK_COBBLESTONESLABDOUBLE) {
			tx = 19;
			ty = 8;
		} else if (blk == BLK_WOODENPLANKOAK || blk == BLK_WOODENSLABDOUBLE || blk == BLK_OAK_WOODSLABDOUBLE) {
			tx = 30;
			ty = 19;
		} else if (blk == BLK_WOODENPLANKSPRUCE || blk == BLK_SPRUCE_WOODSLABDOUBLE) {
			tx = 20;
			ty = 19;
		} else if (blk == BLK_WOODENPLANKBIRCH || blk == BLK_BIRCH_WOODSLABDOUBLE) {
			tx = 27;
			ty = 19;
		} else if (blk == BLK_WOODENPLANKJUNGLE || blk == BLK_JUNGLE_WOODSLABDOUBLE) {
			tx = 3;
			ty = 2;
		} else if (blk == BLK_WOODENPLANKACACIA || blk == BLK_ACACIAWOODSLABDOUBLE) {
			tx = 25;
			ty = 11;
		} else if (blk == BLK_WOODENPLANKDARKOAK || blk == BLK_DARKOAKWOODSLABDOUBLE) {
			tx = 9;
			ty = 1;
		} else if (blk == BLK_BEDROCK) {
			tx = 13;
			ty = 5;
		} else if (blk == BLK_SAND) {
			tx = 23;
			ty = 17;
		} else if (blk == BLK_REDSAND) {
			tx = 1;
			ty = 18;
		} else if (blk == BLK_GRAVEL) {
			tx = 22;
			ty = 17;
		} else if (blk == BLK_GOLDORE) {
			tx = 1;
			ty = 9;
		} else if (blk == BLK_IRONORE) {
			tx = 13;
			ty = 0;
		} else if (blk == BLK_COALORE) {
			tx = 22;
			ty = 5;
		} else if (blk >> 4 == BLK_LEAVESOAK >> 4) {
			int meta = blk & 0x0f;
			meta &= 0x03;
			if (meta == 0) {
				tx = 31;
				ty = 16;
			} else if (meta == 1) {
				tx = 4;
				ty = 9;
			} else if (meta == 2) {
				tx = 28;
				ty = 2;
			} else if (meta == 3) {
				tx = 5;
				ty = 14;
			}
		} else if (blk == BLK_SPONGE) {
			tx = 6;
			ty = 9;
		} else if (blk == BLK_WETSPONGE) {
			tx = 0;
			ty = 14;
		} else if (blk == BLK_GLASS) {
			tx = 18;
			ty = 15;
		} else if (blk == BLK_NOTEBLOCK) {
			tx = 21;
			ty = 11;
		} else if (blk == BLK_BRICK || blk == BLK_BRICKSLABDOUBLE) {
			tx = 28;
			ty = 14;
		} else if (blk == BLK_OBSIDIAN) {
			tx = 5;
			ty = 21;
		} else if (blk == BLK_MOBSPAWNER) {
			tx = 18;
			ty = 19;
		} else if (blk == BLK_DIAMONDORE) {
			tx = 19;
			ty = 7;
		} else if (blk == BLK_REDSTONEORE) { //TODO: activated
			tx = 2;
			ty = 9;
		} else if (blk == BLK_ICE) {
			tx = 1;
			ty = 10;
		} else if (blk == BLK_NETHERRACK) {
			tx = 9;
			ty = 2;
		} else if (blk == BLK_SOULSAND) {
			tx = 9;
			ty = 2;
		} else if (blk == BLK_GLOWSTONE) {
			tx = 0;
			ty = 21;
		} else if (blk == BLK_NETHERBRICK || blk == BLK_NETHERBRICKSLABDOUBLE) {
			tx = 3;
			ty = 11;
		} else if (blk == BLK_ENDSTONE) {
			tx = 31;
			ty = 2;
		} else if (blk == BLK_REDSTONELAMP) {
			tx = 17;
			ty = 18;
		} else if (blk == BLK_REDSTONELAMPON) {
			tx = 17;
			ty = 15;
		} else if (blk == BLK_EMERALDORE) {
			tx = 4;
			ty = 17;
		} else if (blk == BLK_PRISMARINEBRICKS) {
			tx = 4;
			ty = 18;
		} else if (blk == BLK_SEALANTERN) {
			tx = 19;
			ty = 2;
		} else if (blk == BLK_HARDENEDCLAY) {
			tx = 31;
			ty = 5;
		} else if (blk == BLK_HARDENEDCLAY_ORANGE) {
			tx = 22;
			ty = 9;
		} else if (blk == BLK_HARDENEDCLAY_MAGENTA) {
			tx = 5;
			ty = 1;
		} else if (blk == BLK_HARDENEDCLAY_LIGHTBLUE) {
			tx = 18;
			ty = 7;
		} else if (blk == BLK_HARDENEDCLAY_YELLOW) {
			tx = 21;
			ty = 18;
		} else if (blk == BLK_HARDENEDCLAY_LIME) {
			tx = 6;
			ty = 3;
		} else if (blk == BLK_HARDENEDCLAY_PINK) {
			tx = 5;
			ty = 15;
		} else if (blk == BLK_HARDENEDCLAY_GRAY) {
			tx = 26;
			ty = 11;
		} else if (blk == BLK_HARDENEDCLAY_LIGHTGRAY) {
			tx = 21;
			ty = 14;
		} else if (blk == BLK_HARDENEDCLAY_CYAN) {
			tx = 19;
			ty = 11;
		} else if (blk == BLK_HARDENEDCLAY_PURPLE) {
			tx = 20;
			ty = 5;
		} else if (blk == BLK_HARDENEDCLAY_BLUE) {
			tx = 18;
			ty = 8;
		} else if (blk == BLK_HARDENEDCLAY_BROWN) {
			tx = 12;
			ty = 9;
		} else if (blk == BLK_HARDENEDCLAY_GREEN) {
			tx = 2;
			ty = 15;
		} else if (blk == BLK_HARDENEDCLAY_RED) {
			tx = 16;
			ty = 2;
		} else if (blk == BLK_HARDENEDCLAY_BLACK) {
			tx = 5;
			ty = 19;
		} else if (blk == BLK_PURPURBLOCK || blk == BLK_PURPURSLABDOUBLE) {
			tx = 6;
			ty = 18;
		} else if (blk == BLK_LAPISLAZULIORE) {
			tx = 6;
			ty = 19;
		} else if (blk == BLK_LAPISLAZULIBLOCK) {
			tx = 31;
			ty = 18;
		} else if (blk == BLK_WOOL) {
			tx = 10;
			ty = 19;
		} else if (blk == BLK_ORANGEWOOL) {
			tx = 23;
			ty = 19;
		} else if (blk == BLK_MAGENTAWOOL) {
			tx = 19;
			ty = 6;
		} else if (blk == BLK_LIGHTBLUEWOOL) {
			tx = 29;
			ty = 5;
		} else if (blk == BLK_YELLOWWOOL) {
			tx = 12;
			ty = 18;
		} else if (blk == BLK_LIMEWOOL) {
			tx = 11;
			ty = 7;
		} else if (blk == BLK_PINKWOOL) {
			tx = 19;
			ty = 18;
		} else if (blk == BLK_GRAYWOOL) {
			tx = 31;
			ty = 19;
		} else if (blk == BLK_LIGHTGRAYWOOL) {
			tx = 22;
			ty = 1;
		} else if (blk == BLK_CYANWOOL) {
			tx = 14;
			ty = 0;
		} else if (blk == BLK_PURPLEWOOL) {
			tx = 26;
			ty = 5;
		} else if (blk == BLK_BLUEWOOL) {
			tx = 21;
			ty = 5;
		} else if (blk == BLK_BROWNWOOL) {
			tx = 21;
			ty = 8;
		} else if (blk == BLK_GREENWOOL) {
			tx = 29;
			ty = 16;
		} else if (blk == BLK_REDWOOL) {
			tx = 25;
			ty = 18;
		} else if (blk == BLK_BLACKWOOL) {
			tx = 24;
			ty = 16;
		} else if (blk == BLK_BLOCKOFGOLD) {
			tx = 15;
			ty = 15;
		} else if (blk == BLK_BLOCKOFIRON) {
			tx = 8;
			ty = 9;
		} else if (blk == BLK_MOSSSTONE) {
			tx = 21;
			ty = 19;
		} else if (blk == BLK_BLOCKOFDIAMOND) {
			tx = 15;
			ty = 9;
		} else if (blk == BLK_REDSTONEOREGLOWING) {
			tx = 2;
			ty = 9;
			// TODO glow effect?
		} else if (blk == BLK_SNOWBLOCK) {
			tx = 7;
			ty = 9;
		} else if (blk == BLK_CLAYBLOCK) {
			tx = 1;
			ty = 1;
		} else if (blk == BLK_STAINEDGLASSWHITE) {
			tx = 18;
			ty = 15;
		} else if (blk == BLK_STAINEDGLASSORANGE) {
			tx = 26;
			ty = 17;
		} else if (blk == BLK_STAINEDGLASSMAGENTA) {
			tx = 12;
			ty = 5;
		} else if (blk == BLK_STAINEDGLASSLIGHTBLUE) {
			tx = 5;
			ty = 11;
		} else if (blk == BLK_STAINEDGLASSYELLOW) {
			tx = 0;
			ty = 7;
		} else if (blk == BLK_STAINEDGLASSLIME) {
			tx = 31;
			ty = 6;
		} else if (blk == BLK_STAINEDGLASSPINK) {
			tx = 18;
			ty = 6;
		} else if (blk == BLK_STAINEDGLASSGRAY) {
			tx = 27;
			ty = 7;
		} else if (blk == BLK_STAINEDGLASSLIGHTGREY) {
			tx = 29;
			ty = 2;
		} else if (blk == BLK_STAINEDGLASSCYAN) {
			tx = 24;
			ty = 0;
		} else if (blk == BLK_STAINEDGLASSPURPLE) {
			tx = 25;
			ty = 2;
		} else if (blk == BLK_STAINEDGLASSBLUE) {
			tx = 17;
			ty = 21;
		} else if (blk == BLK_STAINEDGLASSBROWN) {
			tx = 16;
			ty = 15;
		} else if (blk == BLK_STAINEDGLASSGREEN) {
			tx = 13;
			ty = 14;
		} else if (blk == BLK_STAINEDGLASSRED) {
			tx = 10;
			ty = 0;
		} else if (blk == BLK_STAINEDGLASSBLACK) {
			tx = 26;
			ty = 9;
		} else if (blk == BLK_MONSTEREGGSTONE) {
			tx = 31;
			ty = 13;
		} else if (blk == BLK_MONSTEREGGCOBBLESTONE) {
			tx = 19;
			ty = 8;
		} else if (blk == BLK_MONSTEREGGSTONEBRICK) {
			tx = 16;
			ty = 11;
		} else if (blk == BLK_MONSTEREGGMOSSYSTONEBRICK) {
			tx = 11;
			ty = 18;
		} else if (blk == BLK_MONSTEREGGCRACKEDSTONE) {
			tx = 6;
			ty = 1;
		} else if (blk == BLK_MONSTEREGGCHISELEDSTONE) {
			tx = 8;
			ty = 4;
		} else if (blk == BLK_STONEBRICKS || blk == BLK_STONEBRICKSLABDOUBLE) {
			tx = 16;
			ty = 11;
		} else if (blk == BLK_MOSSYSTONEBRICKS) {
			tx = 11;
			ty = 18;
		} else if (blk == BLK_CRACKEDSTONEBRICKS) {
			tx = 6;
			ty = 1;
		} else if (blk == BLK_CHISELEDSTONEBRICK) {
			tx = 8;
			ty = 4;
		} else if (blk == BLK_BLOCKOFEMERALD) {
			tx = 30;
			ty = 2;
		} else if (blk == BLK_BLOCKOFREDSTONE) {
			tx = 27;
			ty = 14;
		} else if (blk == BLK_NETHERQUARTZORE) {
			tx = 10;
			ty = 9;
		} else if (blk == BLK_STAINEDCLAYWHITE) {
			tx = 20;
			ty = 11;
		} else if (blk == BLK_STAINEDCLAYORANGE) {
			tx = 22;
			ty = 9;
		} else if (blk == BLK_STAINEDCLAYMAGENTA) {
			tx = 5;
			ty = 1;
		} else if (blk == BLK_STAINEDCLAYLIGHTBLUE) {
			tx = 18;
			ty = 7;
		} else if (blk == BLK_STAINEDCLAYYELLOW) {
			tx = 21;
			ty = 18;
		} else if (blk == BLK_STAINEDCLAYLIME) {
			tx = 6;
			ty = 3;
		} else if (blk == BLK_STAINEDCLAYPINK) {
			tx = 5;
			ty = 15;
		} else if (blk == BLK_STAINEDCLAYGRAY) {
			tx = 26;
			ty = 11;
		} else if (blk == BLK_STAINEDCLAYLIGHTGRAY) {
			tx = 21;
			ty = 14;
		} else if (blk == BLK_STAINEDCLAYCYAN) {
			tx = 19;
			ty = 11;
		} else if (blk == BLK_STAINEDCLAYPURPLE) {
			tx = 20;
			ty = 5;
		} else if (blk == BLK_STAINEDCLAYBLUE) {
			tx = 18;
			ty = 8;
		} else if (blk == BLK_STAINEDCLAYBROWN) {
			tx = 12;
			ty = 9;
		} else if (blk == BLK_STAINEDCLAYGREEN) {
			tx = 2;
			ty = 15;
		} else if (blk == BLK_STAINEDCLAYRED) {
			tx = 16;
			ty = 2;
		} else if (blk == BLK_STAINEDCLAYBLACK) {
			tx = 5;
			ty = 19;
		} else if (blk >> 4 == BLK_LEAVESDARKOAK >> 4) {
			int meta = blk & 0x0f;
			if (meta & 0x01) {
				tx = 28;
				ty = 16;
			} else {
				tx = 28;
				ty = 17;
			}

		} else if (blk == BLK_SLIMEBLOCK) {
			tx = 2;
			ty = 19;
		} else if (blk == BLK_BARRIER) {
			return;
		} else if (blk == BLK_PRISMARINE) {
			tx = 15;
			ty = 14; //TODO: random textures
		} else if (blk == BLK_DARKPRISMARINE) {
			tx = 9;
			ty = 9;
		} else if (blk == BLK_BLOCKOFCOAL) {
			tx = 5;
			ty = 0;
		} else if (blk == BLK_PACKEDICE) {
			tx = 27;
			ty = 1;
		} else if (blk == BLK_SMOOTHSTONESLABDOUBLE) {
			tx = 8;
			ty = 15;
		} else if (tx == -1 && ty == -1) {
			float tx1[6];
			float ty1[6];
			float tx2[6];
			float ty2[6];
			if (blk == BLK_GRASS) {
				getTextureCoordinates(28, 9, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(2, 1, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(6, 2, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (blk == BLK_PODZOL) {
				getTextureCoordinates(21, 1, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(2, 1, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(24, 19, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (blk == BLK_MYCELIUM) {
				getTextureCoordinates(3, 18, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(2, 1, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(30, 16, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (blk >> 4 == BLK_WOODOAK >> 4) {
				int meta = blk & 0x0f;
				int bt = meta & 0x03;
				int dir = (meta & 12) >> 2;
				int ttx = -1;
				int tty = -1;
				int stx = -1;
				int sty = -1;
				if (bt == 0) { // BLK_WOODOAK
					ttx = 4;
					tty = 6;
					stx = 29;
					sty = 9;
				} else if (bt == 1) { // BLK_WOODSPRUCE
					ttx = 22;
					tty = 18;
					stx = 3;
					sty = 19;
				} else if (bt == 2) { // BLK_WOODBIRCH
					ttx = 10;
					tty = 6;
					stx = 17;
					sty = 8;
				} else if (bt == 3) { // BLK_WOODJUNGLE
					ttx = 20;
					tty = 9;
					stx = 18;
					sty = 9;
				}
				getTextureCoordinates(ttx, tty, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				tx1[1] = tx1[0];
				tx2[1] = tx2[0];
				ty1[1] = ty1[0];
				ty2[1] = ty2[0];
				if (dir == 0) {
					getTextureCoordinates(stx, sty, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
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
					getTextureCoordinates(stx, sty, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
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
					getTextureCoordinates(stx, sty, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[1] = tx1[3] = tx1[2] = tx1[0];
					ty1[1] = ty1[3] = ty1[2] = ty1[0];
					tx2[1] = tx2[3] = tx2[2] = tx2[0];
					ty2[1] = ty2[3] = ty2[2] = ty2[0];
				} else if (dir == 3) {
					getTextureCoordinates(stx, sty, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					tx1[1] = tx1[0] = tx1[3] = tx1[4] = tx1[5] = tx1[2];
					ty1[1] = ty1[0] = ty1[3] = ty1[4] = ty1[5] = ty1[2];
					tx2[1] = tx2[0] = tx2[3] = tx2[4] = tx2[5] = tx2[2];
					ty2[1] = ty2[0] = ty2[3] = ty2[4] = ty2[5] = ty2[2];
				}
			} else if (blk >> 4 == BLK_WOODACACIAOAK >> 4) {
				int meta = blk & 0x0f;
				int bt = meta & 0x03;
				int dir = (meta & 12) >> 2;
				int ttx = -1;
				int tty = -1;
				int stx = -1;
				int sty = -1;
				if (bt == 0) { // BLK_WOODOAK
					ttx = 18;
					tty = 18;
					stx = 28;
					sty = 5;
				} else if (bt == 1) { // BLK_WOODSPRUCE
					ttx = 2;
					tty = 10;
					stx = 7;
					sty = 4;
				}
				getTextureCoordinates(ttx, tty, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				tx1[1] = tx1[0];
				tx2[1] = tx2[0];
				ty1[1] = ty1[0];
				ty2[1] = ty2[0];
				if (dir == 0) {
					getTextureCoordinates(stx, sty, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
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
					getTextureCoordinates(stx, sty, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
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
					getTextureCoordinates(stx, sty, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[1] = tx1[3] = tx1[2] = tx1[0];
					ty1[1] = ty1[3] = ty1[2] = ty1[0];
					tx2[1] = tx2[3] = tx2[2] = tx2[0];
					ty2[1] = ty2[3] = ty2[2] = ty2[0];
				} else if (dir == 3) {
					getTextureCoordinates(stx, sty, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					tx1[1] = tx1[0] = tx1[3] = tx1[4] = tx1[5] = tx1[2];
					ty1[1] = ty1[0] = ty1[3] = ty1[4] = ty1[5] = ty1[2];
					tx2[1] = tx2[0] = tx2[3] = tx2[4] = tx2[5] = tx2[2];
					ty2[1] = ty2[0] = ty2[3] = ty2[4] = ty2[5] = ty2[2];
				}
			} else if (blk >> 4 == BLK_DISPENSER >> 4) {
				int meta = blk & 0x0f;
				int dir = meta & 0x07;
				int act = meta & 0x08;
				if (dir == 1) {
					getTextureCoordinates(2, 2, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					getTextureCoordinates(27, 13, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[2] = tx1[3] = tx1[4] = tx1[5] = tx1[1];
					tx2[2] = tx2[3] = tx2[4] = tx2[5] = tx2[1];
					ty1[2] = ty1[3] = ty1[4] = ty1[5] = ty1[1];
					ty2[2] = ty2[3] = ty2[4] = ty2[5] = ty2[1];
				} else if (dir == 0) {
					getTextureCoordinates(2, 2, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					getTextureCoordinates(27, 13, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[2] = tx1[3] = tx1[4] = tx1[5] = tx1[0];
					tx2[2] = tx2[3] = tx2[4] = tx2[5] = tx2[0];
					ty1[2] = ty1[3] = ty1[4] = ty1[5] = ty1[0];
					ty2[2] = ty2[3] = ty2[4] = ty2[5] = ty2[0];
				} else {
					getTextureCoordinates(27, 13, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[1] = tx1[0];
					tx2[1] = tx2[0];
					ty1[1] = ty1[0];
					ty2[1] = ty2[0];
					getTextureCoordinates(18, 11, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2];
					tx2[3] = tx2[4] = tx2[5] = tx2[2];
					ty1[3] = ty1[4] = ty1[5] = ty1[2];
					ty2[3] = ty2[4] = ty2[5] = ty2[2];
					if (dir == 2) getTextureCoordinates(23, 1, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					else if (dir == 3) getTextureCoordinates(23, 1, &tx1[3], &ty1[3], &tx2[3], &ty2[3]);
					else if (dir == 4) getTextureCoordinates(23, 1, &tx1[4], &ty1[4], &tx2[4], &ty2[4]);
					else if (dir == 5) getTextureCoordinates(23, 1, &tx1[5], &ty1[5], &tx2[5], &ty2[5]);
				}
			} else if (blk == BLK_SANDSTONE || blk == BLK_SANDSTONESLABDOUBLE) {
				getTextureCoordinates(27, 17, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(14, 5, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(3, 21, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (blk == BLK_PURPURPILLAR) {
				getTextureCoordinates(20, 0, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				tx1[1] = tx1[0];
				tx2[1] = tx2[0];
				ty1[1] = ty1[0];
				ty2[1] = ty2[0];
				getTextureCoordinates(27, 8, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (blk == BLK_SANDSTONECHISELED) {
				getTextureCoordinates(27, 17, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(14, 5, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(7, 0, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (blk == BLK_SANDSTONESMOOTH || blk == BLK_SMOOTHSANDSTONESLABDOUBLE) {
				getTextureCoordinates(27, 17, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(14, 5, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(8, 17, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (blk == BLK_STONESLABDOUBLE) {
				getTextureCoordinates(8, 15, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				tx1[1] = tx1[0];
				tx2[1] = tx2[0];
				ty1[1] = ty1[0];
				ty2[1] = ty2[0];
				getTextureCoordinates(23, 11, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (blk == BLK_TNT) {
				getTextureCoordinates(0, 2, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(21, 15, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(13, 21, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (blk == BLK_WORKBENCH) {
				getTextureCoordinates(10, 14, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(30, 19, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(4, 14, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[2];
				ty1[3] = ty1[2];
				tx2[3] = tx2[2];
				ty2[3] = ty2[2];
				getTextureCoordinates(24, 9, &tx1[5], &ty1[5], &tx2[5], &ty2[5]);
				tx1[4] = tx1[5];
				ty1[4] = ty1[5];
				tx2[4] = tx2[5];
				ty2[4] = ty2[5];
			} else if (blk >> 4 == BLK_FURNACE >> 4) {
				int dir = (blk & 0x0f) & 0x07;
				getTextureCoordinates(27, 13, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				tx1[1] = tx1[0];
				tx2[1] = tx2[0];
				ty1[1] = ty1[0];
				ty2[1] = ty2[0];
				getTextureCoordinates(18, 11, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
				if (dir == 3) getTextureCoordinates(3, 6, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				else if (dir == 5) getTextureCoordinates(3, 6, &tx1[4], &ty1[4], &tx2[4], &ty2[4]);
				else if (dir == 4) getTextureCoordinates(3, 6, &tx1[5], &ty1[5], &tx2[5], &ty2[5]);
				else getTextureCoordinates(3, 6, &tx1[3], &ty1[3], &tx2[3], &ty2[3]);
			} else if (blk >> 4 == BLK_FURNACESMELTING >> 4) {
				int dir = (blk & 0x0f) & 0x07;
				getTextureCoordinates(27, 13, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				tx1[1] = tx1[0];
				tx2[1] = tx2[0];
				ty1[1] = ty1[0];
				ty2[1] = ty2[0];
				getTextureCoordinates(18, 11, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
				if (dir == 3) getTextureCoordinates(14, 21, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				else if (dir == 5) getTextureCoordinates(14, 21, &tx1[4], &ty1[4], &tx2[4], &ty2[4]);
				else if (dir == 4) getTextureCoordinates(14, 21, &tx1[5], &ty1[5], &tx2[5], &ty2[5]);
				else getTextureCoordinates(14, 21, &tx1[3], &ty1[3], &tx2[3], &ty2[3]);
			} else if (blk == BLK_JUKEBOX) {
				getTextureCoordinates(7, 2, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(8, 19, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
				ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
				tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
				ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1];
			} else if (blk >> 4 == BLK_BROWNMUSHROOMBLOCK >> 4 || blk >> 4 == BLK_REDMUSHROOMBLOCK >> 4) {
				int txcx = (blk >> 4) == (BLK_BROWNMUSHROOMBLOCK >> 4) ? 20 : 22;
				int txcy = (blk >> 4) == (BLK_BROWNMUSHROOMBLOCK >> 4) ? 17 : 19;
				int meta = blk & 0x0f;
				if (meta == 0) {
					getTextureCoordinates(19, 9, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1] = tx1[0];
					ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1] = ty1[0];
					tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1] = tx2[0];
					ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1] = ty2[0];
				} else if (meta == 1) {
					getTextureCoordinates(19, 9, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[4] = tx1[2] = tx1[1];
					ty1[4] = ty1[2] = ty1[1];
					tx2[4] = tx2[2] = tx2[1];
					ty2[4] = ty2[2] = ty2[1];
					getTextureCoordinates(txcx, txcy, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[3] = tx1[5] = tx1[0];
					ty1[3] = ty1[5] = ty1[0];
					tx2[3] = tx2[5] = tx2[0];
					ty2[3] = ty2[5] = ty2[0];
				} else if (meta == 2) {
					getTextureCoordinates(19, 9, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[4] = tx1[5] = tx1[2] = tx1[1];
					ty1[4] = ty1[5] = ty1[2] = ty1[1];
					tx2[4] = tx2[5] = tx2[2] = tx2[1];
					ty2[4] = ty2[5] = ty2[2] = ty2[1];
					getTextureCoordinates(txcx, txcy, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[3] = tx1[0];
					ty1[3] = ty1[0];
					tx2[3] = tx2[0];
					ty2[3] = ty2[0];
				} else if (meta == 3) {
					getTextureCoordinates(19, 9, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[5] = tx1[2] = tx1[1];
					ty1[5] = ty1[2] = ty1[1];
					tx2[5] = tx2[2] = tx2[1];
					ty2[5] = ty2[2] = ty2[1];
					getTextureCoordinates(txcx, txcy, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[3] = tx1[4] = tx1[0];
					ty1[3] = ty1[4] = ty1[0];
					tx2[3] = tx2[4] = tx2[0];
					ty2[3] = ty2[4] = ty2[0];
				} else if (meta == 4) {
					getTextureCoordinates(19, 9, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[4] = tx1[3] = tx1[2] = tx1[1];
					ty1[4] = ty1[3] = ty1[2] = ty1[1];
					tx2[4] = tx2[3] = tx2[2] = tx2[1];
					ty2[4] = ty2[3] = ty2[2] = ty2[1];
					getTextureCoordinates(txcx, txcy, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[5] = tx1[0];
					ty1[5] = ty1[0];
					tx2[5] = tx2[0];
					ty2[5] = ty2[0];
				} else if (meta == 5) {
					getTextureCoordinates(19, 9, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
					ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
					tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
					ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1];
					getTextureCoordinates(txcx, txcy, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				} else if (meta == 6) {
					getTextureCoordinates(19, 9, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[3] = tx1[5] = tx1[2] = tx1[1];
					ty1[3] = ty1[5] = ty1[2] = ty1[1];
					tx2[3] = tx2[5] = tx2[2] = tx2[1];
					ty2[3] = ty2[5] = ty2[2] = ty2[1];
					getTextureCoordinates(txcx, txcy, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[4] = tx1[0];
					ty1[4] = ty1[0];
					tx2[4] = tx2[0];
					ty2[4] = ty2[0];
				} else if (meta == 7) {
					getTextureCoordinates(19, 9, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[4] = tx1[3] = tx1[1];
					ty1[4] = ty1[3] = ty1[1];
					tx2[4] = tx2[3] = tx2[1];
					ty2[4] = ty2[3] = ty2[1];
					getTextureCoordinates(txcx, txcy, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[5] = tx1[2] = tx1[0];
					ty1[5] = ty1[2] = ty1[0];
					tx2[5] = tx2[2] = tx2[0];
					ty2[5] = ty2[2] = ty2[0];
				} else if (meta == 8) {
					getTextureCoordinates(19, 9, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[3] = tx1[5] = tx1[4] = tx1[1];
					ty1[3] = ty1[5] = ty1[4] = ty1[1];
					tx2[3] = tx2[5] = tx2[4] = tx2[1];
					ty2[3] = ty2[5] = ty2[4] = ty2[1];
					getTextureCoordinates(txcx, txcy, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[2] = tx1[0];
					ty1[2] = ty1[0];
					tx2[2] = tx2[0];
					ty2[2] = ty2[0];
				} else if (meta == 9) {
					getTextureCoordinates(19, 9, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[5] = tx1[3] = tx1[1];
					ty1[5] = ty1[3] = ty1[1];
					tx2[5] = tx2[3] = tx2[1];
					ty2[5] = ty2[3] = ty2[1];
					getTextureCoordinates(txcx, txcy, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[4] = tx1[2] = tx1[0];
					ty1[4] = ty1[2] = ty1[0];
					tx2[4] = tx2[2] = tx2[0];
					ty2[4] = ty2[2] = ty2[0];
				} else if (meta == 10) {
					getTextureCoordinates(19, 9, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[1] = tx1[0];
					tx2[1] = tx2[0];
					ty1[1] = ty1[0];
					ty2[1] = ty2[0];
					getTextureCoordinates(1, 14, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2];
					ty1[3] = ty1[4] = ty1[5] = ty1[2];
					tx2[3] = tx2[4] = tx2[5] = tx2[2];
					ty2[3] = ty2[4] = ty2[5] = ty2[2];
				} else if (meta == 14) {
					getTextureCoordinates(txcx, txcy, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1] = tx1[0];
					ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1] = ty1[0];
					tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1] = tx2[0];
					ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1] = ty2[0];
				} else if (meta == 15) {
					getTextureCoordinates(1, 14, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1] = tx1[0];
					ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1] = ty1[0];
					tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1] = tx2[0];
					ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1] = ty2[0];
				}
			} else if (blk == BLK_MELONBLOCK) {
				getTextureCoordinates(20, 14, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(9, 21, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
				ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
				tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
				ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1];
			} else if (blk == BLK_COMMANDBLOCK) {
				return; // TODO:
			} else if (blk == BLK_QUARTZBLOCK || blk == BLK_QUARTZSLABDOUBLE) {
				getTextureCoordinates(28, 13, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(9, 18, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(3, 15, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (blk == BLK_CHISELEDQUARTZBLOCK) {
				getTextureCoordinates(10, 4, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(15, 5, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
				ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
				tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
				ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1];
			} else if (blk == BLK_PILLARQUARTZBLOCK) {
				getTextureCoordinates(23, 15, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(2, 17, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
				ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
				tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
				ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1];
			} else if (blk == BLK_DROPPER) {
				int meta = blk & 0x0f;
				int dir = meta & 0x07;
				int act = meta & 0x08;
				if (dir == 1) {
					getTextureCoordinates(27, 18, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					getTextureCoordinates(27, 13, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					tx1[2] = tx1[3] = tx1[4] = tx1[5] = tx1[1];
					tx2[2] = tx2[3] = tx2[4] = tx2[5] = tx2[1];
					ty1[2] = ty1[3] = ty1[4] = ty1[5] = ty1[1];
					ty2[2] = ty2[3] = ty2[4] = ty2[5] = ty2[1];
				} else if (dir == 0) {
					getTextureCoordinates(27, 18, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
					getTextureCoordinates(27, 13, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[2] = tx1[3] = tx1[4] = tx1[5] = tx1[0];
					tx2[2] = tx2[3] = tx2[4] = tx2[5] = tx2[0];
					ty1[2] = ty1[3] = ty1[4] = ty1[5] = ty1[0];
					ty2[2] = ty2[3] = ty2[4] = ty2[5] = ty2[0];
				} else {
					getTextureCoordinates(27, 13, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[1] = tx1[0];
					tx2[1] = tx2[0];
					ty1[1] = ty1[0];
					ty2[1] = ty2[0];
					getTextureCoordinates(18, 11, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					tx1[3] = tx1[4] = tx1[5] = tx1[2];
					tx2[3] = tx2[4] = tx2[5] = tx2[2];
					ty1[3] = ty1[4] = ty1[5] = ty1[2];
					ty2[3] = ty2[4] = ty2[5] = ty2[2];
					if (dir == 2) getTextureCoordinates(11, 0, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					else if (dir == 3) getTextureCoordinates(11, 0, &tx1[3], &ty1[3], &tx2[3], &ty2[3]);
					else if (dir == 4) getTextureCoordinates(11, 0, &tx1[4], &ty1[4], &tx2[4], &ty2[4]);
					else if (dir == 5) getTextureCoordinates(11, 0, &tx1[5], &ty1[5], &tx2[5], &ty2[5]);
				}
			} else if (blk == BLK_HAYBALE) {
				int meta = blk & 0x0f;
				int dir = (meta & 12) >> 2;
				int ttx = 26;
				int tty = 14;
				int stx = 4;
				int sty = 1;
				getTextureCoordinates(ttx, tty, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				tx1[1] = tx1[0];
				tx2[1] = tx2[0];
				ty1[1] = ty1[0];
				ty2[1] = ty2[0];
				if (dir == 0) {
					getTextureCoordinates(stx, sty, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
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
					getTextureCoordinates(stx, sty, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
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
					getTextureCoordinates(stx, sty, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
					tx1[1] = tx1[3] = tx1[2] = tx1[0];
					ty1[1] = ty1[3] = ty1[2] = ty1[0];
					tx2[1] = tx2[3] = tx2[2] = tx2[0];
					ty2[1] = ty2[3] = ty2[2] = ty2[0];
				} else if (dir == 3) {
					getTextureCoordinates(stx, sty, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					tx1[1] = tx1[0] = tx1[3] = tx1[4] = tx1[5] = tx1[2];
					ty1[1] = ty1[0] = ty1[3] = ty1[4] = ty1[5] = ty1[2];
					tx2[1] = tx2[0] = tx2[3] = tx2[4] = tx2[5] = tx2[2];
					ty2[1] = ty2[0] = ty2[3] = ty2[4] = ty2[5] = ty2[2];
				}
			} else if (blk == BLK_REDSANDSTONE || blk == BLK_REDSANDSTONESLABDOUBLE) {
				getTextureCoordinates(24, 2, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(24, 1, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(14, 2, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (blk == BLK_REDSANDSTONECHISELED) {
				getTextureCoordinates(24, 2, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(24, 1, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(25, 0, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (blk == BLK_REDSANDSTONESMOOTH) {
				getTextureCoordinates(24, 2, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(24, 1, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(26, 8, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else {
				int tx = 0;
				int ty = 0;
				if (blk == BLK_TALLGRASSDEADSHRUB) {
					tx = 12;
					ty = 19;
				} else if (blk == BLK_TALLGRASS) {
					tx = 8;
					ty = 21;
				} else if (blk == BLK_TALLGRASSFERN) {
					tx = 11;
					ty = 4;
				} else if (blk == BLK_ALLIUM) {
					tx = 5;
					ty = 17;
				} else if (blk == BLK_SAPLINGACACIA) {
					tx = 9;
					ty = 17;
				} else if (blk == BLK_SAPLINGBIRCH) {
					tx = 19;
					ty = 1;
				} else if (blk == BLK_LARGEFERN_BOTTOM) {
					tx = 17;
					ty = 1;
				} else if (blk == BLK_DOUBLE_TOP) {
					block bbelow = getBlockWorld(gs.world, wx, wy - 1, wz);
					if (bbelow == BLK_LARGEFERN_BOTTOM) {
						tx = 4;
						ty = 2;
					} else if (bbelow == BLK_DOUBLETALLGRASS_BOTTOM) {
						tx = 29;
						ty = 19;
					} else if (bbelow == BLK_PEONY_BOTTOM) {
						tx = 16;
						ty = 6;
					} else if (bbelow == BLK_LILAC_BOTTOM) {
						tx = 22;
						ty = 6;
					} else if (bbelow == BLK_ROSEBUSH_BOTTOM) {
						tx = 15;
						ty = 2;
					} else if (bbelow == BLK_SUNFLOWER_BOTTOM) { // TODO:
						tx = 19;
						ty = 15;
					} else {
						goto unimpl;
					}
				} else if (blk == BLK_DOUBLETALLGRASS_BOTTOM) {
					tx = 5;
					ty = 6;
				} else if (blk == BLK_WHITETULIP) {
					tx = 0;
					ty = 0;
				} else if (blk == BLK_BROWNMUSHROOM) {
					tx = 22;
					ty = 8;
				} else if (blk == BLK_COBWEB) {
					tx = 1;
					ty = 19;
				} else if (blk == BLK_OXEYEDAISY) {
					tx = 20;
					ty = 6;
				} else if (blk == BLK_SAPLINGSPRUCE) {
					tx = 0;
					ty = 10;
				} else if (blk == BLK_PEONY_BOTTOM) {
					tx = 17;
					ty = 19;
				} else if (blk == BLK_ORANGETULIP) {
					tx = 11;
					ty = 21;
				} else if (blk == BLK_SAPLINGDARKOAK) {
					tx = 27;
					ty = 5;
				} else if (blk == BLK_LILAC_BOTTOM) {
					tx = 3;
					ty = 17;
				} else if (blk == BLK_POPPY) {
					tx = 1;
					ty = 21;
				} else if (blk == BLK_REDMUSHROOM) {
					tx = 21;
					ty = 6;
				} else if (blk == BLK_DANDELION) {
					tx = 10;
					ty = 18;
				} else if (blk == BLK_BLUEORCHID) {
					tx = 24;
					ty = 6;
				} else if (blk == BLK_ROSEBUSH_BOTTOM) {
					tx = 3;
					ty = 9;
				} else if (blk == BLK_SUNFLOWER_BOTTOM) {
					tx = 6;
					ty = 17;
				} else if (blk == BLK_AZUREBLUET) {
					tx = 25;
					ty = 19;
				} else if (blk == BLK_SAPLINGOAK) {
					tx = 16;
					ty = 0;
				} else if (blk == BLK_PINKTULIP) {
					tx = 30;
					ty = 14;
				} else if (blk == BLK_AZUREBLUET) {
					tx = 22;
					ty = 6;
				} else if (blk == BLK_SAPLINGJUNGLE) {
					tx = 12;
					ty = 11;
				} else if (blk == BLK_SUGARCANEBLOCK) {
					tx = 21;
					ty = 17;
				} else if (blk == BLK_REDTULIP) {
					tx = 1;
					ty = 2;
				} else {
					int meta = blk & 0x0f;
					int upper = meta & 0x08;
					meta &= 0x07;
					block sblk = ((blk >> 4) << 4) | meta;
					float tx1[6]; // top, buttom, side, other three are for processing
					float tx2[6];
					float ty1[6];
					float ty2[6];
					if (sblk == BLK_STONESLAB) {
						getTextureCoordinates(8, 15, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						tx1[1] = tx1[0];
						tx2[1] = tx2[0];
						ty1[1] = ty1[0];
						ty2[1] = ty2[0];
						getTextureCoordinates(23, 11, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					} else if (sblk == BLK_SANDSTONESLAB) {
						getTextureCoordinates(27, 17, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						getTextureCoordinates(14, 5, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
						getTextureCoordinates(3, 21, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					} else if (sblk == BLK_WOODENSLAB) {
						getTextureCoordinates(30, 19, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						tx1[2] = tx1[1] = tx1[0];
						tx2[2] = tx2[1] = tx2[0];
						ty1[2] = ty1[1] = ty1[0];
						ty2[2] = ty2[1] = ty2[0];
					} else if (sblk == BLK_COBBLESTONESLAB) {
						getTextureCoordinates(19, 8, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						tx1[2] = tx1[1] = tx1[0];
						tx2[2] = tx2[1] = tx2[0];
						ty1[2] = ty1[1] = ty1[0];
						ty2[2] = ty2[1] = ty2[0];
					} else if (sblk == BLK_BRICKSLAB) {
						getTextureCoordinates(28, 14, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						tx1[2] = tx1[1] = tx1[0];
						tx2[2] = tx2[1] = tx2[0];
						ty1[2] = ty1[1] = ty1[0];
						ty2[2] = ty2[1] = ty2[0];
					} else if (sblk == BLK_STONEBRICKSLAB) {
						getTextureCoordinates(16, 11, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						tx1[2] = tx1[1] = tx1[0];
						tx2[2] = tx2[1] = tx2[0];
						ty1[2] = ty1[1] = ty1[0];
						ty2[2] = ty2[1] = ty2[0];
					} else if (sblk == BLK_NETHERBRICKSLAB) {
						getTextureCoordinates(3, 11, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						tx1[2] = tx1[1] = tx1[0];
						tx2[2] = tx2[1] = tx2[0];
						ty1[2] = ty1[1] = ty1[0];
						ty2[2] = ty2[1] = ty2[0];
					} else if (sblk == BLK_QUARTZSLAB) {
						getTextureCoordinates(28, 13, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						getTextureCoordinates(9, 18, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
						getTextureCoordinates(3, 15, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					} else if (sblk == BLK_OAK_WOODSLAB) {
						getTextureCoordinates(30, 19, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						tx1[2] = tx1[1] = tx1[0];
						tx2[2] = tx2[1] = tx2[0];
						ty1[2] = ty1[1] = ty1[0];
						ty2[2] = ty2[1] = ty2[0];
					} else if (sblk == BLK_SPRUCE_WOODSLAB) {
						getTextureCoordinates(20, 19, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						tx1[2] = tx1[1] = tx1[0];
						tx2[2] = tx2[1] = tx2[0];
						ty1[2] = ty1[1] = ty1[0];
						ty2[2] = ty2[1] = ty2[0];
					} else if (sblk == BLK_BIRCH_WOODSLAB) {
						getTextureCoordinates(27, 19, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						tx1[2] = tx1[1] = tx1[0];
						tx2[2] = tx2[1] = tx2[0];
						ty1[2] = ty1[1] = ty1[0];
						ty2[2] = ty2[1] = ty2[0];
					} else if (sblk == BLK_JUNGLE_WOODSLAB) {
						getTextureCoordinates(3, 2, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						tx1[2] = tx1[1] = tx1[0];
						tx2[2] = tx2[1] = tx2[0];
						ty1[2] = ty1[1] = ty1[0];
						ty2[2] = ty2[1] = ty2[0];
					} else if (sblk == BLK_ACACIAWOODSLAB) {
						getTextureCoordinates(25, 11, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						tx1[2] = tx1[1] = tx1[0];
						tx2[2] = tx2[1] = tx2[0];
						ty1[2] = ty1[1] = ty1[0];
						ty2[2] = ty2[1] = ty2[0];
					} else if (sblk == BLK_DARKOAKWOODSLAB) {
						getTextureCoordinates(9, 1, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						tx1[2] = tx1[1] = tx1[0];
						tx2[2] = tx2[1] = tx2[0];
						ty1[2] = ty1[1] = ty1[0];
						ty2[2] = ty2[1] = ty2[0];
					} else if (sblk == BLK_REDSANDSTONESLAB) {
						getTextureCoordinates(24, 2, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						getTextureCoordinates(24, 1, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
						getTextureCoordinates(14, 2, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
					} else if (sblk == BLK_PURPURSLAB) {
						getTextureCoordinates(6, 18, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
						tx1[2] = tx1[1] = tx1[0];
						tx2[2] = tx2[1] = tx2[0];
						ty1[2] = ty1[1] = ty1[0];
						ty2[2] = ty2[1] = ty2[0];
					} else {
						goto unimpl;
					}
					if (*vexs <= (*cvec * sizeof(struct vertex_tex)) + 6 * 4 * sizeof(struct vertex_tex)) {
						*vexs += 2048 * 4 * 6 * sizeof(struct vertex_tex);
						*vex = realloc(*vex, *vexs);
					}
					tx1[3] = tx1[4] = tx1[5] = tx1[2];
					ty1[3] = ty1[4] = ty1[5] = ty1[2];
					tx2[3] = tx2[4] = tx2[5] = tx2[2];
					ty2[3] = ty2[4] = ty2[5] = ty2[2] - (.5 / (float) def_wrap);
					createMultSub(.5, .25, .5, &((*vex)[*cvec]), x + 0.5, y + (upper ? .75 : .25), z + 0.5, 0xFF, tx1, ty1, tx2, ty2);
					*cvec += 6 * 4;
					return;
				}
				if (*vexs <= (*cvec * sizeof(struct vertex_tex)) + 4 * 4 * sizeof(struct vertex_tex)) {
					*vexs += 2048 * 4 * 6 * sizeof(struct vertex_tex);
					*vex = realloc(*vex, *vexs);
				}
				float tx1;
				float tx2;
				float ty1;
				float ty2;
				getTextureCoordinates(tx, ty, &tx1, &ty1, &tx2, &ty2);
				virtTexCoord2f(&(*vex)[*cvec], tx2, ty2);
				virtVertex3f(&(*vex)[(*cvec)++], x, y, z);
				virtTexCoord2f(&(*vex)[*cvec], tx2, ty1);
				virtVertex3f(&(*vex)[(*cvec)++], x, y + 1., z);
				virtTexCoord2f(&(*vex)[*cvec], tx1, ty1);
				virtVertex3f(&(*vex)[(*cvec)++], x + 1., y + 1., z + 1.);
				virtTexCoord2f(&(*vex)[*cvec], tx1, ty2);
				virtVertex3f(&(*vex)[(*cvec)++], x + 1., y, z + 1.);
				//
				virtTexCoord2f(&(*vex)[*cvec], tx2, ty2);
				virtVertex3f(&(*vex)[(*cvec)++], x + 1., y, z);
				virtTexCoord2f(&(*vex)[*cvec], tx2, ty1);
				virtVertex3f(&(*vex)[(*cvec)++], x + 1., y + 1., z);
				virtTexCoord2f(&(*vex)[*cvec], tx1, ty1);
				virtVertex3f(&(*vex)[(*cvec)++], x, y + 1., z + 1.);
				virtTexCoord2f(&(*vex)[*cvec], tx1, ty2);
				virtVertex3f(&(*vex)[(*cvec)++], x, y, z + 1.);
				//
				//
				virtTexCoord2f(&(*vex)[*cvec], tx2, ty2);
				virtVertex3f(&(*vex)[(*cvec)++], x + 1., y, z + 1.);
				virtTexCoord2f(&(*vex)[*cvec], tx2, ty1);
				virtVertex3f(&(*vex)[(*cvec)++], x + 1., y + 1., z + 1.);
				virtTexCoord2f(&(*vex)[*cvec], tx1, ty1);
				virtVertex3f(&(*vex)[(*cvec)++], x, y + 1., z);
				virtTexCoord2f(&(*vex)[*cvec], tx1, ty2);
				virtVertex3f(&(*vex)[(*cvec)++], x, y, z);
				//
				virtTexCoord2f(&(*vex)[*cvec], tx2, ty2);
				virtVertex3f(&(*vex)[(*cvec)++], x, y, z + 1.);
				virtTexCoord2f(&(*vex)[*cvec], tx2, ty1);
				virtVertex3f(&(*vex)[(*cvec)++], x, y + 1., z + 1.);
				virtTexCoord2f(&(*vex)[*cvec], tx1, ty1);
				virtVertex3f(&(*vex)[(*cvec)++], x + 1., y + 1., z);
				virtTexCoord2f(&(*vex)[*cvec], tx1, ty2);
				virtVertex3f(&(*vex)[(*cvec)++], x + 1., y, z);
				return;
			}
			if (*vexs <= (*cvec * sizeof(struct vertex_tex)) + fc * 4 * sizeof(struct vertex_tex)) {
				*vexs += 2048 * 4 * 6 * sizeof(struct vertex_tex);
				*vex = realloc(*vex, *vexs);
			}
			createMultSubCube(0.5, &((*vex)[*cvec]), x + 0.5, y + 0.5, z + 0.5, faceMask, tx1, ty1, tx2, ty2);
			*cvec += fc * 4;
			return;
		}
		if (tx >= 0 && ty >= 0) {
			float tx1 = 0.;
			float ty1 = 0.;
			float tx2 = 1.;
			float ty2 = 1.;
			if (*vexs <= (*cvec * sizeof(struct vertex_tex)) + fc * 4 * sizeof(struct vertex_tex)) {
				*vexs += 2048 * 4 * 6 * sizeof(struct vertex_tex);
				*vex = realloc(*vex, *vexs);
			}
			getTextureCoordinates(tx, ty, &tx1, &ty1, &tx2, &ty2);
			createSubCube(0.5, &((*vex)[*cvec]), x + 0.5, y + 0.5, z + 0.5, faceMask, tx1, ty1, tx2, ty2);
			*cvec += fc * 4;
		}
	}
}

int isBlockOpaque(block block) {
	int bs = block >> 4;
	bs <<= 4;
	return bs == BLK_STONE || bs == BLK_GRASS || bs == BLK_DIRT || bs == BLK_COBBLESTONE || bs == BLK_WOODENPLANKOAK || bs == BLK_BEDROCK || (bs >= BLK_SAND && bs <= BLK_WOODOAK) || bs == BLK_SPONGE || bs == BLK_WETSPONGE || (bs >= BLK_LAPISLAZULIORE && bs <= BLK_NOTEBLOCK) || bs == BLK_WOOL || bs == BLK_BLOCKOFGOLD || bs == BLK_BLOCKOFIRON || bs == BLK_STONESLABDOUBLE || bs == BLK_BRICK || bs == BLK_TNT || bs == BLK_BOOKSHELF || bs == BLK_MOSSSTONE || bs == BLK_OBSIDIAN || bs == BLK_DIAMONDORE || bs == BLK_BLOCKOFDIAMOND || bs == BLK_WORKBENCH || bs == BLK_FURNACE || bs == BLK_FURNACESMELTING || bs == BLK_REDSTONEORE || bs == BLK_REDSTONEOREGLOWING || bs == BLK_SNOWBLOCK || bs == BLK_CLAYBLOCK || bs == BLK_JUKEBOX || bs == BLK_PUMPKIN || bs == BLK_NETHERRACK || bs == BLK_SOULSAND || bs == BLK_GLOWSTONE || bs == BLK_JACK_O_LANTERN || bs == BLK_MONSTEREGGSTONE || bs == BLK_STONEBRICKS || bs == BLK_MELONBLOCK || bs == BLK_MYCELIUM || bs == BLK_NETHERBRICK || bs == BLK_ENDSTONE
			|| bs == BLK_REDSTONELAMP || bs == BLK_REDSTONELAMPON || bs == BLK_OAK_WOODSLABDOUBLE || bs == BLK_EMERALDORE || bs == BLK_BLOCKOFEMERALD || bs == BLK_COMMANDBLOCK || bs == BLK_BLOCKOFREDSTONE || bs == BLK_NETHERQUARTZORE || bs == BLK_QUARTZBLOCK || bs == BLK_DROPPER || bs == BLK_STAINEDCLAYWHITE || bs == BLK_DISPENSER || bs == BLK_WOODOAK || bs == BLK_WOODACACIAOAK || bs == BLK_PRISMARINE || bs == BLK_PRISMARINEBRICKS || bs == BLK_DARKPRISMARINE || bs == BLK_SEALANTERN || bs == BLK_HAYBALE || bs == BLK_HARDENEDCLAY || bs == BLK_BLOCKOFCOAL || bs == BLK_PACKEDICE || bs == BLK_REDSANDSTONE || bs == BLK_REDSANDSTONESLABDOUBLE || bs == BLK_PURPURBLOCK || bs == BLK_PURPURPILLAR || bs == BLK_PURPURSLABDOUBLE || bs == BLK_ENDSTONEBRICKS;
}

struct boundingbox bb_cube;
struct boundingbox bb_hcube;
struct boundingbox bb_hucube;

struct boundingbox* getBlockCollision(block block) {
	if (block == BLK_AIR || block >> 4 == BLK_TALLGRASSDEADSHRUB >> 4 || block >> 4 == BLK_SUNFLOWER_BOTTOM >> 4 || block >> 4 == BLK_REDMUSHROOM >> 4 || block >> 4 == BLK_POPPY >> 4 || block >> 4 == BLK_DANDELION >> 4) return NULL;
	if (block >> 4 == BLK_STONESLAB >> 4 || block >> 4 == BLK_OAK_WOODSLAB >> 4 || block >> 4 == BLK_REDSANDSTONESLAB >> 4 || block >> 4 == BLK_PURPURSLAB >> 4) {
		int meta = block & 0x0f;
		int upper = meta & 0x08;
		return upper ? &bb_hucube : &bb_hcube;
	}

	return &bb_cube;
}

void loadBlocks() {
	bb_cube.maxX = 1.;
	bb_cube.maxY = 1.;
	bb_cube.maxZ = 1.;
	bb_hcube.maxX = 1.;
	bb_hcube.maxY = .5;
	bb_hcube.maxZ = 1.;
	bb_hucube.minY = .5;
	bb_hucube.maxX = 1.;
	bb_hucube.maxY = 1.;
	bb_hucube.maxZ = 1.;
}
