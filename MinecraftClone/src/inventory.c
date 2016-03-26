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

void newInventory(struct inventory* inv, int type, int id) {
	inv->title = NULL;
	inv->slots = NULL;
	inv->slot_count = 0;
	inv->props = NULL;
	inv->prop_count = 0;
	inv->type = type;
	inv->windowID = id;
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
	loadTexturesPNG(INSTALLDIR "assets/minecraft/textures/items/", idef_wrap, &idef_width, &idef_height, TX_ITEMS, 1, NULL, 0, NULL);;
}

int drawSlot(struct slot* slot, int x, int y) {
	if (slot->item <= 0) return 0;
	if (slot->item < 256) {
		//block (for now)
	} else {
		//if(slot->item == 256) {

		//}
	}
	return 0;
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
}

void setInventoryItems(struct inventory* inv, struct slot** slots, size_t slot_count) {
	_freeInventorySlots(inv);
	inv->slots = slots;
	inv->slot_count = slot_count;
}

void setInventorySlot(struct inventory* inv, struct slot* slot, int index) {
	if (index < 0 || index >= inv->slot_count) return;
	if (inv->slots == NULL) {
		if (inv->slot_count < 1) return;
		inv->slots = malloc(sizeof(struct slot*) * inv->slot_count);
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

