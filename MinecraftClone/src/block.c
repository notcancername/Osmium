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

void drawBlock(struct vertex_tex** vex, size_t* vexs, size_t* cvec, block block, unsigned char faceMask, float x, float y, float z) {
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
	if (block == BLK_SAPLINGOAK) {
		goto unimpl;
	} else if (block == BLK_SAPLINGSPRUCE) {
		goto unimpl;
	} else if (block == BLK_SAPLINGBIRCH) {
		goto unimpl;
	} else if (block == BLK_SAPLINGJUNGLE) {
		goto unimpl;
	} else if (block == BLK_SAPLINGACACIA) {
		goto unimpl;
	} else if (block == BLK_SAPLINGDARKOAK) {
		goto unimpl;
	} else if (block == BLK_WATER) {
		goto unimpl;
	} else if (block == BLK_WATERNOSPREAD) {
		goto unimpl;
	} else if (block == BLK_LAVA) {
		goto unimpl;
	} else if (block == BLK_LAVANOSPREAD) {
		goto unimpl;
	} else if (block == BLK_RAILPOWERED) {
		goto unimpl;
	} else if (block == BLK_STICKYPISTON) {
		goto unimpl;
	} else if (block == BLK_COBWEB) {
		goto unimpl;
	} else if (block == BLK_TALLGRASSDEADSHRUB) {
		goto unimpl;
	} else if (block == BLK_TALLGRASSFERN) {
		goto unimpl;
	} else if (block == BLK_DEADSHRUB) {
		goto unimpl;
	} else if (block == BLK_PISTON) {
		goto unimpl;
	} else if (block == BLK_PISTONHEAD) {
		goto unimpl;
	} else if (block == BLK_PISTONMOVING) {
		goto unimpl;
	} else if (block == BLK_DANDELION) {
		goto unimpl;
	} else if (block == BLK_POPPY) {
		goto unimpl;
	} else if (block == BLK_BLUEORCHID) {
		goto unimpl;
	} else if (block == BLK_ALLIUM) {
		goto unimpl;
	} else if (block == BLK_AZUREBLUET) {
		goto unimpl;
	} else if (block == BLK_REDTULIP) {
		goto unimpl;
	} else if (block == BLK_ORANGETULIP) {
		goto unimpl;
	} else if (block == BLK_WHITETULIP) {
		goto unimpl;
	} else if (block == BLK_PINKTULIP) {
		goto unimpl;
	} else if (block == BLK_OXEYEDAISY) {
		goto unimpl;
	} else if (block == BLK_STONESLAB) {
		goto unimpl;
	} else if (block == BLK_SANDSTONESLAB) {
		goto unimpl;
	} else if (block == BLK_WOODENSLAB) {
		goto unimpl;
	} else if (block == BLK_COBBLESTONESLAB) {
		goto unimpl;
	} else if (block == BLK_BRICKSLAB) {
		goto unimpl;
	} else if (block == BLK_STONEBRICKSLAB) {
		goto unimpl;
	} else if (block == BLK_NETHERBRICKSLAB) {
		goto unimpl;
	} else if (block == BLK_QUARTZSLAB) {
		goto unimpl;
	} else if (block == BLK_TORCH) {
		goto unimpl;
	} else if (block == BLK_FIRE) {
		goto unimpl;
	} else if (block == BLK_WOODENSTAIRSOAK) {
		goto unimpl;
	} else if (block == BLK_CHEST) {
		goto unimpl;
	} else if (block == BLK_REDSTONEWIRE) {
		goto unimpl;
	} else if (block == BLK_WHEATCROP) {
		goto unimpl;
	} else if (block >> 4 == BLK_FARMLAND >> 4) {
		if (*vexs <= (*cvec * sizeof(struct vertex_tex)) + 6 * 4 * sizeof(struct vertex_tex)) {
			*vexs += 2048 * 4 * 6 * sizeof(struct vertex_tex);
			*vex = realloc(*vex, *vexs);
		}
		int meta = block & 0x0f;
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
	} else if (block == BLK_SIGNBLOCK) {
		goto unimpl;
	} else if (block == BLK_WOODDOORBLOCK) {
		goto unimpl;
	} else if (block == BLK_RAIL) {
		goto unimpl;
	} else if (block == BLK_COBBLESTONESTAIRS) {
		goto unimpl;
	} else if (block == BLK_SIGNWALLBLOCK) {
		goto unimpl;
	} else if (block == BLK_STONEPRESSUREPLATE) {
		goto unimpl;
	} else if (block == BLK_IRONDOORBLOCK) {
		goto unimpl;
	} else if (block == BLK_WOODENPRESSUREPLATE) {
		goto unimpl;
	} else if (block == BLK_REDSTONETORCH) {
		goto unimpl;
	} else if (block == BLK_BUTTONSTONE) {
		goto unimpl;
	} else if (block == BLK_CACTUS) {
		goto unimpl;
	} else if (block == BLK_SUGARCANEBLOCK) {
		goto unimpl;
	} else if (block == BLK_FENCEOAK) {
		goto unimpl;
	} else if (block == BLK_PUMPKIN) {
		goto unimpl;
	} else if (block == BLK_JACK_O_LANTERN) {
		goto unimpl;
	} else if (block == BLK_CAKEBLOCK) {
		goto unimpl;
	} else if (block == BLK_REDSTONEREPEATERBLOCKOFF) {
		goto unimpl;
	} else if (block == BLK_REDSTONEREPEATERBLOCKON) {
		goto unimpl;
	} else if (block == BLK_BROWNMUSHROOM) {
		goto unimpl;
	} else if (block == BLK_REDMUSHROOM) {
		goto unimpl;
	} else if (block == BLK_GLASSPANE) {
		goto unimpl;
	} else if (block == BLK_PUMPKINVINE) {
		goto unimpl;
	} else if (block == BLK_MELONVINE) {
		goto unimpl;
	} else if (block == BLK_VINES) {
		goto unimpl;
	} else if (block == BLK_FENCEGATEOAK) {
		goto unimpl;
	} else if (block == BLK_BRICKSTAIRS) {
		goto unimpl;
	} else if (block == BLK_STONEBRICKSTAIRS) {
		goto unimpl;
	} else if (block == BLK_LILYPAD) {
		goto unimpl;
	} else if (block == BLK_NETHERBRICKFENCE) {
		goto unimpl;
	} else if (block == BLK_NETHERBRICKSTAIRS) {
		goto unimpl;
	} else if (block == BLK_NETHERWART) {
		goto unimpl;
	} else if (block == BLK_ENCHANTMENTTABLE) {
		goto unimpl;
	} else if (block == BLK_BREWINGSTANDBLOCK) {
		goto unimpl;
	} else if (block == BLK_CAULDRONBLOCK) {
		goto unimpl;
	} else if (block == BLK_ENDPORTAL) {
		goto unimpl;
	} else if (block == BLK_ENDPORTALFRAME) {
		goto unimpl;
	} else if (block == BLK_OAK_WOODSLAB) {
		goto unimpl;
	} else if (block == BLK_SPRUCE_WOODSLAB) {
		goto unimpl;
	} else if (block == BLK_BIRCH_WOODSLAB) {
		goto unimpl;
	} else if (block == BLK_JUNGLE_WOODSLAB) {
		goto unimpl;
	} else if (block == BLK_ACACIAWOODSLAB) {
		goto unimpl;
	} else if (block == BLK_DARKOAKWOODSLAB) {
		goto unimpl;
	} else if (block == BLK_COCOAPLANT) {
		goto unimpl;
	} else if (block == BLK_SANDSTONESTAIRS) {
		goto unimpl;
	} else if (block == BLK_ENDERCHEST) {
		goto unimpl;
	} else if (block == BLK_TRIPWIREHOOK) {
		goto unimpl;
	} else if (block == BLK_WOODENSTAIRSSPRUCE) {
		goto unimpl;
	} else if (block == BLK_WOODENSTAIRSBIRCH) {
		goto unimpl;
	} else if (block == BLK_WOODENSTAIRSJUNGLE) {
		goto unimpl;
	} else if (block == BLK_COBBLESTONEWALL) {
		goto unimpl;
	} else if (block == BLK_MOSSYCOBBLESTONEWALL) {
		goto unimpl;
	} else if (block == BLK_FLOWERPOTBLOCK) {
		goto unimpl;
	} else if (block == BLK_CARROTCROP) {
		goto unimpl;
	} else if (block == BLK_POTATOESCROP) {
		goto unimpl;
	} else if (block == BLK_BUTTONWOOD) {
		goto unimpl;
	} else if (block == BLK_HEADBLOCKSKELETON) {
		goto unimpl;
	} else if (block == BLK_HEADBLOCKWITHER) {
		goto unimpl;
	} else if (block == BLK_HEADBLOCKZOMBIE) {
		goto unimpl;
	} else if (block == BLK_HEADBLOCKSTEVE) {
		goto unimpl;
	} else if (block == BLK_HEADBLOCKCREEPER) {
		goto unimpl;
	} else if (block == BLK_ANVIL) {
		goto unimpl;
	} else if (block == BLK_ANVILSLIGHTLYDAMAGED) {
		goto unimpl;
	} else if (block == BLK_ANVILVERYDAMAGED) {
		goto unimpl;
	} else if (block == BLK_TRAPPEDCHEST) {
		goto unimpl;
	} else if (block == BLK_WEIGHTEDPRESSUREPLATELIGHT) {
		goto unimpl;
	} else if (block == BLK_WEIGHTEDPRESSUREPLATEHEAVY) {
		goto unimpl;
	} else if (block == BLK_REDSTONECOMPARATOROFF) {
		goto unimpl;
	} else if (block == BLK_REDSTONECOMPARATORON) {
		goto unimpl;
	} else if (block == BLK_DAYLIGHTSENSOR) {
		goto unimpl;
	} else if (block == BLK_HOPPER) {
		goto unimpl;
	} else if (block == BLK_QUARTZSTAIRS) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANEWHITE) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANEORANGE) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANEMAGENTA) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANELIGHTBLUE) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANEYELLOW) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANELIME) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANEPINK) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANEGRAY) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANELIGHTGRAY) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANECYAN) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANEPURPLE) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANEBLUE) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANEBROWN) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANEGREEN) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANERED) {
		goto unimpl;
	} else if (block == BLK_STAINEDGLASSPANEBLACK) {
		goto unimpl;
	} else if (block == BLK_CARPETWHITE) {
		goto unimpl;
	} else if (block == BLK_CARPETORANGE) {
		goto unimpl;
	} else if (block == BLK_CARPETMAGENTA) {
		goto unimpl;
	} else if (block == BLK_CARPETLIGHTBLUE) {
		goto unimpl;
	} else if (block == BLK_CARPETYELLOW) {
		goto unimpl;
	} else if (block == BLK_CARPETLIME) {
		goto unimpl;
	} else if (block == BLK_CARPETPINK) {
		goto unimpl;
	} else if (block == BLK_CARPETGREY) {
		goto unimpl;
	} else if (block == BLK_CARPETLIGHTGRAY) {
		goto unimpl;
	} else if (block == BLK_CARPETCYAN) {
		goto unimpl;
	} else if (block == BLK_CARPETPURPLE) {
		goto unimpl;
	} else if (block == BLK_CARPETBLUE) {
		goto unimpl;
	} else if (block == BLK_CARPETBROWN) {
		goto unimpl;
	} else if (block == BLK_CARPETGREEN) {
		goto unimpl;
	} else if (block == BLK_CARPETRED) {
		goto unimpl;
	} else if (block == BLK_CARPETBLACK) {
		goto unimpl;
	} else if (block == BLK_SUNFLOWER) {
		goto unimpl;
	} else if (block == BLK_LILAC) {
		goto unimpl;
	} else if (block == BLK_DOUBLETALLGRASS) {
		goto unimpl;
	} else if (block == BLK_LARGEFERN) {
		goto unimpl;
	} else if (block == BLK_ROSEBUSH) {
		goto unimpl;
	} else if (block == BLK_PEONY) {
		goto unimpl;
	} else if (block == BLK_STANDINGBANNERBLOCK) {
		goto unimpl;
	} else if (block == BLK_WALLBANNERBLOCK) {
		goto unimpl;
	} else if (block == BLK_INVERTEDDAYLIGHTSENSOR) {
		goto unimpl;
	} else if (block == BLK_REDSANDSTONESTAIRS) {
		goto unimpl;
	} else if (block == BLK_REDSANDSTONESLAB) {
		goto unimpl;
	} else if (block == BLK_FENCEGATESPRUCE) {
		goto unimpl;
	} else if (block == BLK_FENCEGATEBIRCH) {
		goto unimpl;
	} else if (block == BLK_FENCEGATEJUNGLE) {
		goto unimpl;
	} else if (block == BLK_FENCEGATEDARKOAK) {
		goto unimpl;
	} else if (block == BLK_FENCEGATEACACIA) {
		goto unimpl;
	} else if (block == BLK_FENCESPRUCE) {
		goto unimpl;
	} else if (block == BLK_FENCEBIRCH) {
		goto unimpl;
	} else if (block == BLK_FENCEJUNGLE) {
		goto unimpl;
	} else if (block == BLK_FENCEDARKOAK) {
		goto unimpl;
	} else if (block == BLK_FENCEACACIA) {
		goto unimpl;
	} else if (block == BLK_WOODENDOORBLOCKSPRUCE) {
		goto unimpl;
	} else if (block == BLK_WOODENDOORBLOCKBIRCH) {
		goto unimpl;
	} else if (block == BLK_WOODENDOORBLOCKJUNGLE) {
		goto unimpl;
	} else if (block == BLK_WOODENDOORBLOCKACACIA) {
		goto unimpl;
	} else if (block == BLK_WOODENDOORBLOCKDARKOAK) {
		goto unimpl;
	} else if (block == BLK_PURPURSTAIRS) {
		goto unimpl;
	} else if (block == BLK_PURPURSLAB) {
		goto unimpl;
	} else if (block == BLK_ENDSTONEBRICKS) {
		goto unimpl;
	} else if (block == BLK_GRASSPATH) {
		goto unimpl;
	} else if (block == BLK_ENDGATEWAY) {
		goto unimpl;
	} else if (block == BLK_RAILDETECTOR) {
		goto unimpl;
	} else if (block == BLK_TALLGRASS) {
		goto unimpl;
	} else if (block == BLK_BOOKSHELF) {
		goto unimpl;
	} else if (block == BLK_LADDER) {
		goto unimpl;
	} else if (block == BLK_LEVER) {
		goto unimpl;
	} else if (block == BLK_REDSTONETORCHOFF) {
		goto unimpl;
	} else if (block == BLK_SNOW) {
		goto unimpl;
	} else if (block == BLK_PORTAL) {
		goto unimpl;
	} else if (block == BLK_TRAPDOOR) {
		goto unimpl;
	} else if (block == BLK_IRONBARS) {
		goto unimpl;
	} else if (block == BLK_DRAGONEGG) {
		goto unimpl;
	} else if (block == BLK_TRIPWIRE) {
		goto unimpl;
	} else if (block == BLK_BEACON) {
		goto unimpl;
	} else if (block == BLK_RAILACTIVATOR) {
		goto unimpl;
	} else if (block == BLK_IRONTRAPDOOR) {
		goto unimpl;
	} else if (block == BLK_ENDROD) {
		goto unimpl;
	} else if (block == BLK_CHORUSPLANT) {
		goto unimpl;
	} else if (block == BLK_CHORUSFLOWER) {
		goto unimpl;
	} else if (block == BLK_STRUCTUREBLOCK) {
		goto unimpl;
	} else if (block == BLK_BEDBLOCK) {
		goto unimpl;
	} else if (block == BLK_WOODENSTAIRSACACIA) {
		goto unimpl;
	} else if (block == BLK_WOODENSTAIRSDARKOAK) {
		goto unimpl;
	} else {
		int tx = -1;
		int ty = -1;
		if (block == BLK_AIR) {
			return;
		} else if (block == BLK_STONE) {
			tx = 31;
			ty = 13;
		} else if (block == BLK_GRANITE) {
			tx = 14;
			ty = 14;
		} else if (block == BLK_POLISHEDGRANITE) {
			tx = 9;
			ty = 7;
		} else if (block == BLK_DIORITE) {
			tx = 21;
			ty = 0;
		} else if (block == BLK_POLISHEDDIORITE) {
			tx = 13;
			ty = 17;
		} else if (block == BLK_ANDESITE) {
			tx = 3;
			ty = 14;
		} else if (block == BLK_POLISHEDANDESITE) {
			tx = 11;
			ty = 1;
		} else if (block == BLK_DIRT) {
			tx = 2;
			ty = 1;
		} else if (block == BLK_COARSEDIRT) {
			tx = 28;
			ty = 18;
		} else if (block == BLK_COBBLESTONE || block == BLK_COBBLESTONESLABDOUBLE) {
			tx = 19;
			ty = 8;
		} else if (block == BLK_WOODENPLANKOAK || block == BLK_WOODENSLABDOUBLE || block == BLK_OAK_WOODSLABDOUBLE) {
			tx = 30;
			ty = 19;
		} else if (block == BLK_WOODENPLANKSPRUCE || block == BLK_SPRUCE_WOODSLABDOUBLE) {
			tx = 20;
			ty = 19;
		} else if (block == BLK_WOODENPLANKBIRCH || block == BLK_BIRCH_WOODSLABDOUBLE) {
			tx = 27;
			ty = 19;
		} else if (block == BLK_WOODENPLANKJUNGLE || block == BLK_JUNGLE_WOODSLABDOUBLE) {
			tx = 3;
			ty = 2;
		} else if (block == BLK_WOODENPLANKACACIA || block == BLK_ACACIAWOODSLABDOUBLE) {
			tx = 25;
			ty = 11;
		} else if (block == BLK_WOODENPLANKDARKOAK || block == BLK_DARKOAKWOODSLABDOUBLE) {
			tx = 9;
			ty = 1;
		} else if (block == BLK_BEDROCK) {
			tx = 13;
			ty = 5;
		} else if (block == BLK_SAND) {
			tx = 23;
			ty = 17;
		} else if (block == BLK_REDSAND) {
			tx = 1;
			ty = 18;
		} else if (block == BLK_GRAVEL) {
			tx = 22;
			ty = 17;
		} else if (block == BLK_GOLDORE) {
			tx = 1;
			ty = 9;
		} else if (block == BLK_IRONORE) {
			tx = 13;
			ty = 0;
		} else if (block == BLK_COALORE) {
			tx = 22;
			ty = 5;
		} else if (block >> 4 == BLK_LEAVESOAK >> 4) {
			int meta = block & 0x0f;
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
		} else if (block == BLK_SPONGE) {
			tx = 6;
			ty = 9;
		} else if (block == BLK_WETSPONGE) {
			tx = 0;
			ty = 14;
		} else if (block == BLK_GLASS) {
			tx = 18;
			ty = 15;
		} else if (block == BLK_NOTEBLOCK) {
			tx = 21;
			ty = 11;
		} else if (block == BLK_BRICK || block == BLK_BRICKSLABDOUBLE) {
			tx = 28;
			ty = 14;
		} else if (block == BLK_OBSIDIAN) {
			tx = 5;
			ty = 21;
		} else if (block == BLK_MOBSPAWNER) {
			tx = 18;
			ty = 19;
		} else if (block == BLK_DIAMONDORE) {
			tx = 19;
			ty = 7;
		} else if (block == BLK_REDSTONEORE) { //TODO: activated
			tx = 2;
			ty = 9;
		} else if (block == BLK_ICE) {
			tx = 1;
			ty = 10;
		} else if (block == BLK_NETHERRACK) {
			tx = 9;
			ty = 2;
		} else if (block == BLK_SOULSAND) {
			tx = 9;
			ty = 2;
		} else if (block == BLK_GLOWSTONE) {
			tx = 0;
			ty = 21;
		} else if (block == BLK_NETHERBRICK || block == BLK_NETHERBRICKSLABDOUBLE) {
			tx = 3;
			ty = 11;
		} else if (block == BLK_ENDSTONE) {
			tx = 31;
			ty = 2;
		} else if (block == BLK_REDSTONELAMP) {
			tx = 17;
			ty = 18;
		} else if (block == BLK_REDSTONELAMPON) {
			tx = 17;
			ty = 15;
		} else if (block == BLK_EMERALDORE) {
			tx = 4;
			ty = 17;
		} else if (block == BLK_PRISMARINEBRICKS) {
			tx = 4;
			ty = 18;
		} else if (block == BLK_SEALANTERN) {
			tx = 19;
			ty = 2;
		} else if (block == BLK_HARDENEDCLAY) {
			tx = 31;
			ty = 5;
		} else if (block == BLK_HARDENEDCLAY_ORANGE) {
			tx = 22;
			ty = 9;
		} else if (block == BLK_HARDENEDCLAY_MAGENTA) {
			tx = 5;
			ty = 1;
		} else if (block == BLK_HARDENEDCLAY_LIGHTBLUE) {
			tx = 18;
			ty = 7;
		} else if (block == BLK_HARDENEDCLAY_YELLOW) {
			tx = 21;
			ty = 18;
		} else if (block == BLK_HARDENEDCLAY_LIME) {
			tx = 6;
			ty = 3;
		} else if (block == BLK_HARDENEDCLAY_PINK) {
			tx = 5;
			ty = 15;
		} else if (block == BLK_HARDENEDCLAY_GRAY) {
			tx = 26;
			ty = 11;
		} else if (block == BLK_HARDENEDCLAY_LIGHTGRAY) {
			tx = 21;
			ty = 14;
		} else if (block == BLK_HARDENEDCLAY_CYAN) {
			tx = 19;
			ty = 11;
		} else if (block == BLK_HARDENEDCLAY_PURPLE) {
			tx = 20;
			ty = 5;
		} else if (block == BLK_HARDENEDCLAY_BLUE) {
			tx = 18;
			ty = 8;
		} else if (block == BLK_HARDENEDCLAY_BROWN) {
			tx = 12;
			ty = 9;
		} else if (block == BLK_HARDENEDCLAY_GREEN) {
			tx = 2;
			ty = 15;
		} else if (block == BLK_HARDENEDCLAY_RED) {
			tx = 16;
			ty = 2;
		} else if (block == BLK_HARDENEDCLAY_BLACK) {
			tx = 5;
			ty = 19;
		} else if (block == BLK_PURPURBLOCK || block == BLK_PURPURSLABDOUBLE) {
			tx = 6;
			ty = 18;
		} else if (block == BLK_LAPISLAZULIORE) {
			tx = 6;
			ty = 19;
		} else if (block == BLK_LAPISLAZULIBLOCK) {
			tx = 31;
			ty = 18;
		} else if (block == BLK_WOOL) {
			tx = 10;
			ty = 19;
		} else if (block == BLK_ORANGEWOOL) {
			tx = 23;
			ty = 19;
		} else if (block == BLK_MAGENTAWOOL) {
			tx = 19;
			ty = 6;
		} else if (block == BLK_LIGHTBLUEWOOL) {
			tx = 29;
			ty = 5;
		} else if (block == BLK_YELLOWWOOL) {
			tx = 12;
			ty = 18;
		} else if (block == BLK_LIMEWOOL) {
			tx = 11;
			ty = 7;
		} else if (block == BLK_PINKWOOL) {
			tx = 19;
			ty = 18;
		} else if (block == BLK_GRAYWOOL) {
			tx = 31;
			ty = 19;
		} else if (block == BLK_LIGHTGRAYWOOL) {
			tx = 22;
			ty = 1;
		} else if (block == BLK_CYANWOOL) {
			tx = 14;
			ty = 0;
		} else if (block == BLK_PURPLEWOOL) {
			tx = 26;
			ty = 5;
		} else if (block == BLK_BLUEWOOL) {
			tx = 21;
			ty = 5;
		} else if (block == BLK_BROWNWOOL) {
			tx = 21;
			ty = 8;
		} else if (block == BLK_GREENWOOL) {
			tx = 29;
			ty = 16;
		} else if (block == BLK_REDWOOL) {
			tx = 25;
			ty = 18;
		} else if (block == BLK_BLACKWOOL) {
			tx = 24;
			ty = 16;
		} else if (block == BLK_BLOCKOFGOLD) {
			tx = 15;
			ty = 15;
		} else if (block == BLK_BLOCKOFIRON) {
			tx = 8;
			ty = 9;
		} else if (block == BLK_MOSSSTONE) {
			tx = 21;
			ty = 19;
		} else if (block == BLK_BLOCKOFDIAMOND) {
			tx = 15;
			ty = 9;
		} else if (block == BLK_REDSTONEOREGLOWING) {
			tx = 2;
			ty = 9;
			// TODO glow effect?
		} else if (block == BLK_SNOWBLOCK) {
			tx = 7;
			ty = 9;
		} else if (block == BLK_CLAYBLOCK) {
			tx = 1;
			ty = 1;
		} else if (block == BLK_STAINEDGLASSWHITE) {
			tx = 18;
			ty = 15;
		} else if (block == BLK_STAINEDGLASSORANGE) {
			tx = 26;
			ty = 17;
		} else if (block == BLK_STAINEDGLASSMAGENTA) {
			tx = 12;
			ty = 5;
		} else if (block == BLK_STAINEDGLASSLIGHTBLUE) {
			tx = 5;
			ty = 11;
		} else if (block == BLK_STAINEDGLASSYELLOW) {
			tx = 0;
			ty = 7;
		} else if (block == BLK_STAINEDGLASSLIME) {
			tx = 31;
			ty = 6;
		} else if (block == BLK_STAINEDGLASSPINK) {
			tx = 18;
			ty = 6;
		} else if (block == BLK_STAINEDGLASSGRAY) {
			tx = 27;
			ty = 7;
		} else if (block == BLK_STAINEDGLASSLIGHTGREY) {
			tx = 29;
			ty = 2;
		} else if (block == BLK_STAINEDGLASSCYAN) {
			tx = 24;
			ty = 0;
		} else if (block == BLK_STAINEDGLASSPURPLE) {
			tx = 25;
			ty = 2;
		} else if (block == BLK_STAINEDGLASSBLUE) {
			tx = 17;
			ty = 21;
		} else if (block == BLK_STAINEDGLASSBROWN) {
			tx = 16;
			ty = 15;
		} else if (block == BLK_STAINEDGLASSGREEN) {
			tx = 13;
			ty = 14;
		} else if (block == BLK_STAINEDGLASSRED) {
			tx = 10;
			ty = 0;
		} else if (block == BLK_STAINEDGLASSBLACK) {
			tx = 26;
			ty = 9;
		} else if (block == BLK_MONSTEREGGSTONE) {
			tx = 31;
			ty = 13;
		} else if (block == BLK_MONSTEREGGCOBBLESTONE) {
			tx = 19;
			ty = 8;
		} else if (block == BLK_MONSTEREGGSTONEBRICK) {
			tx = 16;
			ty = 11;
		} else if (block == BLK_MONSTEREGGMOSSYSTONEBRICK) {
			tx = 11;
			ty = 18;
		} else if (block == BLK_MONSTEREGGCRACKEDSTONE) {
			tx = 6;
			ty = 1;
		} else if (block == BLK_MONSTEREGGCHISELEDSTONE) {
			tx = 8;
			ty = 4;
		} else if (block == BLK_STONEBRICKS || block == BLK_STONEBRICKSLABDOUBLE) {
			tx = 16;
			ty = 11;
		} else if (block == BLK_MOSSYSTONEBRICKS) {
			tx = 11;
			ty = 18;
		} else if (block == BLK_CRACKEDSTONEBRICKS) {
			tx = 6;
			ty = 1;
		} else if (block == BLK_CHISELEDSTONEBRICK) {
			tx = 8;
			ty = 4;
		} else if (block == BLK_BLOCKOFEMERALD) {
			tx = 30;
			ty = 2;
		} else if (block == BLK_BLOCKOFREDSTONE) {
			tx = 27;
			ty = 14;
		} else if (block == BLK_NETHERQUARTZORE) {
			tx = 10;
			ty = 9;
		} else if (block == BLK_STAINEDCLAYWHITE) {
			tx = 20;
			ty = 11;
		} else if (block == BLK_STAINEDCLAYORANGE) {
			tx = 22;
			ty = 9;
		} else if (block == BLK_STAINEDCLAYMAGENTA) {
			tx = 5;
			ty = 1;
		} else if (block == BLK_STAINEDCLAYLIGHTBLUE) {
			tx = 18;
			ty = 7;
		} else if (block == BLK_STAINEDCLAYYELLOW) {
			tx = 21;
			ty = 18;
		} else if (block == BLK_STAINEDCLAYLIME) {
			tx = 6;
			ty = 3;
		} else if (block == BLK_STAINEDCLAYPINK) {
			tx = 5;
			ty = 15;
		} else if (block == BLK_STAINEDCLAYGRAY) {
			tx = 26;
			ty = 11;
		} else if (block == BLK_STAINEDCLAYLIGHTGRAY) {
			tx = 21;
			ty = 14;
		} else if (block == BLK_STAINEDCLAYCYAN) {
			tx = 19;
			ty = 11;
		} else if (block == BLK_STAINEDCLAYPURPLE) {
			tx = 20;
			ty = 5;
		} else if (block == BLK_STAINEDCLAYBLUE) {
			tx = 18;
			ty = 8;
		} else if (block == BLK_STAINEDCLAYBROWN) {
			tx = 12;
			ty = 9;
		} else if (block == BLK_STAINEDCLAYGREEN) {
			tx = 2;
			ty = 15;
		} else if (block == BLK_STAINEDCLAYRED) {
			tx = 16;
			ty = 2;
		} else if (block == BLK_STAINEDCLAYBLACK) {
			tx = 5;
			ty = 19;
		} else if (block >> 4 == BLK_LEAVESDARKOAK >> 4) {
			int meta = block & 0x0f;
			if (meta & 0x01) {
				tx = 28;
				ty = 16;
			} else {
				tx = 28;
				ty = 17;
			}

		} else if (block == BLK_SLIMEBLOCK) {
			tx = 2;
			ty = 19;
		} else if (block == BLK_BARRIER) {
			return;
		} else if (block == BLK_PRISMARINE) {
			tx = 15;
			ty = 14; //TODO: random textures
		} else if (block == BLK_DARKPRISMARINE) {
			tx = 9;
			ty = 9;
		} else if (block == BLK_BLOCKOFCOAL) {
			tx = 5;
			ty = 0;
		} else if (block == BLK_PACKEDICE) {
			tx = 27;
			ty = 1;
		} else if (block == BLK_SMOOTHSTONESLABDOUBLE) {
			tx = 8;
			ty = 15;
		} else if (tx == -1 && ty == -1) {
			float tx1[6];
			float ty1[6];
			float tx2[6];
			float ty2[6];
			if (block == BLK_GRASS) {
				getTextureCoordinates(28, 9, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(2, 1, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(6, 2, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_PODZOL) {
				getTextureCoordinates(21, 1, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(2, 1, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(24, 19, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_MYCELIUM) {
				getTextureCoordinates(3, 18, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(2, 1, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(30, 16, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block >> 4 == BLK_WOODOAK >> 4) {
				int meta = block & 0x0f;
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
			} else if (block >> 4 == BLK_WOODACACIAOAK >> 4) {
				int meta = block & 0x0f;
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
			} else if (block >> 4 == BLK_DISPENSER >> 4) {
				int meta = block & 0x0f;
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
			} else if (block == BLK_SANDSTONE || block == BLK_SANDSTONESLABDOUBLE) {
				getTextureCoordinates(27, 17, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(14, 5, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(3, 21, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_PURPURPILLAR) {
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
			} else if (block == BLK_SANDSTONECHISELED) {
				getTextureCoordinates(27, 17, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(14, 5, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(7, 0, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_SANDSTONESMOOTH || block == BLK_SMOOTHSANDSTONESLABDOUBLE) {
				getTextureCoordinates(27, 17, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(14, 5, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(8, 17, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_STONESLABDOUBLE) {
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
			} else if (block == BLK_TNT) {
				getTextureCoordinates(0, 2, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(21, 15, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(13, 21, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_WORKBENCH) {
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
			} else if (block >> 4 == BLK_FURNACE >> 4) {
				int dir = (block & 0x0f) & 0x07;
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
			} else if (block >> 4 == BLK_FURNACESMELTING >> 4) {
				int dir = (block & 0x0f) & 0x07;
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
			} else if (block == BLK_JUKEBOX) {
				getTextureCoordinates(7, 2, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(8, 19, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
				ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
				tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
				ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1];
			} else if (block >> 4 == BLK_BROWNMUSHROOMBLOCK >> 4 || block >> 4 == BLK_REDMUSHROOMBLOCK >> 4) {
				int txcx = (block >> 4) == (BLK_BROWNMUSHROOMBLOCK >> 4) ? 20 : 22;
				int txcy = (block >> 4) == (BLK_BROWNMUSHROOMBLOCK >> 4) ? 17 : 19;
				int meta = block & 0x0f;
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
			} else if (block == BLK_MELONBLOCK) {
				getTextureCoordinates(20, 14, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(9, 21, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
				ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
				tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
				ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1];
			} else if (block == BLK_COMMANDBLOCK) {
				return; // TODO:
			} else if (block == BLK_QUARTZBLOCK || block == BLK_QUARTZSLABDOUBLE) {
				getTextureCoordinates(28, 13, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(9, 18, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(3, 15, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_CHISELEDQUARTZBLOCK) {
				getTextureCoordinates(10, 4, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(15, 5, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
				ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
				tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
				ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1];
			} else if (block == BLK_PILLARQUARTZBLOCK) {
				getTextureCoordinates(23, 15, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(2, 17, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2] = tx1[1];
				ty1[3] = ty1[4] = ty1[5] = ty1[2] = ty1[1];
				tx2[3] = tx2[4] = tx2[5] = tx2[2] = tx2[1];
				ty2[3] = ty2[4] = ty2[5] = ty2[2] = ty2[1];
			} else if (block == BLK_DROPPER) {
				int meta = block & 0x0f;
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
			} else if (block == BLK_HAYBALE) {
				int meta = block & 0x0f;
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
			} else if (block == BLK_REDSANDSTONE || block == BLK_REDSANDSTONESLABDOUBLE) {
				getTextureCoordinates(24, 2, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(24, 1, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(14, 2, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_REDSANDSTONECHISELED) {
				getTextureCoordinates(24, 2, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(24, 1, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(25, 0, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else if (block == BLK_REDSANDSTONESMOOTH) {
				getTextureCoordinates(24, 2, &tx1[0], &ty1[0], &tx2[0], &ty2[0]);
				getTextureCoordinates(24, 1, &tx1[1], &ty1[1], &tx2[1], &ty2[1]);
				getTextureCoordinates(26, 8, &tx1[2], &ty1[2], &tx2[2], &ty2[2]);
				tx1[3] = tx1[4] = tx1[5] = tx1[2];
				ty1[3] = ty1[4] = ty1[5] = ty1[2];
				tx2[3] = tx2[4] = tx2[5] = tx2[2];
				ty2[3] = ty2[4] = ty2[5] = ty2[2];
			} else {
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
