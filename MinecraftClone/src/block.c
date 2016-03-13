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

void drawBlock(struct vertex_tex** vex, size_t* vexs, block block, unsigned char faceMask, float x, float y, float z) {
	//TODO: if not solid blah
	unsigned char fc = 0;
	if (faceMask & 0x01) fc++;
	if (faceMask & 0x02) fc++;
	if (faceMask & 0x04) fc++;
	if (faceMask & 0x08) fc++;
	if (faceMask & 0x10) fc++;
	if (faceMask & 0x20) fc++;
	if (*vex == NULL) {
		*vex = malloc(fc * 4 * sizeof(struct vertex_tex));
		*vexs = 0;
	} else {
		*vex = realloc(*vex, ((fc * 4) + *vexs) * sizeof(struct vertex_tex));
	}
	float tw = 1. / (float) def_wrap;
	float th = 1. / ((float) def_height / ((float) def_width / (float) def_wrap));
	float tx = 2.;
	float ty = 1.;
	if (block == BLK_GRASS) {

	} else if (block == BLK_PODZOL) {

	} else if (block == BLK_SAPLINGDARKOAK) {

	} else if (block == BLK_WATER) {

	} else if (block == BLK_WATERNOSPREAD) {

	} else if (block == BLK_LAVA) {

	} else if (block == BLK_LAVANOSPREAD) {

	} else if (block == BLK_WOODOAK) {

	} else if (block == BLK_WOODSPRUCE) {

	} else if (block == BLK_WOODBIRCH) {

	} else if (block == BLK_WOODJUNGLE) {

	} else if (block == BLK_WOODOAK4) {

	} else if (block == BLK_WOODOAK5) {

	} else if (block == BLK_WETSPONGE) {

	} else if (block == BLK_LAPISLAZULIORE) {

	} else if (block == BLK_LAPISLAZULIBLOCK) {

	} else if (block == BLK_DISPENSER) {

	} else if (block == BLK_SANDSTONE) {

	} else if (block == BLK_SANDSTONECHISELED) {

	} else if (block == BLK_BEDBLOCK) {

	} else if (block == BLK_RAILPOWERED) {

	} else if (block == BLK_STICKYPISTON) {

	} else if (block == BLK_COBWEB) {

	} else if (block == BLK_TALLGRASSDEADSHRUB) {

	} else if (block == BLK_TALLGRASSFERN) {

	} else if (block == BLK_DEADSHRUB) {

	} else if (block == BLK_PISTON) {

	} else if (block == BLK_PISTONHEAD) {

	} else if (block == BLK_WOOL) {

	} else if (block == BLK_ORANGEWOOL) {

	} else if (block == BLK_MAGENTAWOOL) {

	} else if (block == BLK_LIGHTBLUEWOOL) {

	} else if (block == BLK_YELLOWWOOL) {

	} else if (block == BLK_LIMEWOOL) {

	} else if (block == BLK_PINKWOOL) {

	} else if (block == BLK_GRAYWOOL) {

	} else if (block == BLK_LIGHTGRAYWOOL) {

	} else if (block == BLK_CYANWOOL) {

	} else if (block == BLK_PURPLEWOOL) {

	} else if (block == BLK_BLUEWOOL) {

	} else if (block == BLK_BROWNWOOL) {

	} else if (block == BLK_GREENWOOL) {

	} else if (block == BLK_REDWOOL) {

	} else if (block == BLK_BLACKWOOL) {

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

	} else if (block == BLK_BROWNMUSHROOM) {

	} else if (block == BLK_REDMUSHROOM) {

	} else if (block == BLK_BLOCKOFGOLD) {

	} else if (block == BLK_BLOCKOFIRON) {

	} else if (block == BLK_STONESLABDOUBLE) {

	} else if (block == BLK_SANDSTONESLABDOUBLE) {

	} else if (block == BLK_WOODENSLABDOUBLE) {

	} else if (block == BLK_COBBLESTONESLABDOUBLE) {

	} else if (block == BLK_BRICKSLABDOUBLE) {

	} else if (block == BLK_STONEBRICKSLABDOUBLE) {

	} else if (block == BLK_NETHERBRICKSLABDOUBLE) {

	} else if (block == BLK_QUARTZSLABDOUBLE) {

	} else if (block == BLK_SMOOTHSTONESLABDOUBLE) {

	} else if (block == BLK_SMOOTHSANDSTONESLABDOUBLE) {

	} else if (block == BLK_STONESLAB) {

	} else if (block == BLK_SANDSTONESLAB) {

	} else if (block == BLK_WOODENSLAB) {

	} else if (block == BLK_COBBLESTONESLAB) {

	} else if (block == BLK_BRICKSLAB) {

	} else if (block == BLK_STONEBRICKSLAB) {

	} else if (block == BLK_NETHERBRICKSLAB) {

	} else if (block == BLK_QUARTZSLAB) {

	} else if (block == BLK_TNT) {

	} else if (block == BLK_MOSSSTONE) {

	} else if (block == BLK_TORCH) {

	} else if (block == BLK_FIRE) {

	} else if (block == BLK_WOODENSTAIRSOAK) {

	} else if (block == BLK_CHEST) {

	} else if (block == BLK_REDSTONEWIRE) {

	} else if (block == BLK_BLOCKOFDIAMOND) {

	} else if (block == BLK_WORKBENCH) {

	} else if (block == BLK_WHEATCROP) {

	} else if (block == BLK_FARMLAND) {

	} else if (block == BLK_FURNACE) {

	} else if (block == BLK_FURNACESMELTING) {

	} else if (block == BLK_SIGNBLOCK) {

	} else if (block == BLK_WOODDOORBLOCK) {

	} else if (block == BLK_RAIL) {

	} else if (block == BLK_COBBLESTONESTAIRS) {

	} else if (block == BLK_SIGNWALLBLOCK) {

	} else if (block == BLK_STONEPRESSUREPLATE) {

	} else if (block == BLK_IRONDOORBLOCK) {

	} else if (block == BLK_WOODENPRESSUREPLATE) {

	} else if (block == BLK_REDSTONEOREGLOWING) {

	} else if (block == BLK_REDSTONETORCH) {

	} else if (block == BLK_BUTTONSTONE) {

	} else if (block == BLK_SNOWBLOCK) {

	} else if (block == BLK_CACTUS) {

	} else if (block == BLK_CLAYBLOCK) {

	} else if (block == BLK_SUGARCANEBLOCK) {

	} else if (block == BLK_JUKEBOX) {

	} else if (block == BLK_FENCEOAK) {

	} else if (block == BLK_PUMPKIN) {

	} else if (block == BLK_JACK_O_LANTERN) {

	} else if (block == BLK_CAKEBLOCK) {

	} else if (block == BLK_REDSTONEREPEATERBLOCKOFF) {

	} else if (block == BLK_REDSTONEREPEATERBLOCKON) {

	} else if (block == BLK_STAINEDGLASSWHITE) {

	} else if (block == BLK_STAINEDGLASSORANGE) {

	} else if (block == BLK_STAINEDGLASSMAGENTA) {

	} else if (block == BLK_STAINEDGLASSLIGHTBLUE) {

	} else if (block == BLK_STAINEDGLASSYELLOW) {

	} else if (block == BLK_STAINEDGLASSLIME) {

	} else if (block == BLK_STAINEDGLASSPINK) {

	} else if (block == BLK_STAINEDGLASSGRAY) {

	} else if (block == BLK_STAINEDGLASSLIGHTGREY) {

	} else if (block == BLK_STAINEDGLASSCYAN) {

	} else if (block == BLK_STAINEDGLASSPURPLE) {

	} else if (block == BLK_STAINEDGLASSBLUE) {

	} else if (block == BLK_STAINEDGLASSBROWN) {

	} else if (block == BLK_STAINEDGLASSGREEN) {

	} else if (block == BLK_STAINEDGLASSRED) {

	} else if (block == BLK_STAINEDGLASSBLACK) {

	} else if (block == BLK_MONSTEREGGSTONE) {

	} else if (block == BLK_MONSTEREGGCOBBLESTONE) {

	} else if (block == BLK_MONSTEREGGSTONEBRICK) {

	} else if (block == BLK_MONSTEREGGMOSSYSTONEBRICK) {

	} else if (block == BLK_MONSTEREGGCRACKEDSTONE) {

	} else if (block == BLK_MONSTEREGGCHISELEDSTONE) {

	} else if (block == BLK_STONEBRICKS) {

	} else if (block == BLK_MOSSYSTONEBRICKS) {

	} else if (block == BLK_CRACKEDSTONEBRICKS) {

	} else if (block == BLK_CHISELEDSTONEBRICK) {

	} else if (block == BLK_BROWNMUSHROOMBLOCK) {

	} else if (block == BLK_REDMUSHROOMBLOCK) {

	} else if (block == BLK_GLASSPANE) {

	} else if (block == BLK_MELONBLOCK) {

	} else if (block == BLK_PUMPKINVINE) {

	} else if (block == BLK_MELONVINE) {

	} else if (block == BLK_VINES) {

	} else if (block == BLK_FENCEGATEOAK) {

	} else if (block == BLK_BRICKSTAIRS) {

	} else if (block == BLK_STONEBRICKSTAIRS) {

	} else if (block == BLK_MYCELIUM) {

	} else if (block == BLK_LILYPAD) {

	} else if (block == BLK_NETHERBRICKFENCE) {

	} else if (block == BLK_NETHERBRICKSTAIRS) {

	} else if (block == BLK_NETHERWART) {

	} else if (block == BLK_ENCHANTMENTTABLE) {

	} else if (block == BLK_BREWINGSTANDBLOCK) {

	} else if (block == BLK_CAULDRONBLOCK) {

	} else if (block == BLK_ENDPORTAL) {

	} else if (block == BLK_ENDPORTALFRAME) {

	} else if (block == BLK_REDSTONELAMP) {

	} else if (block == BLK_OAK_WOODSLABDOUBLE) {

	} else if (block == BLK_SPRUCE_WOODSLABDOUBLE) {

	} else if (block == BLK_BIRCH_WOODSLABDOUBLE) {

	} else if (block == BLK_JUNGLE_WOODSLABDOUBLE) {

	} else if (block == BLK_ACACIAWOODSLABDOUBLE) {

	} else if (block == BLK_DARKOAKWOODSLABDOUBLE) {

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

	} else if (block == BLK_BLOCKOFEMERALD) {

	} else if (block == BLK_WOODENSTAIRSSPRUCE) {

	} else if (block == BLK_WOODENSTAIRSBIRCH) {

	} else if (block == BLK_WOODENSTAIRSJUNGLE) {

	} else if (block == BLK_COMMANDBLOCK) {

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

	} else if (block == BLK_BLOCKOFREDSTONE) {

	} else if (block == BLK_NETHERQUARTZORE) {

	} else if (block == BLK_HOPPER) {

	} else if (block == BLK_QUARTZBLOCK) {

	} else if (block == BLK_CHISELEDQUARTZBLOCK) {

	} else if (block == BLK_PILLARQUARTZBLOCK) {

	} else if (block == BLK_QUARTZSTAIRS) {

	} else if (block == BLK_DROPPER) {

	} else if (block == BLK_STAINEDCLAYWHITE) {

	} else if (block == BLK_STAINEDCLAYORANGE) {

	} else if (block == BLK_STAINEDCLAYMAGENTA) {

	} else if (block == BLK_STAINEDCLAYLIGHTBLUE) {

	} else if (block == BLK_STAINEDCLAYYELLOW) {

	} else if (block == BLK_STAINEDCLAYLIME) {

	} else if (block == BLK_STAINEDCLAYPINK) {

	} else if (block == BLK_STAINEDCLAYGRAY) {

	} else if (block == BLK_STAINEDCLAYLIGHTGRAY) {

	} else if (block == BLK_STAINEDCLAYCYAN) {

	} else if (block == BLK_STAINEDCLAYPURPLE) {

	} else if (block == BLK_STAINEDCLAYBLUE) {

	} else if (block == BLK_STAINEDCLAYBROWN) {

	} else if (block == BLK_STAINEDCLAYGREEN) {

	} else if (block == BLK_STAINEDCLAYRED) {

	} else if (block == BLK_STAINEDCLAYBLACK) {

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

	} else if (block == BLK_LEAVESDARKOAK) {

	} else if (block == BLK_WOODACACIAOAK) {

	} else if (block == BLK_WOODDARKOAK) {

	} else if (block == BLK_WOODENSTAIRSACACIA) {

	} else if (block == BLK_WOODENSTAIRSDARKOAK) {

	} else if (block == BLK_SLIMEBLOCK) {

	} else if (block == BLK_BARRIER) {

	} else if (block == BLK_PRISMARINE) {

	} else if (block == BLK_DARKPRISMARINE) {

	} else if (block == BLK_HAYBALE) {

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

	} else if (block == BLK_BLOCKOFCOAL) {

	} else if (block == BLK_PACKEDICE) {

	} else if (block == BLK_SUNFLOWER) {

	} else if (block == BLK_LILAC) {

	} else if (block == BLK_DOUBLETALLGRASS) {

	} else if (block == BLK_LARGEFERN) {

	} else if (block == BLK_ROSEBUSH) {

	} else if (block == BLK_PEONY) {

	} else if (block == BLK_STANDINGBANNERBLOCK) {

	} else if (block == BLK_WALLBANNERBLOCK) {

	} else if (block == BLK_INVERTEDDAYLIGHTSENSOR) {

	} else if (block == BLK_REDSANDSTONE) {

	} else if (block == BLK_REDSANDSTONECHISELED) {

	} else if (block == BLK_REDSANDSTONESTAIRS) {

	} else if (block == BLK_REDSANDSTONESLABDOUBLE) {

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

	} else if (block == BLK_PURPURSLABDOUBLE) {

	} else if (block == BLK_PURPURSLAB) {

	} else if (block == BLK_ENDSTONEBRICKS) {

	} else if (block == BLK_GRASSPATH) {

	} else if (block == BLK_ENDGATEWAY) {

	} else {
		if (block == BLK_AIR) {

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
		} else if (block == BLK_DIRT) {
			tx = 2;
			ty = 1;
		} else if (block == BLK_COARSEDIRT) {
			tx = 28;
			ty = 18;
		} else if (block == BLK_COBBLESTONE) {
			tx = 19;
			ty = 8;
		} else if (block == BLK_WOODENPLANKOAK) {
			tx = 30;
			ty = 19;
		} else if (block == BLK_WOODENPLANKSPRUCE) {
			tx = 20;
			ty = 19;
		} else if (block == BLK_WOODENPLANKBIRCH) {
			tx = 27;
			ty = 19;
		} else if (block == BLK_WOODENPLANKJUNGLE) {
			tx = 3;
			ty = 2;
		} else if (block == BLK_WOODENPLANKACACIA) {
			tx = 25;
			ty = 11;
		} else if (block == BLK_WOODENPLANKDARKOAK) {
			tx = 9;
			ty = 1;
		} else if (block == BLK_SAPLINGOAK) {
			tx = 16;
			ty = 0;
		} else if (block == BLK_SAPLINGSPRUCE) {
			tx = 0;
			ty = 10;
		} else if (block == BLK_SAPLINGBIRCH) {
			tx = 19;
			ty = 1;
		} else if (block == BLK_SAPLINGJUNGLE) {
			tx = 12;
			ty = 11;
		} else if (block == BLK_SAPLINGACACIA) {
			tx = 9;
			ty = 17;
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
		} else if (block == BLK_LEAVESOAK) {
			tx = 31;
			ty = 16;
		} else if (block == BLK_LEAVESSPRUCE) {
			tx = 4;
			ty = 9;
		} else if (block == BLK_LEAVESBIRCH) {
			tx = 28;
			ty = 2;
		} else if (block == BLK_LEAVESJUNGLE) {
			tx = 5;
			ty = 14;
		} else if (block == BLK_SPONGE) {
			tx = 6;
			ty = 9;
		} else if (block == BLK_GLASS) {
			tx = 18;
			ty = 15;
		} else if (block == BLK_SANDSTONESMOOTH) {
			tx = 8;
			ty = 17;
		} else if (block == BLK_NOTEBLOCK) {
			tx = 21;
			ty = 11;
		} else if (block == BLK_RAILDETECTOR) {
			tx = 24;
			ty = 18;
		} else if (block == BLK_TALLGRASS) {
			tx = 8;
			ty = 21;
		} else if (block == BLK_BRICK) {
			tx = 28;
			ty = 14;
		} else if (block == BLK_BOOKSHELF) {
			tx = 9;
			ty = 15;
		} else if (block == BLK_OBSIDIAN) {
			tx = 5;
			ty = 21;
		} else if (block == BLK_MOBSPAWNER) {
			tx = 18;
			ty = 19;
		} else if (block == BLK_DIAMONDORE) {
			tx = 19;
			ty = 7;
		} else if (block == BLK_LADDER) {
			tx = 23;
			ty = 8;
		} else if (block == BLK_LEVER) {
			tx = 26;
			ty = 16;
		} else if (block == BLK_REDSTONEORE) {
			tx = 2;
			ty = 9;
		} else if (block == BLK_REDSTONETORCHOFF) {
			tx = 30;
			ty = 18;
		} else if (block == BLK_SNOW) {
			tx = 7;
			ty = 9;
		} else if (block == BLK_ICE) {
			tx = 1;
			ty = 10;
		} else if (block == BLK_NETHERRACK) {
			tx = 9;
			ty = 2;
		} else if (block == BLK_SOULSAND) {
			tx = 0;
			ty = 21;
		} else if (block == BLK_GLOWSTONE) {
			tx = 8;
			ty = 7;
		} else if (block == BLK_PORTAL) {
			tx = 3;
			ty = 10;
		} else if (block == BLK_TRAPDOOR) {
			tx = 16;
			ty = 5;
		} else if (block == BLK_IRONBARS) {
			tx = 7;
			ty = 14;
		} else if (block == BLK_NETHERBRICK) {
			tx = 3;
			ty = 11;
		} else if (block == BLK_ENDSTONE) {
			tx = 31;
			ty = 2;
		} else if (block == BLK_DRAGONEGG) {
			tx = 26;
			ty = 2;
		} else if (block == BLK_REDSTONELAMPON) {
			tx = 17;
			ty = 15;
		} else if (block == BLK_EMERALDORE) {
			tx = 4;
			ty = 17;
		} else if (block == BLK_TRIPWIRE) {
			tx = 0;
			ty = 15;
		} else if (block == BLK_BEACON) {
			tx = 9;
			ty = 6;
		} else if (block == BLK_RAILACTIVATOR) {
			tx = 29;
			ty = 13;
		} else if (block == BLK_LEAVESACACIA) {
			tx = 28;
			ty = 17;
		} else if (block == BLK_IRONTRAPDOOR) {
			tx = 19;
			ty = 5;
		} else if (block == BLK_PRISMARINEBRICKS) {
			tx = 4;
			ty = 18;
		} else if (block == BLK_SEALANTERN) {
			tx = 19;
			ty = 2;
		} else if (block == BLK_HARDENEDCLAY) {
			tx = 31;
			ty = 5;
		} else if (block == BLK_REDSANDSTONESMOOTH) {
			tx = 26;
			ty = 8;
		} else if (block == BLK_ENDROD) {
			tx = 24;
			ty = 17;
		} else if (block == BLK_CHORUSPLANT) {
			tx = 11;
			ty = 15;
		} else if (block == BLK_CHORUSFLOWER) {
			tx = 7;
			ty = 21;
		} else if (block == BLK_PURPURBLOCK) {
			tx = 6;
			ty = 18;
		} else if (block == BLK_PURPURPILLAR) {
			tx = 27;
			ty = 8;
		} else if (block == BLK_STRUCTUREBLOCK) {
			tx = 5;
			ty = 18;
		}
	}
	createSubCube(0.5, &((*vex)[*vexs]), x + 0.5, y + 0.5, z + 0.5, faceMask, tw * tx, th * ty, tw * (tx + 1), th * (ty + 1));
	*vexs += fc * 4;
}

int isBlockOpaque(block block) {
	return block != BLK_AIR;
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
