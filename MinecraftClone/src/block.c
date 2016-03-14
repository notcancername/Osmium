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
	*tx1 = tw * tx;
	*ty1 = th * ty;
	*tx2 = tw * (tx + 1);
	*ty2 = th * (ty + 1);
}

void drawBlock(struct vertex_tex** vex, size_t* vexs, block block, unsigned char faceMask, float x, float y, float z) {
	//TODO: if not solid blah
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

	} else if (block == BLK_WOODOAK) {

	} else if (block == BLK_WOODSPRUCE) {

	} else if (block == BLK_WOODBIRCH) {

	} else if (block == BLK_WOODJUNGLE) {

	} else if (block == BLK_WOODOAK4) {

	} else if (block == BLK_WOODOAK5) {

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

	} else if (block == BLK_SANDSTONESMOOTH) {

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

	} else if (block == BLK_REDSANDSTONESMOOTH) {

	} else if (block == BLK_ENDROD) {

	} else if (block == BLK_CHORUSPLANT) {

	} else if (block == BLK_CHORUSFLOWER) {

	} else if (block == BLK_PURPURPILLAR) {

	} else if (block == BLK_STRUCTUREBLOCK) {

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
		} else if (block == BLK_COBBLESTONE) {
			tn = "cobblestone.png";
		} else if (block == BLK_WOODENPLANKOAK) {
			tn = "planks_oak.png";
		} else if (block == BLK_WOODENPLANKSPRUCE) {
			tn = "planks_spruce.png";
		} else if (block == BLK_WOODENPLANKBIRCH) {
			tn = "planks_birch.png";
		} else if (block == BLK_WOODENPLANKJUNGLE) {
			tn = "planks_jungle.png";
		} else if (block == BLK_WOODENPLANKACACIA) {
			tn = "planks_acacia.png";
		} else if (block == BLK_WOODENPLANKDARKOAK) {
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
		} else if (block == BLK_LEAVESOAK) {
			tn = "leaves_oak.png";
		} else if (block == BLK_LEAVESSPRUCE) {
			tn = "leaves_spruce.png";
		} else if (block == BLK_LEAVESBIRCH) {
			tn = "leaves_birch.png";
		} else if (block == BLK_LEAVESJUNGLE) {
			tn = "leaves_jungle.png";
		} else if (block == BLK_SPONGE) {
			tn = "sponge.png";
		} else if (block == BLK_WETSPONGE) {
			tn = "sponge_wet.png";
		} else if (block == BLK_GLASS) {
			tn = "glass.png";
		} else if (block == BLK_NOTEBLOCK) {
			tn = "noteblock.png";
		} else if (block == BLK_BRICK) {
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
		} else if (block == BLK_NETHERBRICK) {
			tn = "nether_brick.png";
		} else if (block == BLK_ENDSTONE) {
			tn = "end_stone.png";
		} else if (block == BLK_REDSTONELAMP) {
			tn = "redstone_lamp_off.png";
		} else if (block == BLK_REDSTONELAMPON) {
			tn = "redstone_lamp_on.png";
		} else if (block == BLK_EMERALDORE) {
			tn = "emerald_ore.png";
		} else if (block == BLK_LEAVESACACIA) {
			tn = "leaves_acacia.png";
		} else if (block == BLK_PRISMARINEBRICKS) {
			tn = "prismarine_bricks.png";
		} else if (block == BLK_SEALANTERN) {
			tn = "sea_lantern.png";
		} else if (block == BLK_HARDENEDCLAY) {
			tn = "hardened_clay.png";
		} else if (block == BLK_HARDENEDCLAY_ORANGE) {
			tn = "hardened_clay_orange.png";
		} else if (block == BLK_HARDENEDCLAY_MAGENTA) {
			tn = "hardened_clay_magenta.png";
		} else if (block == BLK_HARDENEDCLAY_LIGHTBLUE) {
			tn = "hardened_clay_lightblue.png";
		} else if (block == BLK_HARDENEDCLAY_YELLOW) {
			tn = "hardened_clay_yellow.png";
		} else if (block == BLK_HARDENEDCLAY_LIME) {
			tn = "hardened_clay_lime.png";
		} else if (block == BLK_HARDENEDCLAY_PINK) {
			tn = "hardened_clay_pink.png";
		} else if (block == BLK_HARDENEDCLAY_GRAY) {
			tn = "hardened_clay_gray.png";
		} else if (block == BLK_HARDENEDCLAY_LIGHTGRAY) {
			tn = "hardened_clay_lightgray.png";
		} else if (block == BLK_HARDENEDCLAY_CYAN) {
			tn = "hardened_clay_cyan.png";
		} else if (block == BLK_HARDENEDCLAY_PURPLE) {
			tn = "hardened_clay_purple.png";
		} else if (block == BLK_HARDENEDCLAY_BLUE) {
			tn = "hardened_clay_blue.png";
		} else if (block == BLK_HARDENEDCLAY_BROWN) {
			tn = "hardened_clay_brown.png";
		} else if (block == BLK_HARDENEDCLAY_GREEN) {
			tn = "hardened_clay_green.png";
		} else if (block == BLK_HARDENEDCLAY_RED) {
			tn = "hardened_clay_red.png";
		} else if (block == BLK_HARDENEDCLAY_BLACK) {
			tn = "hardened_clay_black.png";
		} else if (block == BLK_PURPURBLOCK) {
			tn = "purpur_block.png";
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
