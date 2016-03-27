/*
 * inventory.c
 *
 *  Created on: Mar 25, 2016
 *      Author: root
 */

#include "inventory.h"
#include "globals.h"
#include "models.h"
#include <GL/gl.h>
#include "gui.h"
#include "render.h"
#include "item.h"
#include "network.h"
#include "ingame.h"
#include <string.h>
#include <math.h>

void newInventory(struct inventory* inv, int type, int id) {
	inv->title = NULL;
	inv->slots = NULL;
	inv->slot_count = 0;
	inv->props = NULL;
	inv->prop_count = 0;
	inv->type = type;
	inv->windowID = id;
	inv->desync = -1;
}

void _freeInventorySlots(struct inventory* inv) {
	if (inv->slots != NULL) {
		for (size_t i = 0; i < inv->slot_count; i++) {
			if (inv->slots[i] == NULL) continue;
			if (inv->slots[i]->nbt != NULL) {
				freeNBT(inv->slots[i]->nbt);
				free(inv->slots[i]->nbt);
			}
			free(inv->slots[i]);
		}
		free(inv->slots);
		inv->slots = NULL;
	}
}

void freeInventory(struct inventory* inv) {
	if (inv->title != NULL) free(inv->title);
	if (inv->props != NULL) {
		for (size_t i = 0; i < inv->prop_count; i++) {
			free(inv->props[i]);
		}
		free(inv->props);
	}
	_freeInventorySlots(inv);
}

void loadInventoryGUI() {
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/gui/container/inventory.png", TX_IV_INVENTORY, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/gui/container/generic_54.png", TX_IV_CHEST, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/gui/container/crafting_table.png", TX_IV_WORKBENCH, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/gui/container/furnace.png", TX_IV_FURNACE, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/gui/container/dispenser.png", TX_IV_DISPENSER, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/gui/container/enchanting_table.png", TX_IV_ENCHANTINGTABLE, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/gui/container/brewing_stand.png", TX_IV_BREWINGSTAND, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/gui/container/villager.png", TX_IV_VILLAGER, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/gui/container/beacon.png", TX_IV_BEACON, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/gui/container/anvil.png", TX_IV_ANVIL, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/gui/container/hopper.png", TX_IV_HOPPER, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/gui/container/horse.png", TX_IV_HORSE, 1);
	idef_wrap = 32;
	itemMapLength = 339;
	itemMap = malloc(sizeof(char*) * 339);
	itemMap[0] = "diamond_axe.png";
	itemMap[1] = "potion_bottle_splash.png";
	itemMap[2] = "potion_bottle_lingering.png";
	itemMap[3] = "record_ward.png";
	itemMap[4] = "clock_63.png";
	itemMap[5] = "diamond_shovel.png";
	itemMap[6] = "melon_speckled.png";
	itemMap[7] = "compass_24.png";
	itemMap[8] = "porkchop_cooked.png";
	itemMap[9] = "chainmail_leggings.png";
	itemMap[10] = "charcoal.png";
	itemMap[11] = "clock_52.png";
	itemMap[12] = "bow_pulling_1.png";
	itemMap[13] = "rabbit_cooked.png";
	itemMap[14] = "carrot_golden.png";
	itemMap[15] = "clock_46.png";
	itemMap[16] = "clock_50.png";
	itemMap[17] = "leather.png";
	itemMap[18] = "diamond_sword.png";
	itemMap[19] = "seeds_pumpkin.png";
	itemMap[20] = "minecart_furnace.png";
	itemMap[21] = "leather_boots.png";
	itemMap[22] = "clock_54.png";
	itemMap[23] = "chorus_fruit_popped.png";
	itemMap[24] = "clock_37.png";
	itemMap[25] = "saddle.png";
	itemMap[26] = "clock_39.png";
	itemMap[27] = "clock_19.png";
	itemMap[28] = "clock_24.png";
	itemMap[29] = "prismarine_shard.png";
	itemMap[30] = "iron_axe.png";
	itemMap[31] = "beetroot_seeds.png";
	itemMap[32] = "compass_14.png";
	itemMap[33] = "clock_25.png";
	itemMap[34] = "clock_14.png";
	itemMap[35] = "gold_chestplate.png";
	itemMap[36] = "compass_26.png";
	itemMap[37] = "spectral_arrow.png";
	itemMap[38] = "gold_axe.png";
	itemMap[39] = "clock_47.png";
	itemMap[40] = "diamond.png";
	itemMap[41] = "wood_shovel.png";
	itemMap[42] = "empty_armor_slot_boots.png";
	itemMap[43] = "book_normal.png";
	itemMap[44] = "leather_boots_overlay.png";
	itemMap[45] = "door_dark_oak.png";
	itemMap[46] = "flint_and_steel.png";
	itemMap[47] = "fireworks.png";
	itemMap[48] = "rotten_flesh.png";
	itemMap[49] = "bucket_empty.png";
	itemMap[50] = "clock_27.png";
	itemMap[51] = "bucket_lava.png";
	itemMap[52] = "compass_16.png";
	itemMap[53] = "fish_clownfish_raw.png";
	itemMap[54] = "fireball.png";
	itemMap[55] = "leather_leggings_overlay.png";
	itemMap[56] = "compass_04.png";
	itemMap[57] = "ruby.png";
	itemMap[58] = "mutton_raw.png";
	itemMap[59] = "compass_09.png";
	itemMap[60] = "spruce_boat.png";
	itemMap[61] = "wood_sword.png";
	itemMap[62] = "record_blocks.png";
	itemMap[63] = "clock_59.png";
	itemMap[64] = "wooden_armorstand.png";
	itemMap[65] = "apple.png";
	itemMap[66] = "clock_20.png";
	itemMap[67] = "book_written.png";
	itemMap[68] = "stone_axe.png";
	itemMap[69] = "iron_boots.png";
	itemMap[70] = "compass_25.png";
	itemMap[71] = "clock_06.png";
	itemMap[72] = "dye_powder_black.png";
	itemMap[73] = "compass_10.png";
	itemMap[74] = "shears.png";
	itemMap[75] = "wood_axe.png";
	itemMap[76] = "record_wait.png";
	itemMap[77] = "clock_04.png";
	itemMap[78] = "compass_07.png";
	itemMap[79] = "gold_pickaxe.png";
	itemMap[80] = "gold_shovel.png";
	itemMap[81] = "compass_05.png";
	itemMap[82] = "compass_31.png";
	itemMap[83] = "dye_powder_magenta.png";
	itemMap[84] = "fish_cod_raw.png";
	itemMap[85] = "clock_56.png";
	itemMap[86] = "compass_23.png";
	itemMap[87] = "record_far.png";
	itemMap[88] = "comparator.png";
	itemMap[89] = "gold_leggings.png";
	itemMap[90] = "dragon_breath.png";
	itemMap[91] = "clock_10.png";
	itemMap[92] = "clay_ball.png";
	itemMap[93] = "clock_41.png";
	itemMap[94] = "leather_chestplate.png";
	itemMap[95] = "name_tag.png";
	itemMap[96] = "clock_18.png";
	itemMap[97] = "emerald.png";
	itemMap[98] = "iron_chestplate.png";
	itemMap[99] = "carrot.png";
	itemMap[100] = "seeds_wheat.png";
	itemMap[101] = "book_enchanted.png";
	itemMap[102] = "fish_cod_cooked.png";
	itemMap[103] = "iron_sword.png";
	itemMap[104] = "clock_44.png";
	itemMap[105] = "dye_powder_lime.png";
	itemMap[106] = "netherbrick.png";
	itemMap[107] = "fish_pufferfish_raw.png";
	itemMap[108] = "clock_38.png";
	itemMap[109] = "door_birch.png";
	itemMap[110] = "wheat.png";
	itemMap[111] = "gold_sword.png";
	itemMap[112] = "minecart_chest.png";
	itemMap[113] = "clock_45.png";
	itemMap[114] = "door_acacia.png";
	itemMap[115] = "gold_hoe.png";
	itemMap[116] = "compass_27.png";
	itemMap[117] = "clock_43.png";
	itemMap[118] = "beetroot_soup.png";
	itemMap[119] = "blaze_rod.png";
	itemMap[120] = "dye_powder_brown.png";
	itemMap[121] = "compass_22.png";
	itemMap[122] = "potato.png";
	itemMap[123] = "empty_armor_slot_chestplate.png";
	itemMap[124] = "dye_powder_silver.png";
	itemMap[125] = "clock_57.png";
	itemMap[126] = "dye_powder_red.png";
	itemMap[127] = "record_13.png";
	itemMap[128] = "rabbit_hide.png";
	itemMap[129] = "compass_13.png";
	itemMap[130] = "prismarine_crystals.png";
	itemMap[131] = "compass_12.png";
	itemMap[132] = "compass_06.png";
	itemMap[133] = "record_mellohi.png";
	itemMap[134] = "clock_31.png";
	itemMap[135] = "iron_pickaxe.png";
	itemMap[136] = "compass_03.png";
	itemMap[137] = "door_wood.png";
	itemMap[138] = "dye_powder_pink.png";
	itemMap[139] = "ender_pearl.png";
	itemMap[140] = "record_strad.png";
	itemMap[141] = "bow_standby.png";
	itemMap[142] = "egg.png";
	itemMap[143] = "snowball.png";
	itemMap[144] = "record_mall.png";
	itemMap[145] = "leather_helmet_overlay.png";
	itemMap[146] = "compass_28.png";
	itemMap[147] = "beef_raw.png";
	itemMap[148] = "clock_23.png";
	itemMap[149] = "end_crystal.png";
	itemMap[150] = "compass_30.png";
	itemMap[151] = "birch_boat.png";
	itemMap[152] = "fireworks_charge.png";
	itemMap[153] = "potion_bottle_empty.png";
	itemMap[154] = "stone_hoe.png";
	itemMap[155] = "tipped_arrow_base.png";
	itemMap[156] = "map_filled.png";
	itemMap[157] = "nether_star.png";
	itemMap[158] = "blaze_powder.png";
	itemMap[159] = "tipped_arrow_head.png";
	itemMap[160] = "spider_eye.png";
	itemMap[161] = "coal.png";
	itemMap[162] = "rabbit_foot.png";
	itemMap[163] = "dye_powder_blue.png";
	itemMap[164] = "cake.png";
	itemMap[165] = "clock_07.png";
	itemMap[166] = "bone.png";
	itemMap[167] = "compass_17.png";
	itemMap[168] = "stick.png";
	itemMap[169] = "beef_cooked.png";
	itemMap[170] = "clock_12.png";
	itemMap[171] = "clock_58.png";
	itemMap[172] = "compass_01.png";
	itemMap[173] = "paper.png";
	itemMap[174] = "diamond_hoe.png";
	itemMap[175] = "compass_21.png";
	itemMap[176] = "brewing_stand.png";
	itemMap[177] = "diamond_boots.png";
	itemMap[178] = "potato_baked.png";
	itemMap[179] = "pumpkin_pie.png";
	itemMap[180] = "magma_cream.png";
	itemMap[181] = "iron_horse_armor.png";
	itemMap[182] = "dye_powder_gray.png";
	itemMap[183] = "sugar.png";
	itemMap[184] = "fish_salmon_raw.png";
	itemMap[185] = "potato_poisonous.png";
	itemMap[186] = "compass_19.png";
	itemMap[187] = "gold_helmet.png";
	itemMap[188] = "diamond_pickaxe.png";
	itemMap[189] = "flower_pot.png";
	itemMap[190] = "sign.png";
	itemMap[191] = "minecart_hopper.png";
	itemMap[192] = "bread.png";
	itemMap[193] = "record_11.png";
	itemMap[194] = "clock_33.png";
	itemMap[195] = "glowstone_dust.png";
	itemMap[196] = "dye_powder_white.png";
	itemMap[197] = "clock_51.png";
	itemMap[198] = "slimeball.png";
	itemMap[199] = "iron_leggings.png";
	itemMap[200] = "empty_armor_slot_shield.png";
	itemMap[201] = "dye_powder_cyan.png";
	itemMap[202] = "nether_wart.png";
	itemMap[203] = "dye_powder_purple.png";
	itemMap[204] = "gold_boots.png";
	itemMap[205] = "acacia_boat.png";
	itemMap[206] = "oak_boat.png";
	itemMap[207] = "dark_oak_boat.png";
	itemMap[208] = "minecart_normal.png";
	itemMap[209] = "redstone_dust.png";
	itemMap[210] = "chainmail_chestplate.png";
	itemMap[211] = "cauldron.png";
	itemMap[212] = "stone_shovel.png";
	itemMap[213] = "clock_60.png";
	itemMap[214] = "fishing_rod_cast.png";
	itemMap[215] = "spawn_egg.png";
	itemMap[216] = "string.png";
	itemMap[217] = "mutton_cooked.png";
	itemMap[218] = "melon.png";
	itemMap[219] = "dye_powder_orange.png";
	itemMap[220] = "clock_17.png";
	itemMap[221] = "brick.png";
	itemMap[222] = "leather_helmet.png";
	itemMap[223] = "clock_32.png";
	itemMap[224] = "record_cat.png";
	itemMap[225] = "clock_55.png";
	itemMap[226] = "iron_helmet.png";
	itemMap[227] = "barrier.png";
	itemMap[228] = "spawn_egg_overlay.png";
	itemMap[229] = "flint.png";
	itemMap[230] = "porkchop_raw.png";
	itemMap[231] = "clock_01.png";
	itemMap[232] = "mushroom_stew.png";
	itemMap[233] = "bow_pulling_2.png";
	itemMap[234] = "rabbit_raw.png";
	itemMap[235] = "clock_40.png";
	itemMap[236] = "seeds_melon.png";
	itemMap[237] = "fishing_rod_uncast.png";
	itemMap[238] = "wood_pickaxe.png";
	itemMap[239] = "clock_05.png";
	itemMap[240] = "gunpowder.png";
	itemMap[241] = "iron_hoe.png";
	itemMap[242] = "door_iron.png";
	itemMap[243] = "minecart_tnt.png";
	itemMap[244] = "clock_36.png";
	itemMap[245] = "clock_16.png";
	itemMap[246] = "bow_pulling_0.png";
	itemMap[247] = "stone_pickaxe.png";
	itemMap[248] = "potion_overlay.png";
	itemMap[249] = "compass_20.png";
	itemMap[250] = "cookie.png";
	itemMap[251] = "compass_11.png";
	itemMap[252] = "clock_35.png";
	itemMap[253] = "clock_11.png";
	itemMap[254] = "broken_elytra.png";
	itemMap[255] = "clock_48.png";
	itemMap[256] = "carrot_on_a_stick.png";
	itemMap[257] = "arrow.png";
	itemMap[258] = "compass_08.png";
	itemMap[259] = "map_empty.png";
	itemMap[260] = "dye_powder_yellow.png";
	itemMap[261] = "lead.png";
	itemMap[262] = "clock_29.png";
	itemMap[263] = "compass_15.png";
	itemMap[264] = "elytra.png";
	itemMap[265] = "reeds.png";
	itemMap[266] = "clock_13.png";
	itemMap[267] = "chicken_raw.png";
	itemMap[268] = "compass_18.png";
	itemMap[269] = "leather_chestplate_overlay.png";
	itemMap[270] = "clock_49.png";
	itemMap[271] = "clock_28.png";
	itemMap[272] = "empty_armor_slot_leggings.png";
	itemMap[273] = "dye_powder_green.png";
	itemMap[274] = "clock_00.png";
	itemMap[275] = "potion_bottle_drinkable.png";
	itemMap[276] = "chainmail_helmet.png";
	itemMap[277] = "chainmail_boots.png";
	itemMap[278] = "clock_34.png";
	itemMap[279] = "spider_eye_fermented.png";
	itemMap[280] = "rabbit_stew.png";
	itemMap[281] = "clock_08.png";
	itemMap[282] = "diamond_chestplate.png";
	itemMap[283] = "clock_53.png";
	itemMap[284] = "feather.png";
	itemMap[285] = "wood_hoe.png";
	itemMap[286] = "compass_29.png";
	itemMap[287] = "apple_golden.png";
	itemMap[288] = "bed.png";
	itemMap[289] = "gold_horse_armor.png";
	itemMap[290] = "banner_overlay.png";
	itemMap[291] = "stone_sword.png";
	itemMap[292] = "ghast_tear.png";
	itemMap[293] = "door_jungle.png";
	itemMap[294] = "chorus_fruit.png";
	itemMap[295] = "clock_02.png";
	itemMap[296] = "gold_ingot.png";
	itemMap[297] = "item_frame.png";
	itemMap[298] = "clock_15.png";
	itemMap[299] = "iron_shovel.png";
	itemMap[300] = "quartz.png";
	itemMap[301] = "fish_salmon_cooked.png";
	itemMap[302] = "jungle_boat.png";
	itemMap[303] = "ender_eye.png";
	itemMap[304] = "chicken_cooked.png";
	itemMap[305] = "clock_03.png";
	itemMap[306] = "leather_leggings.png";
	itemMap[307] = "painting.png";
	itemMap[308] = "record_chirp.png";
	itemMap[309] = "clock_22.png";
	itemMap[310] = "bowl.png";
	itemMap[311] = "record_stal.png";
	itemMap[312] = "clock_09.png";
	itemMap[313] = "compass_00.png";
	itemMap[314] = "fireworks_charge_overlay.png";
	itemMap[315] = "diamond_helmet.png";
	itemMap[316] = "banner_base.png";
	itemMap[317] = "bucket_water.png";
	itemMap[318] = "door_spruce.png";
	itemMap[319] = "clock_26.png";
	itemMap[320] = "dye_powder_light_blue.png";
	itemMap[321] = "book_writable.png";
	itemMap[322] = "empty_armor_slot_helmet.png";
	itemMap[323] = "diamond_horse_armor.png";
	itemMap[324] = "clock_30.png";
	itemMap[325] = "clock_61.png";
	itemMap[326] = "repeater.png";
	itemMap[327] = "clock_21.png";
	itemMap[328] = "hopper.png";
	itemMap[329] = "diamond_leggings.png";
	itemMap[330] = "gold_nugget.png";
	itemMap[331] = "beetroot.png";
	itemMap[332] = "compass_02.png";
	itemMap[333] = "experience_bottle.png";
	itemMap[334] = "bucket_milk.png";
	itemMap[335] = "clock_42.png";
	itemMap[336] = "clock_62.png";
	itemMap[337] = "iron_ingot.png";
	itemMap[338] = "minecart_command_block.png";
	itemSizeMap = malloc(sizeof(int) * 339);
	loadTexturesPNG(INSTALLDIR "assets/minecraft/textures/items/", idef_wrap, &idef_width, &idef_height, TX_ITEMS, 1, itemMap, 339, itemSizeMap);;
}

void getITextureCoordinates(int tx, int ty, float* tx1, float* ty1, float* tx2, float* ty2) {
	static float tw;
	if (!tw) tw = 1. / (float) idef_wrap;
	static float th;
	if (!th) th = 1. / ((float) idef_height / ((float) idef_width / (float) idef_wrap));
	*tx1 = tw * tx + ((float) TEXTURE_BUFFER + 0.01) / (float) idef_width;
	*ty1 = th * ty + ((float) TEXTURE_BUFFER + 0.01) / (float) idef_height;
	*tx2 = tw * (tx + 1) - ((float) TEXTURE_BUFFER + 0.01) / (float) idef_width;
	*ty2 = th * (ty + 1) - ((float) TEXTURE_BUFFER + 0.01) / (float) idef_height;
}

void getItemTexture(struct slot* slot, float* tx1, float* ty1, float* tx2, float* ty2) {
	if (slot->item == IRON_SHOVEL) getITextureCoordinates(TXC_IRON_SHOVEL, tx1, ty1, tx2, ty2);
	else if (slot->item == IRON_PICKAXE) getITextureCoordinates(TXC_IRON_PICKAXE, tx1, ty1, tx2, ty2);
	else if (slot->item == IRON_AXE) getITextureCoordinates(TXC_IRON_AXE, tx1, ty1, tx2, ty2);
	else if (slot->item == FLINT_AND_STEEL) getITextureCoordinates(TXC_FLINT_AND_STEEL, tx1, ty1, tx2, ty2);
	else if (slot->item == APPLE) getITextureCoordinates(TXC_APPLE, tx1, ty1, tx2, ty2);
	else if (slot->item == BOW) getITextureCoordinates(TXC_BOW, tx1, ty1, tx2, ty2);
	else if (slot->item == ARROW) getITextureCoordinates(TXC_ARROW, tx1, ty1, tx2, ty2);
	else if (slot->item == COAL) getITextureCoordinates(TXC_COAL, tx1, ty1, tx2, ty2);
	else if (slot->item == DIAMOND) getITextureCoordinates(TXC_DIAMOND, tx1, ty1, tx2, ty2);
	else if (slot->item == IRON_INGOT) getITextureCoordinates(TXC_IRON_INGOT, tx1, ty1, tx2, ty2);
	else if (slot->item == GOLD_INGOT) getITextureCoordinates(TXC_GOLD_INGOT, tx1, ty1, tx2, ty2);
	else if (slot->item == IRON_SWORD) getITextureCoordinates(TXC_IRON_SWORD, tx1, ty1, tx2, ty2);
	else if (slot->item == WOODEN_SWORD) getITextureCoordinates(TXC_WOODEN_SWORD, tx1, ty1, tx2, ty2);
	else if (slot->item == WOODEN_SHOVEL) getITextureCoordinates(TXC_WOODEN_SHOVEL, tx1, ty1, tx2, ty2);
	else if (slot->item == WOODEN_PICKAXE) getITextureCoordinates(TXC_WOODEN_PICKAXE, tx1, ty1, tx2, ty2);
	else if (slot->item == WOODEN_AXE) getITextureCoordinates(TXC_WOODEN_AXE, tx1, ty1, tx2, ty2);
	else if (slot->item == STONE_SWORD) getITextureCoordinates(TXC_STONE_SWORD, tx1, ty1, tx2, ty2);
	else if (slot->item == STONE_SHOVEL) getITextureCoordinates(TXC_STONE_SHOVEL, tx1, ty1, tx2, ty2);
	else if (slot->item == STONE_PICKAXE) getITextureCoordinates(TXC_STONE_PICKAXE, tx1, ty1, tx2, ty2);
	else if (slot->item == STONE_AXE) getITextureCoordinates(TXC_STONE_AXE, tx1, ty1, tx2, ty2);
	else if (slot->item == DIAMOND_SWORD) getITextureCoordinates(TXC_DIAMOND_SWORD, tx1, ty1, tx2, ty2);
	else if (slot->item == DIAMOND_SHOVEL) getITextureCoordinates(TXC_DIAMOND_SHOVEL, tx1, ty1, tx2, ty2);
	else if (slot->item == DIAMOND_PICKAXE) getITextureCoordinates(TXC_DIAMOND_PICKAXE, tx1, ty1, tx2, ty2);
	else if (slot->item == DIAMOND_AXE) getITextureCoordinates(TXC_DIAMOND_AXE, tx1, ty1, tx2, ty2);
	else if (slot->item == STICK) getITextureCoordinates(TXC_STICK, tx1, ty1, tx2, ty2);
	else if (slot->item == BOWL) getITextureCoordinates(TXC_BOWL, tx1, ty1, tx2, ty2);
	else if (slot->item == MUSHROOM_STEW) getITextureCoordinates(TXC_MUSHROOM_STEW, tx1, ty1, tx2, ty2);
	else if (slot->item == GOLDEN_SWORD) getITextureCoordinates(TXC_GOLDEN_SWORD, tx1, ty1, tx2, ty2);
	else if (slot->item == GOLDEN_SHOVEL) getITextureCoordinates(TXC_GOLDEN_SHOVEL, tx1, ty1, tx2, ty2);
	else if (slot->item == GOLDEN_PICKAXE) getITextureCoordinates(TXC_GOLDEN_PICKAXE, tx1, ty1, tx2, ty2);
	else if (slot->item == GOLDEN_AXE) getITextureCoordinates(TXC_GOLDEN_AXE, tx1, ty1, tx2, ty2);
	else if (slot->item == STRING) getITextureCoordinates(TXC_STRING, tx1, ty1, tx2, ty2);
	else if (slot->item == FEATHER) getITextureCoordinates(TXC_FEATHER, tx1, ty1, tx2, ty2);
	else if (slot->item == GUNPOWDER) getITextureCoordinates(TXC_GUNPOWDER, tx1, ty1, tx2, ty2);
	else if (slot->item == WOODEN_HOE) getITextureCoordinates(TXC_WOODEN_HOE, tx1, ty1, tx2, ty2);
	else if (slot->item == STONE_HOE) getITextureCoordinates(TXC_STONE_HOE, tx1, ty1, tx2, ty2);
	else if (slot->item == IRON_HOE) getITextureCoordinates(TXC_IRON_HOE, tx1, ty1, tx2, ty2);
	else if (slot->item == DIAMOND_HOE) getITextureCoordinates(TXC_DIAMOND_HOE, tx1, ty1, tx2, ty2);
	else if (slot->item == GOLDEN_HOE) getITextureCoordinates(TXC_GOLDEN_HOE, tx1, ty1, tx2, ty2);
	else if (slot->item == SEEDS) getITextureCoordinates(TXC_SEEDS, tx1, ty1, tx2, ty2);
	else if (slot->item == WHEAT) getITextureCoordinates(TXC_WHEAT, tx1, ty1, tx2, ty2);
	else if (slot->item == BREAD) getITextureCoordinates(TXC_BREAD, tx1, ty1, tx2, ty2);
	else if (slot->item == LEATHER_CAP) getITextureCoordinates(TXC_LEATHER_CAP, tx1, ty1, tx2, ty2);
	else if (slot->item == LEATHER_TUNIC) getITextureCoordinates(TXC_LEATHER_TUNIC, tx1, ty1, tx2, ty2);
	else if (slot->item == LEATHER_PANTS) getITextureCoordinates(TXC_LEATHER_PANTS, tx1, ty1, tx2, ty2);
	else if (slot->item == LEATHER_BOOTS) getITextureCoordinates(TXC_LEATHER_BOOTS, tx1, ty1, tx2, ty2);
	else if (slot->item == CHAIN_HELMET) getITextureCoordinates(TXC_CHAIN_HELMET, tx1, ty1, tx2, ty2);
	else if (slot->item == CHAIN_CHESTPLATE) getITextureCoordinates(TXC_CHAIN_CHESTPLATE, tx1, ty1, tx2, ty2);
	else if (slot->item == CHAIN_LEGGINGS) getITextureCoordinates(TXC_CHAIN_LEGGINGS, tx1, ty1, tx2, ty2);
	else if (slot->item == CHAIN_BOOTS) getITextureCoordinates(TXC_CHAIN_BOOTS, tx1, ty1, tx2, ty2);
	else if (slot->item == IRON_HELMET) getITextureCoordinates(TXC_IRON_HELMET, tx1, ty1, tx2, ty2);
	else if (slot->item == IRON_CHESTPLATE) getITextureCoordinates(TXC_IRON_CHESTPLATE, tx1, ty1, tx2, ty2);
	else if (slot->item == IRON_LEGGINGS) getITextureCoordinates(TXC_IRON_LEGGINGS, tx1, ty1, tx2, ty2);
	else if (slot->item == IRON_BOOTS) getITextureCoordinates(TXC_IRON_BOOTS, tx1, ty1, tx2, ty2);
	else if (slot->item == DIAMOND_HELMET) getITextureCoordinates(TXC_DIAMOND_HELMET, tx1, ty1, tx2, ty2);
	else if (slot->item == DIAMOND_CHESTPLATE) getITextureCoordinates(TXC_DIAMOND_CHESTPLATE, tx1, ty1, tx2, ty2);
	else if (slot->item == DIAMOND_LEGGINGS) getITextureCoordinates(TXC_DIAMOND_LEGGINGS, tx1, ty1, tx2, ty2);
	else if (slot->item == DIAMOND_BOOTS) getITextureCoordinates(TXC_DIAMOND_BOOTS, tx1, ty1, tx2, ty2);
	else if (slot->item == GOLDEN_HELMET) getITextureCoordinates(TXC_GOLDEN_HELMET, tx1, ty1, tx2, ty2);
	else if (slot->item == GOLDEN_CHESTPLATE) getITextureCoordinates(TXC_GOLDEN_CHESTPLATE, tx1, ty1, tx2, ty2);
	else if (slot->item == GOLDEN_LEGGINGS) getITextureCoordinates(TXC_GOLDEN_LEGGINGS, tx1, ty1, tx2, ty2);
	else if (slot->item == GOLDEN_BOOTS) getITextureCoordinates(TXC_GOLDEN_BOOTS, tx1, ty1, tx2, ty2);
	else if (slot->item == FLINT) getITextureCoordinates(TXC_FLINT, tx1, ty1, tx2, ty2);
	else if (slot->item == RAW_PORKCHOP) getITextureCoordinates(TXC_RAW_PORKCHOP, tx1, ty1, tx2, ty2);
	else if (slot->item == COOKED_PORKCHOP) getITextureCoordinates(TXC_COOKED_PORKCHOP, tx1, ty1, tx2, ty2);
	else if (slot->item == PAINTING) getITextureCoordinates(TXC_PAINTING, tx1, ty1, tx2, ty2);
	else if (slot->item == GOLDEN_APPLE) getITextureCoordinates(TXC_GOLDEN_APPLE, tx1, ty1, tx2, ty2);
	else if (slot->item == SIGN) getITextureCoordinates(TXC_SIGN, tx1, ty1, tx2, ty2);
	else if (slot->item == OAK_DOOR) getITextureCoordinates(TXC_OAK_DOOR, tx1, ty1, tx2, ty2);
	else if (slot->item == BUCKET) getITextureCoordinates(TXC_BUCKET, tx1, ty1, tx2, ty2);
	else if (slot->item == WATER_BUCKET) getITextureCoordinates(TXC_WATER_BUCKET, tx1, ty1, tx2, ty2);
	else if (slot->item == LAVA_BUCKET) getITextureCoordinates(TXC_LAVA_BUCKET, tx1, ty1, tx2, ty2);
	else if (slot->item == MINECART) getITextureCoordinates(TXC_MINECART, tx1, ty1, tx2, ty2);
	else if (slot->item == SADDLE) getITextureCoordinates(TXC_SADDLE, tx1, ty1, tx2, ty2);
	else if (slot->item == IRON_DOOR) getITextureCoordinates(TXC_IRON_DOOR, tx1, ty1, tx2, ty2);
	else if (slot->item == REDSTONE) getITextureCoordinates(TXC_REDSTONE, tx1, ty1, tx2, ty2);
	else if (slot->item == SNOWBALL) getITextureCoordinates(TXC_SNOWBALL, tx1, ty1, tx2, ty2);
	else if (slot->item == OAK_BOAT) getITextureCoordinates(TXC_OAK_BOAT, tx1, ty1, tx2, ty2);
	else if (slot->item == LEATHER) getITextureCoordinates(TXC_LEATHER, tx1, ty1, tx2, ty2);
	else if (slot->item == MILK) getITextureCoordinates(TXC_MILK, tx1, ty1, tx2, ty2);
	else if (slot->item == BRICK) getITextureCoordinates(TXC_BRICK, tx1, ty1, tx2, ty2);
	else if (slot->item == CLAY) getITextureCoordinates(TXC_CLAY, tx1, ty1, tx2, ty2);
	else if (slot->item == SUGAR_CANES) getITextureCoordinates(TXC_SUGAR_CANES, tx1, ty1, tx2, ty2);
	else if (slot->item == PAPER) getITextureCoordinates(TXC_PAPER, tx1, ty1, tx2, ty2);
	else if (slot->item == BOOK) getITextureCoordinates(TXC_BOOK, tx1, ty1, tx2, ty2);
	else if (slot->item == SLIMEBALL) getITextureCoordinates(TXC_SLIMEBALL, tx1, ty1, tx2, ty2);
	else if (slot->item == MINECART_WITH_CHEST) getITextureCoordinates(TXC_MINECART_WITH_CHEST, tx1, ty1, tx2, ty2);
	else if (slot->item == MINECART_WITH_FURNACE) getITextureCoordinates(TXC_MINECART_WITH_FURNACE, tx1, ty1, tx2, ty2);
	else if (slot->item == EGG) getITextureCoordinates(TXC_EGG, tx1, ty1, tx2, ty2);
	else if (slot->item == COMPASS) getITextureCoordinates(TXC_COMPASS, tx1, ty1, tx2, ty2);
	else if (slot->item == FISHING_ROD) getITextureCoordinates(TXC_FISHING_ROD, tx1, ty1, tx2, ty2);
	else if (slot->item == CLOCK) getITextureCoordinates(TXC_CLOCK, tx1, ty1, tx2, ty2);
	else if (slot->item == GLOWSTONE_DUST) getITextureCoordinates(TXC_GLOWSTONE_DUST, tx1, ty1, tx2, ty2);
	else if (slot->item == ITEM_FISH_NAME) getITextureCoordinates(TXC_ITEM_FISH_NAME, tx1, ty1, tx2, ty2);
	else if (slot->item == ITEM_FISH_NAME2) getITextureCoordinates(TXC_ITEM_FISH_NAME2, tx1, ty1, tx2, ty2);
	else if (slot->item == ITEM_DYEPOWDER_NAME) getITextureCoordinates(TXC_ITEM_DYEPOWDER_NAME, tx1, ty1, tx2, ty2);
	else if (slot->item == BONE) getITextureCoordinates(TXC_BONE, tx1, ty1, tx2, ty2);
	else if (slot->item == SUGAR) getITextureCoordinates(TXC_SUGAR, tx1, ty1, tx2, ty2);
	else if (slot->item == CAKE) getITextureCoordinates(TXC_CAKE, tx1, ty1, tx2, ty2);
	else if (slot->item == BED) getITextureCoordinates(TXC_BED, tx1, ty1, tx2, ty2);
	else if (slot->item == REDSTONE_REPEATER) getITextureCoordinates(TXC_REDSTONE_REPEATER, tx1, ty1, tx2, ty2);
	else if (slot->item == COOKIE) getITextureCoordinates(TXC_COOKIE, tx1, ty1, tx2, ty2);
	else if (slot->item == MAP) getITextureCoordinates(TXC_MAP, tx1, ty1, tx2, ty2);
	else if (slot->item == SHEARS) getITextureCoordinates(TXC_SHEARS, tx1, ty1, tx2, ty2);
	else if (slot->item == MELON) getITextureCoordinates(TXC_MELON, tx1, ty1, tx2, ty2);
	else if (slot->item == PUMPKIN_SEEDS) getITextureCoordinates(TXC_PUMPKIN_SEEDS, tx1, ty1, tx2, ty2);
	else if (slot->item == MELON_SEEDS) getITextureCoordinates(TXC_MELON_SEEDS, tx1, ty1, tx2, ty2);
	else if (slot->item == RAW_BEEF) getITextureCoordinates(TXC_RAW_BEEF, tx1, ty1, tx2, ty2);
	else if (slot->item == STEAK) getITextureCoordinates(TXC_STEAK, tx1, ty1, tx2, ty2);
	else if (slot->item == RAW_CHICKEN) getITextureCoordinates(TXC_RAW_CHICKEN, tx1, ty1, tx2, ty2);
	else if (slot->item == COOKED_CHICKEN) getITextureCoordinates(TXC_COOKED_CHICKEN, tx1, ty1, tx2, ty2);
	else if (slot->item == ROTTEN_FLESH) getITextureCoordinates(TXC_ROTTEN_FLESH, tx1, ty1, tx2, ty2);
	else if (slot->item == ENDER_PEARL) getITextureCoordinates(TXC_ENDER_PEARL, tx1, ty1, tx2, ty2);
	else if (slot->item == BLAZE_ROD) getITextureCoordinates(TXC_BLAZE_ROD, tx1, ty1, tx2, ty2);
	else if (slot->item == GHAST_TEAR) getITextureCoordinates(TXC_GHAST_TEAR, tx1, ty1, tx2, ty2);
	else if (slot->item == GOLD_NUGGET) getITextureCoordinates(TXC_GOLD_NUGGET, tx1, ty1, tx2, ty2);
	else if (slot->item == NETHER_WART) getITextureCoordinates(TXC_NETHER_WART, tx1, ty1, tx2, ty2);
	else if (slot->item == POTION) getITextureCoordinates(TXC_POTION, tx1, ty1, tx2, ty2);
	else if (slot->item == GLASS_BOTTLE) getITextureCoordinates(TXC_GLASS_BOTTLE, tx1, ty1, tx2, ty2);
	else if (slot->item == SPIDER_EYE) getITextureCoordinates(TXC_SPIDER_EYE, tx1, ty1, tx2, ty2);
	else if (slot->item == FERMENTED_SPIDER_EYE) getITextureCoordinates(TXC_FERMENTED_SPIDER_EYE, tx1, ty1, tx2, ty2);
	else if (slot->item == BLAZE_POWDER) getITextureCoordinates(TXC_BLAZE_POWDER, tx1, ty1, tx2, ty2);
	else if (slot->item == MAGMA_CREAM) getITextureCoordinates(TXC_MAGMA_CREAM, tx1, ty1, tx2, ty2);
	else if (slot->item == BREWING_STAND) getITextureCoordinates(TXC_BREWING_STAND, tx1, ty1, tx2, ty2);
	else if (slot->item == CAULDRON) getITextureCoordinates(TXC_CAULDRON, tx1, ty1, tx2, ty2);
	else if (slot->item == EYE_OF_ENDER) getITextureCoordinates(TXC_EYE_OF_ENDER, tx1, ty1, tx2, ty2);
	else if (slot->item == GLISTERING_MELON) getITextureCoordinates(TXC_GLISTERING_MELON, tx1, ty1, tx2, ty2);
	else if (slot->item == SPAWN) getITextureCoordinates(TXC_SPAWN, tx1, ty1, tx2, ty2);
	else if (slot->item == BOTTLE_O_ENCHANTING) getITextureCoordinates(TXC_BOTTLE_O_ENCHANTING, tx1, ty1, tx2, ty2);
	else if (slot->item == FIRE_CHARGE) getITextureCoordinates(TXC_FIRE_CHARGE, tx1, ty1, tx2, ty2);
	else if (slot->item == BOOK_AND_QUILL) getITextureCoordinates(TXC_BOOK_AND_QUILL, tx1, ty1, tx2, ty2);
	else if (slot->item == WRITTEN_BOOK) getITextureCoordinates(TXC_WRITTEN_BOOK, tx1, ty1, tx2, ty2);
	else if (slot->item == EMERALD) getITextureCoordinates(TXC_EMERALD, tx1, ty1, tx2, ty2);
	else if (slot->item == ITEM_FRAME) getITextureCoordinates(TXC_ITEM_FRAME, tx1, ty1, tx2, ty2);
	else if (slot->item == FLOWER_POT) getITextureCoordinates(TXC_FLOWER_POT, tx1, ty1, tx2, ty2);
	else if (slot->item == CARROT) getITextureCoordinates(TXC_CARROT, tx1, ty1, tx2, ty2);
	else if (slot->item == POTATO) getITextureCoordinates(TXC_POTATO, tx1, ty1, tx2, ty2);
	else if (slot->item == BAKED_POTATO) getITextureCoordinates(TXC_BAKED_POTATO, tx1, ty1, tx2, ty2);
	else if (slot->item == POISONOUS_POTATO) getITextureCoordinates(TXC_POISONOUS_POTATO, tx1, ty1, tx2, ty2);
	else if (slot->item == EMPTY_MAP) getITextureCoordinates(TXC_EMPTY_MAP, tx1, ty1, tx2, ty2);
	else if (slot->item == GOLDEN_CARROT) getITextureCoordinates(TXC_GOLDEN_CARROT, tx1, ty1, tx2, ty2);
	else if (slot->item == ITEM_SKULL_NAME) getITextureCoordinates(TXC_ITEM_SKULL_NAME, tx1, ty1, tx2, ty2);
	else if (slot->item == CARROT_ON_A_STICK) getITextureCoordinates(TXC_CARROT_ON_A_STICK, tx1, ty1, tx2, ty2);
	else if (slot->item == NETHER_STAR) getITextureCoordinates(TXC_NETHER_STAR, tx1, ty1, tx2, ty2);
	else if (slot->item == PUMPKIN_PIE) getITextureCoordinates(TXC_PUMPKIN_PIE, tx1, ty1, tx2, ty2);
	else if (slot->item == FIREWORK_ROCKET) getITextureCoordinates(TXC_FIREWORK_ROCKET, tx1, ty1, tx2, ty2);
	else if (slot->item == FIREWORK_STAR) getITextureCoordinates(TXC_FIREWORK_STAR, tx1, ty1, tx2, ty2);
	else if (slot->item == ENCHANTED_BOOK) getITextureCoordinates(TXC_ENCHANTED_BOOK, tx1, ty1, tx2, ty2);
	else if (slot->item == REDSTONE_COMPARATOR) getITextureCoordinates(TXC_REDSTONE_COMPARATOR, tx1, ty1, tx2, ty2);
	else if (slot->item == NETHER_BRICK) getITextureCoordinates(TXC_NETHER_BRICK, tx1, ty1, tx2, ty2);
	else if (slot->item == NETHER_QUARTZ) getITextureCoordinates(TXC_NETHER_QUARTZ, tx1, ty1, tx2, ty2);
	else if (slot->item == MINECART_WITH_TNT) getITextureCoordinates(TXC_MINECART_WITH_TNT, tx1, ty1, tx2, ty2);
	else if (slot->item == MINECART_WITH_HOPPER) getITextureCoordinates(TXC_MINECART_WITH_HOPPER, tx1, ty1, tx2, ty2);
	else if (slot->item == PRISMARINE_SHARD) getITextureCoordinates(TXC_PRISMARINE_SHARD, tx1, ty1, tx2, ty2);
	else if (slot->item == PRISMARINE_CRYSTALS) getITextureCoordinates(TXC_PRISMARINE_CRYSTALS, tx1, ty1, tx2, ty2);
	else if (slot->item == RAW_RABBIT) getITextureCoordinates(TXC_RAW_RABBIT, tx1, ty1, tx2, ty2);
	else if (slot->item == COOKED_RABBIT) getITextureCoordinates(TXC_COOKED_RABBIT, tx1, ty1, tx2, ty2);
	else if (slot->item == RABBIT_STEW) getITextureCoordinates(TXC_RABBIT_STEW, tx1, ty1, tx2, ty2);
	else if (slot->item == RABBITS_FOOT) getITextureCoordinates(TXC_RABBITS_FOOT, tx1, ty1, tx2, ty2);
	else if (slot->item == RABBIT_HIDE) getITextureCoordinates(TXC_RABBIT_HIDE, tx1, ty1, tx2, ty2);
	else if (slot->item == ARMOR_STAND) getITextureCoordinates(TXC_ARMOR_STAND, tx1, ty1, tx2, ty2);
	else if (slot->item == IRON_HORSE_ARMOR) getITextureCoordinates(TXC_IRON_HORSE_ARMOR, tx1, ty1, tx2, ty2);
	else if (slot->item == GOLD_HORSE_ARMOR) getITextureCoordinates(TXC_GOLD_HORSE_ARMOR, tx1, ty1, tx2, ty2);
	else if (slot->item == DIAMOND_HORSE_ARMOR) getITextureCoordinates(TXC_DIAMOND_HORSE_ARMOR, tx1, ty1, tx2, ty2);
	else if (slot->item == LEAD) getITextureCoordinates(TXC_LEAD, tx1, ty1, tx2, ty2);
	else if (slot->item == NAME_TAG) getITextureCoordinates(TXC_NAME_TAG, tx1, ty1, tx2, ty2);
	else if (slot->item == MINECART_WITH_COMMAND_BLOCK) getITextureCoordinates(TXC_MINECART_WITH_COMMAND_BLOCK, tx1, ty1, tx2, ty2);
	else if (slot->item == RAW_MUTTON) getITextureCoordinates(TXC_RAW_MUTTON, tx1, ty1, tx2, ty2);
	else if (slot->item == COOKED_MUTTON) getITextureCoordinates(TXC_COOKED_MUTTON, tx1, ty1, tx2, ty2);
	else if (slot->item == TILE_BANNER_NAME) getITextureCoordinates(TXC_TILE_BANNER_NAME, tx1, ty1, tx2, ty2);
	else if (slot->item == END_CRYSTAL) getITextureCoordinates(TXC_END_CRYSTAL, tx1, ty1, tx2, ty2);
	else if (slot->item == SPRUCE_DOOR) getITextureCoordinates(TXC_SPRUCE_DOOR, tx1, ty1, tx2, ty2);
	else if (slot->item == BIRCH_DOOR) getITextureCoordinates(TXC_BIRCH_DOOR, tx1, ty1, tx2, ty2);
	else if (slot->item == JUNGLE_DOOR) getITextureCoordinates(TXC_JUNGLE_DOOR, tx1, ty1, tx2, ty2);
	else if (slot->item == ACACIA_DOOR) getITextureCoordinates(TXC_ACACIA_DOOR, tx1, ty1, tx2, ty2);
	else if (slot->item == DARK_OAK_DOOR) getITextureCoordinates(TXC_DARK_OAK_DOOR, tx1, ty1, tx2, ty2);
	else if (slot->item == CHORUS_FRUIT) getITextureCoordinates(TXC_CHORUS_FRUIT, tx1, ty1, tx2, ty2);
	else if (slot->item == POPPED_CHORUS_FRUIT) getITextureCoordinates(TXC_POPPED_CHORUS_FRUIT, tx1, ty1, tx2, ty2);
	else if (slot->item == BEETROOT) getITextureCoordinates(TXC_BEETROOT, tx1, ty1, tx2, ty2);
	else if (slot->item == BEETROOT_SEEDS) getITextureCoordinates(TXC_BEETROOT_SEEDS, tx1, ty1, tx2, ty2);
	else if (slot->item == BEETROOT_SOUP) getITextureCoordinates(TXC_BEETROOT_SOUP, tx1, ty1, tx2, ty2);
	else if (slot->item == DRAGONS_BREATH) getITextureCoordinates(TXC_DRAGONS_BREATH, tx1, ty1, tx2, ty2);
	else if (slot->item == ITEM_SPLASH_POTION_NAME) getITextureCoordinates(TXC_ITEM_SPLASH_POTION_NAME, tx1, ty1, tx2, ty2);
	else if (slot->item == SPECTRAL_ARROW) getITextureCoordinates(TXC_SPECTRAL_ARROW, tx1, ty1, tx2, ty2);
	else if (slot->item == TIPPED_ARROW) getITextureCoordinates(TXC_TIPPED_ARROW, tx1, ty1, tx2, ty2);
	else if (slot->item == ITEM_LINGERING_POTION_NAME) getITextureCoordinates(TXC_ITEM_LINGERING_POTION_NAME, tx1, ty1, tx2, ty2);
	else if (slot->item == SHIELD) getITextureCoordinates(TXC_SHIELD, tx1, ty1, tx2, ty2);
	else if (slot->item == ELYTRA) getITextureCoordinates(TXC_ELYTRA, tx1, ty1, tx2, ty2);
	else if (slot->item == SPRUCE_BOAT) getITextureCoordinates(TXC_SPRUCE_BOAT, tx1, ty1, tx2, ty2);
	else if (slot->item == BIRCH_BOAT) getITextureCoordinates(TXC_BIRCH_BOAT, tx1, ty1, tx2, ty2);
	else if (slot->item == JUNGLE_BOAT) getITextureCoordinates(TXC_JUNGLE_BOAT, tx1, ty1, tx2, ty2);
	else if (slot->item == ACACIA_BOAT) getITextureCoordinates(TXC_ACACIA_BOAT, tx1, ty1, tx2, ty2);
	else if (slot->item == DARK_OAK_BOAT) getITextureCoordinates(TXC_DARK_OAK_BOAT, tx1, ty1, tx2, ty2);
	else if (slot->item == MUSIC_DISC_13) getITextureCoordinates(TXC_MUSIC_DISC_13, tx1, ty1, tx2, ty2);
	else if (slot->item == MUSIC_DISC_CAT) getITextureCoordinates(TXC_MUSIC_DISC_CAT, tx1, ty1, tx2, ty2);
	else if (slot->item == MUSIC_DISC_BLOCKS) getITextureCoordinates(TXC_MUSIC_DISC_BLOCKS, tx1, ty1, tx2, ty2);
	else if (slot->item == MUSIC_DISC_CHIRP) getITextureCoordinates(TXC_MUSIC_DISC_CHIRP, tx1, ty1, tx2, ty2);
	else if (slot->item == MUSIC_DISC_FAR) getITextureCoordinates(TXC_MUSIC_DISC_FAR, tx1, ty1, tx2, ty2);
	else if (slot->item == MUSIC_DISC_MALL) getITextureCoordinates(TXC_MUSIC_DISC_MALL, tx1, ty1, tx2, ty2);
	else if (slot->item == MUSIC_DISC_MELLOHI) getITextureCoordinates(TXC_MUSIC_DISC_MELLOHI, tx1, ty1, tx2, ty2);
	else if (slot->item == MUSIC_DISC_STAL) getITextureCoordinates(TXC_MUSIC_DISC_STAL, tx1, ty1, tx2, ty2);
	else if (slot->item == MUSIC_DISC_STRAD) getITextureCoordinates(TXC_MUSIC_DISC_STRAD, tx1, ty1, tx2, ty2);
	else if (slot->item == MUSIC_DISC_WARD) getITextureCoordinates(TXC_MUSIC_DISC_WARD, tx1, ty1, tx2, ty2);
	else if (slot->item == MUSIC_DISC_11) getITextureCoordinates(TXC_MUSIC_DISC11, tx1, ty1, tx2, ty2);
	else if (slot->item == MUSIC_DISC_WAIT) getITextureCoordinates(TXC_MUSIC_DISC_WAIT, tx1, ty1, tx2, ty2);
	else if (slot->item == INV_NOHELM) getITextureCoordinates(TXC_INV_NOHELM, tx1, ty1, tx2, ty2);
	else if (slot->item == INV_NOCHEST) getITextureCoordinates(TXC_INV_NOCHEST, tx1, ty1, tx2, ty2);
	else if (slot->item == INV_NOPANTS) getITextureCoordinates(TXC_INV_NOPANTS, tx1, ty1, tx2, ty2);
	else if (slot->item == INV_NOFEET) getITextureCoordinates(TXC_INV_NOFEET, tx1, ty1, tx2, ty2);
	else if (slot->item == INV_NOSHIELD) getITextureCoordinates(TXC_INV_NOSHIELD, tx1, ty1, tx2, ty2);
}

int validItemForSlot(int invtype, int si, struct slot* slot) {
	if (invtype == INVTYPE_PLAYERINVENTORY) {
		if (si == 0) return 0;
		if (si >= 5 && si <= 8) {
			return slot->item >= LEATHER_CAP && slot->item <= GOLDEN_BOOTS;
		} else if (si == 45) {
			return slot->item == SHIELD;
		}
	}
	return 1;
}

int maxStackSize(struct slot* slot) {
	if ((slot->item >= IRON_SHOVEL && slot->item <= FLINT_AND_STEEL) || slot->item == BOW || (slot->item >= IRON_SWORD && slot->item <= DIAMOND_AXE) || (slot->item >= MUSHROOM_STEW && slot->item <= GOLDEN_AXE) || (slot->item >= WOODEN_HOE && slot->item <= GOLDEN_HOE) || (slot->item >= LEATHER_CAP && slot->item <= GOLDEN_BOOTS) || (slot->item >= WATER_BUCKET && slot->item <= SADDLE) || slot->item == OAK_BOAT || slot->item == MILK || slot->item == MINECART_WITH_CHEST || slot->item == MINECART_WITH_FURNACE || slot->item == FISHING_ROD || slot->item == CAKE || slot->item == BED || slot->item == SHEARS || slot->item == POTION || slot->item == BOOK_AND_QUILL || slot->item == CARROT_ON_A_STICK || slot->item == ENCHANTED_BOOK || slot->item == MINECART_WITH_TNT || slot->item == MINECART_WITH_HOPPER || slot->item == RABBIT_STEW || slot->item == IRON_HORSE_ARMOR || slot->item == GOLD_HORSE_ARMOR || slot->item == DIAMOND_HORSE_ARMOR || slot->item == MINECART_WITH_COMMAND_BLOCK
			|| slot->item == BEETROOT_SOUP || slot->item == ITEM_SPLASH_POTION_NAME || slot->item == ITEM_LINGERING_POTION_NAME || slot->item >= SHIELD) return 1;
	if (slot->item == SIGN || slot->item == BUCKET || slot->item == SNOWBALL || slot->item == EGG || slot->item == ENDER_PEARL || slot->item == WRITTEN_BOOK || slot->item == ARMOR_STAND || slot->item == TILE_BANNER_NAME) return 16;
	return 64;
}

void drawSlot(struct inventory* inv, int si, struct slot* slot, int x, int y) {
	if (mouseX >= x && mouseY >= y && mouseX <= x + 16 && mouseY <= y + 16 && si >= -1) {
		drawRect(x, y, -.1, 16, 16, -2130706433);
		if (gs.shiftDown && (mouseButton == 0 || mouseButton == 1)) {
			if (slot == NULL) return;
			struct packet pkt;
			pkt.data.play_client.clickwindow.clicked.item = -1;
			pkt.data.play_client.clickwindow.clicked.nbt = NULL;
			if (slot != NULL && !(slot->item >= INV_NOHELM && slot->item <= INV_NOSHIELD)) {
				memcpy(&pkt.data.play_client.clickwindow.clicked, slot, sizeof(struct slot));
				pkt.data.play_client.clickwindow.clicked.nbt = cloneNBT(slot->nbt);
			}
			int target = -1;
			if (inv->type == INVTYPE_PLAYERINVENTORY) {
				if (slot->item >= LEATHER_CAP && slot->item <= GOLDEN_BOOTS) {
					int at = (slot->item - LEATHER_CAP) % 4;
					if (si != at + 5) target = at + 5;
				}
				int cis = 0;
				int cie = 0;
				if (si >= 36 && si <= 44) {
					cis = 9;
					cie = 35;
				} else if (si >= 9 && si <= 35) {
					cis = 36;
					cie = 44;
				} else {
					cis = 9;
					cie = 44;
				}
				for (int i = cis; i < cie; i++) {
					if (inv->slots[i] != NULL && inv->slots[i]->item == slot->item && inv->slots[i]->damage == slot->damage) {
						int mss = maxStackSize(inv->slots[i]);
						int tc = slot->itemCount + inv->slots[i]->itemCount;
						if (tc <= mss) {
							target = i;
							break;
						} else {
							inv->slots[i]->itemCount = mss;
							slot->itemCount = tc - mss;
						}
					}
				}
				if (target == -1) for (int i = cis; i < cie; i++) {
					if (inv->slots[i] == NULL) {
						target = i;
						break;
					}
				}
				pkt.id = PKT_PLAY_CLIENT_CLICKWINDOW;
				pkt.data.play_client.clickwindow.actionNumber = gs.invAct++;
				pkt.data.play_client.clickwindow.button = 0;
				pkt.data.play_client.clickwindow.mode = 1;
				pkt.data.play_client.clickwindow.slot = si;
				pkt.data.play_client.clickwindow.windowID = inv->windowID;
				writePacket(gs.conn, &pkt);
				if (pkt.data.play_client.clickwindow.clicked.nbt != NULL) {
					freeNBT(pkt.data.play_client.clickwindow.clicked.nbt);
					free(pkt.data.play_client.clickwindow.clicked.nbt);
				}
			}
			if (target != -1) {
				struct slot* tgt = inv->slots[target];
				if (tgt != NULL) {
					tgt->itemCount += slot->itemCount;
					if (slot->nbt != NULL) {
						freeNBT(slot->nbt);
						free(slot->nbt);
					}
					free(slot);
					slot = NULL;
					inv->slots[si] = NULL;
				} else {
					inv->slots[target] = slot;
					slot = NULL;
					inv->slots[si] = NULL;
				}
			}
		} else if (mouseButton == 0) {
			mouseButton = -1;
			struct packet pkt;
			pkt.data.play_client.clickwindow.clicked.item = -1;
			pkt.data.play_client.clickwindow.clicked.nbt = NULL;
			if (slot != NULL && !(slot->item >= INV_NOHELM && slot->item <= INV_NOSHIELD)) {
				memcpy(&pkt.data.play_client.clickwindow.clicked, slot, sizeof(struct slot));
				pkt.data.play_client.clickwindow.clicked.nbt = cloneNBT(slot->nbt);
			}
			if (gs.inCursor != NULL && !validItemForSlot(inv->type, si, gs.inCursor)) goto ske;
			if (inv->slots[si] != NULL && gs.inCursor != NULL && inv->slots[si]->item == gs.inCursor->item && inv->slots[si]->damage == gs.inCursor->damage) {
				int mss = maxStackSize(gs.inCursor);
				int tot = inv->slots[si]->itemCount + gs.inCursor->itemCount;
				inv->slots[si]->itemCount = mss < tot ? mss : tot;
				gs.inCursor->itemCount = tot - inv->slots[si]->itemCount;
				if (gs.inCursor->itemCount <= 0) {
					if (gs.inCursor->nbt != NULL) {
						freeNBT(gs.inCursor->nbt);
						free(gs.inCursor->nbt);
					}
					free(gs.inCursor);
					gs.inCursor = NULL;
				}
				goto sndl;
			}
			inv->slots[si] = gs.inCursor;
			int fi = slot != NULL && slot->item >= INV_NOHELM && slot->item <= INV_NOSHIELD;
			gs.inCursor = fi ? NULL : slot;
			if (gs.inCursor != NULL && gs.inCursor->item < 0) {
				if (gs.inCursor->nbt != NULL) {
					freeNBT(gs.inCursor->nbt);
					free(gs.inCursor->nbt);
				}
				free(gs.inCursor);
				gs.inCursor = NULL;
			}
			slot = inv->slots[si];
			sndl: ;
			pkt.id = PKT_PLAY_CLIENT_CLICKWINDOW;
			pkt.data.play_client.clickwindow.actionNumber = gs.invAct++;
			pkt.data.play_client.clickwindow.button = 0;
			pkt.data.play_client.clickwindow.mode = 0;
			pkt.data.play_client.clickwindow.slot = si;
			pkt.data.play_client.clickwindow.windowID = inv->windowID;
			writePacket(gs.conn, &pkt);
			ske: ;
		} else if (mouseButton == 1) {
			mouseButton = -1;
			struct packet pkt;
			pkt.data.play_client.clickwindow.clicked.item = -1;
			pkt.data.play_client.clickwindow.clicked.nbt = NULL;
			if (slot != NULL && !(slot->item >= INV_NOHELM && slot->item <= INV_NOSHIELD)) {
				memcpy(&pkt.data.play_client.clickwindow.clicked, slot, sizeof(struct slot));
				pkt.data.play_client.clickwindow.clicked.nbt = cloneNBT(slot->nbt);
			}
			if (gs.inCursor == NULL && slot != NULL) {
				gs.inCursor = malloc(sizeof(struct slot));
				memcpy(gs.inCursor, slot, sizeof(struct slot));
				gs.inCursor->nbt = cloneNBT(slot->nbt);
				gs.inCursor->itemCount = (unsigned char) ceil((float) gs.inCursor->itemCount / 2.);
				slot->itemCount -= gs.inCursor->itemCount;
				if (slot->itemCount < 0) {
					if (slot->nbt != NULL) {
						freeNBT(slot->nbt);
						free(slot->nbt);
					}
					free(slot);
					slot = NULL;
					inv->slots[si] = NULL;
				}
			} else if (gs.inCursor != NULL) {
				if (slot == NULL || (slot->item == gs.inCursor->item && slot->damage == gs.inCursor->damage)) {
					int mss = maxStackSize(gs.inCursor);
					if (slot == NULL) {
						slot = malloc(sizeof(struct slot));
						inv->slots[si] = slot;
						memcpy(slot, gs.inCursor, sizeof(struct slot));
						slot->nbt = cloneNBT(gs.inCursor->nbt);
						slot->itemCount = 0;
					}
					if (slot->itemCount < mss) {
						slot->itemCount++;
						if (--gs.inCursor->itemCount == 0) {
							if (gs.inCursor->nbt != NULL) {
								freeNBT(gs.inCursor->nbt);
								free(gs.inCursor->nbt);
							}
							free(gs.inCursor);
							gs.inCursor = NULL;
						}
					}
				} else if (slot != NULL) {
					inv->slots[si] = gs.inCursor;
					int fi = slot != NULL && slot->item >= INV_NOHELM && slot->item <= INV_NOSHIELD;
					gs.inCursor = fi ? NULL : slot;
					slot = inv->slots[si];
					if (gs.inCursor->item < 0) {
						if (gs.inCursor->nbt != NULL) {
							freeNBT(gs.inCursor->nbt);
							free(gs.inCursor->nbt);
						}
						free(gs.inCursor);
						gs.inCursor = NULL;
					}
				}
			}
			pkt.id = PKT_PLAY_CLIENT_CLICKWINDOW;
			pkt.data.play_client.clickwindow.actionNumber = gs.invAct++;
			pkt.data.play_client.clickwindow.button = 1;
			pkt.data.play_client.clickwindow.mode = 0;
			pkt.data.play_client.clickwindow.slot = si;
			pkt.data.play_client.clickwindow.windowID = inv->windowID;
			writePacket(gs.conn, &pkt);
			if (pkt.data.play_client.clickwindow.clicked.nbt != NULL) {
				freeNBT(pkt.data.play_client.clickwindow.clicked.nbt);
				free(pkt.data.play_client.clickwindow.clicked.nbt);
			}
		}
	}
	if (slot == NULL || slot->item <= 0) return;
	if (slot->item < 256) {
		//block (for now)
	} else {
		float tx1 = 0.;
		float ty1 = 0.;
		float tx2 = 0.;
		float ty2 = 0.;
		getItemTexture(slot, &tx1, &ty1, &tx2, &ty2);
		glBindTexture(GL_TEXTURE_2D, TX_ITEMS);
		glBegin (GL_QUADS);
		glTexCoord2f(tx1, ty2);
		glVertex3f(x, y + 16, 1.);
		glTexCoord2f(tx2, ty2);
		glVertex3f(x + 16, y + 16, 1.);
		glTexCoord2f(tx2, ty1);
		glVertex3f(x + 16, y, 1.);
		glTexCoord2f(tx1, ty1);
		glVertex3f(x, y, 1.);
		glEnd();
	}
	if (slot->itemCount != 1) {
		char nc[33];
		nc[32] = 0;
		snprintf(nc, 32, "%i", slot->itemCount);
		drawString(nc, x + 19 - 2 - stringWidth(nc), y + 6 + 3, 16777215);
	}
}

void drawInventory(struct inventory* inv, struct inventory* plinv) {
	int iwid = 176;
	int ihei = 166;
	if (inv->type == INVTYPE_CHEST) ihei = 114 + (inv->slot_count * 2);
	else if (inv->type == INVTYPE_BEACON) {
		iwid = 230;
		ihei = 219;
	} else if (inv->type == INVTYPE_HOPPER) {
		ihei = 133;
	}
	int x = (swidth - iwid) / 2;
	int y = (sheight - ihei) / 2;
	if (inv->type == INVTYPE_PLAYERINVENTORY) {
		glBindTexture(GL_TEXTURE_2D, TX_IV_INVENTORY);
		drawTexturedModalRect(x, y, -1, 0, 0, iwid, ihei);
		if (inv->slots != NULL && inv->slot_count == 46) {
			drawSlot(inv, 0, inv->slots[0], x + 154, y + 28);
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					drawSlot(inv, j + i * 2, inv->slots[j + i * 2], x + 98 + j * 18, y + 18 + i * 18);
				}
			}
			for (int i = 0; i < 4; i++) {
				struct slot* sl = inv->slots[5 + i];
				struct slot ti;
				if (sl == NULL || sl->item <= 0) {
					sl = &ti;
					ti.item = INV_NOHELM + i;
					ti.damage = 0;
					ti.itemCount = 1;
					ti.nbt = NULL;
				}
				drawSlot(inv, 5 + i, sl, x + 8, y + 8 + i * 18);
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 9; j++) {
					drawSlot(inv, j + (i + 1) * 9, inv->slots[j + (i + 1) * 9], x + 8 + j * 18, y + 84 + i * 18);
				}
			}
			for (int i = 0; i < 9; i++) {
				drawSlot(inv, 36 + i, inv->slots[36 + i], x + 8 + i * 18, y + 142);
			}
			{
				struct slot* sl = inv->slots[45];
				struct slot ti;
				if (sl == NULL || sl->item <= 0) {
					sl = &ti;
					ti.item = INV_NOSHIELD;
					ti.damage = 0;
					ti.itemCount = 1;
					ti.nbt = NULL;
				}
				drawSlot(inv, 45, sl, x + 77, y + 62);
			}
		}
	} else if (inv->type == INVTYPE_CHEST) {
		glBindTexture(GL_TEXTURE_2D, TX_IV_CHEST);
		drawTexturedModalRect(x, y, -1, 0, 0, iwid, ihei);
	} else if (inv->type == INVTYPE_WORKBENCH) {
		glBindTexture(GL_TEXTURE_2D, TX_IV_WORKBENCH);
		drawTexturedModalRect(x, y, -1, 0, 0, iwid, ihei);
	} else if (inv->type == INVTYPE_FURNACE) {
		glBindTexture(GL_TEXTURE_2D, TX_IV_FURNACE);
		drawTexturedModalRect(x, y, -1, 0, 0, iwid, ihei);
	} else if (inv->type == INVTYPE_DISPENSER || inv->type == INVTYPE_DROPPER) {
		glBindTexture(GL_TEXTURE_2D, TX_IV_DISPENSER);
		drawTexturedModalRect(x, y, -1, 0, 0, iwid, ihei);
	} else if (inv->type == INVTYPE_ENCHANTINGTABLE) {
		glBindTexture(GL_TEXTURE_2D, TX_IV_ENCHANTINGTABLE);
		drawTexturedModalRect(x, y, -1, 0, 0, iwid, ihei);
	} else if (inv->type == INVTYPE_BREWINGSTAND) {
		glBindTexture(GL_TEXTURE_2D, TX_IV_BREWINGSTAND);
		drawTexturedModalRect(x, y, -1, 0, 0, iwid, ihei);
	} else if (inv->type == INVTYPE_VILLAGER) {
		glBindTexture(GL_TEXTURE_2D, TX_IV_VILLAGER);
		drawTexturedModalRect(x, y, -1, 0, 0, iwid, ihei);
	} else if (inv->type == INVTYPE_BEACON) {
		glBindTexture(GL_TEXTURE_2D, TX_IV_BEACON);
		drawTexturedModalRect(x, y, -1, 0, 0, iwid, ihei);
	} else if (inv->type == INVTYPE_ANVIL) {
		glBindTexture(GL_TEXTURE_2D, TX_IV_ANVIL);
		drawTexturedModalRect(x, y, -1, 0, 0, iwid, ihei);
	} else if (inv->type == INVTYPE_HOPPER) {
		glBindTexture(GL_TEXTURE_2D, TX_IV_HOPPER);
		drawTexturedModalRect(x, y, -1, 0, 0, iwid, ihei);
	} else if (inv->type == INVTYPE_HORSE) {
		glBindTexture(GL_TEXTURE_2D, TX_IV_HORSE);
		drawTexturedModalRect(x, y, -1, 0, 0, iwid, ihei);
	}
	drawSlot(NULL, -2, gs.inCursor, mouseX - 8, mouseY - 8);
}

void setInventoryItems(struct inventory* inv, struct slot** slots, size_t slot_count) {
	_freeInventorySlots(inv);
	for (size_t i = 0; i < slot_count; i++) {
		if (slots[i]->item < 0) {
			if (slots[i]->nbt != NULL) freeNBT(slots[i]->nbt);
			free(slots[i]);
			slots[i] = NULL;
		}
	}
	inv->slots = slots;
	inv->slot_count = slot_count;
}

void setInventorySlot(struct inventory* inv, struct slot* slot, int index) {
	if (index < 0 || index >= inv->slot_count) return;
	if (inv->slots == NULL) {
		if (inv->slot_count < 1) return;
		inv->slots = malloc(sizeof(struct slot*) * inv->slot_count);
		for (int i = 0; i < inv->slot_count; i++) {
			inv->slots[i] = NULL;
		}
	}
	if (slot != NULL && slot->item < 0) {
		if (slot->nbt != NULL) {
			freeNBT(slot->nbt);
			free(slot->nbt);
		}
		free(slot);
		slot = NULL;
	}
	if (inv->slots[index] != NULL) {
		if (inv->slots[index]->nbt != NULL) {
			freeNBT(inv->slots[index]->nbt);
			free(inv->slots[index]->nbt);
		}
		free(inv->slots[index]);
	}
	inv->slots[index] = slot;
}

void setInventoryProperty(struct inventory* inv, int16_t name, int16_t value) {
	if (inv->props != NULL) {
		for (size_t i = 0; i < inv->prop_count; i++) {
			if (inv->props[i][0] == name) {
				inv->props[i][1] = value;
				return;
			}
		}
		inv->props = realloc(inv->props, sizeof(int16_t*) * (inv->prop_count + 1));
	} else {
		inv->props = malloc(sizeof(int16_t*));
		inv->prop_count = 0;
	}
	int16_t* dm = malloc(sizeof(int16_t) * 2);
	dm[0] = name;
	dm[1] = value;
	inv->props[inv->prop_count++] = dm;
}

