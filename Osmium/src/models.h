/*
 * models.h
 *
 *  Created on: Feb 23, 2016
 *      Author: root
 */

#ifndef MODELS_H_
#define MODELS_H_

#include "render.h"
#include <stdlib.h>
#include <stdio.h>

#define TEXTURE_BUFFER 4

struct model {
		float txh;
		float txw;
		struct modr** children;
		size_t child_count;
};

void loadBaseModels();

struct model mod_spider;
struct model mod_pig;
struct model mod_pigsaddle;
struct model mod_sheep;
struct model mod_sheepwool;
struct model mod_cow;
struct model mod_wolf;
struct model mod_chicken;
struct model mod_ocelot;
struct model mod_rabbit;
struct model mod_silverfish;
struct model mod_endermite;
struct model mod_creeper;
struct model mod_creepercharge;
struct model mod_enderman;
struct model mod_snowman;
struct model mod_skeleton;
struct model mod_skeletonleggings;
struct model mod_skeletonarmor;
struct model mod_witch;
struct model mod_blaze;
struct model mod_zombie;
struct model mod_zombieleggings;
struct model mod_zombiearmor;
struct model mod_zombievillager;
struct model mod_slime;
struct model mod_slimegel;
struct model mod_magmacube;
struct model mod_ghast;
struct model mod_squid;
struct model mod_villager;
struct model mod_irongolem;
struct model mod_bat;
struct model mod_guardian;
struct model mod_shulker;
struct model mod_dragon;
struct model mod_endercrystal;
struct model mod_endercrystalbaseless;
struct model mod_wither;
struct model mod_witheraura;
struct model mod_leashknot;
struct model mod_witherskull;
struct model mod_shulkerbullet;
struct model mod_armorstand;
struct model mod_armorstandleggings;
struct model mod_armorstandarmor;
struct model mod_minecarttnt;
struct model mod_minecartmobspawner;
struct model mod_minecart;
struct model mod_boat;
struct model mod_horse;
struct model mod_player;
struct model mod_playerleggings;
struct model mod_playerarmor;
struct model mod_playerelytra;
struct model mod_splayer;
struct model mod_splayerleggings;
struct model mod_splayerarmor;
struct model mod_splayerelytra;

// mod_spider
#define SPIDER_SPIDERHEAD children[0]
#define SPIDER_SPIDERNECK children[1]
#define SPIDER_SPIDERBODY children[2]
#define SPIDER_SPIDERLEG1 children[3]
#define SPIDER_SPIDERLEG2 children[4]
#define SPIDER_SPIDERLEG3 children[5]
#define SPIDER_SPIDERLEG4 children[6]
#define SPIDER_SPIDERLEG5 children[7]
#define SPIDER_SPIDERLEG6 children[8]
#define SPIDER_SPIDERLEG7 children[9]
#define SPIDER_SPIDERLEG8 children[10]
// mod_pig
#define PIG_HEAD children[0]
#define PIG_BODY children[1]
#define PIG_LEG1 children[2]
#define PIG_LEG2 children[3]
#define PIG_LEG3 children[4]
#define PIG_LEG4 children[5]
// mod_pigsaddle
#define PIGSADDLE_HEAD children[0]
#define PIGSADDLE_BODY children[1]
#define PIGSADDLE_LEG1 children[2]
#define PIGSADDLE_LEG2 children[3]
#define PIGSADDLE_LEG3 children[4]
#define PIGSADDLE_LEG4 children[5]
// mod_sheep
#define SHEEP_HEAD children[0]
#define SHEEP_BODY children[1]
#define SHEEP_LEG1 children[2]
#define SHEEP_LEG2 children[3]
#define SHEEP_LEG3 children[4]
#define SHEEP_LEG4 children[5]
// mod_sheepwool
#define SHEEPWOOL_HEAD children[0]
#define SHEEPWOOL_BODY children[1]
#define SHEEPWOOL_LEG1 children[2]
#define SHEEPWOOL_LEG2 children[3]
#define SHEEPWOOL_LEG3 children[4]
#define SHEEPWOOL_LEG4 children[5]
// mod_cow
#define COW_HEAD children[0]
#define COW_BODY children[1]
#define COW_LEG1 children[2]
#define COW_LEG2 children[3]
#define COW_LEG3 children[4]
#define COW_LEG4 children[5]
// mod_wolf
#define WOLF_WOLFHEADMAIN children[0]
#define WOLF_WOLFBODY children[1]
#define WOLF_WOLFLEG1 children[2]
#define WOLF_WOLFLEG2 children[3]
#define WOLF_WOLFLEG3 children[4]
#define WOLF_WOLFLEG4 children[5]
// mod_chicken
#define CHICKEN_HEAD children[0]
#define CHICKEN_BODY children[1]
#define CHICKEN_RIGHTLEG children[2]
#define CHICKEN_LEFTLEG children[3]
#define CHICKEN_RIGHTWING children[4]
#define CHICKEN_LEFTWING children[5]
#define CHICKEN_BILL children[6]
#define CHICKEN_CHIN children[7]
// mod_ocelot
#define OCELOT_OCELOTBACKLEFTLEG children[0]
#define OCELOT_OCELOTBACKRIGHTLEG children[1]
#define OCELOT_OCELOTFRONTLEFTLEG children[2]
#define OCELOT_OCELOTFRONTRIGHTLEG children[3]
#define OCELOT_OCELOTTAIL children[4]
#define OCELOT_OCELOTTAIL2 children[5]
#define OCELOT_OCELOTHEAD children[6]
#define OCELOT_OCELOTBODY children[7]
// mod_rabbit
#define RABBIT_RABBITLEFTFOOT children[0]
#define RABBIT_RABBITRIGHTFOOT children[1]
#define RABBIT_RABBITLEFTTHIGH children[2]
#define RABBIT_RABBITRIGHTTHIGH children[3]
#define RABBIT_RABBITBODY children[4]
#define RABBIT_RABBITLEFTARM children[5]
#define RABBIT_RABBITRIGHTARM children[6]
#define RABBIT_RABBITHEAD children[7]
#define RABBIT_RABBITRIGHTEAR children[8]
#define RABBIT_RABBITLEFTEAR children[9]
#define RABBIT_RABBITTAIL children[10]
#define RABBIT_RABBITNOSE children[11]
// mod_silverfish
#define SILVERFISH_SILVERFISHBODYPARTS1 children[0]
#define SILVERFISH_SILVERFISHBODYPARTS2 children[1]
#define SILVERFISH_SILVERFISHBODYPARTS3 children[2]
#define SILVERFISH_SILVERFISHBODYPARTS4 children[3]
#define SILVERFISH_SILVERFISHBODYPARTS5 children[4]
#define SILVERFISH_SILVERFISHBODYPARTS6 children[5]
#define SILVERFISH_SILVERFISHBODYPARTS7 children[6]
#define SILVERFISH_SILVERFISHWINGS1 children[7]
#define SILVERFISH_SILVERFISHWINGS2 children[8]
#define SILVERFISH_SILVERFISHWINGS3 children[9]
// mod_endermite
#define ENDERMITE_PARTS1 children[0]
#define ENDERMITE_PARTS2 children[1]
#define ENDERMITE_PARTS3 children[2]
#define ENDERMITE_PARTS4 children[3]
// mod_creeper
#define CREEPER_HEAD children[0]
#define CREEPER_CREEPERARMOR children[1]
#define CREEPER_BODY children[2]
#define CREEPER_LEG1 children[3]
#define CREEPER_LEG2 children[4]
#define CREEPER_LEG3 children[5]
#define CREEPER_LEG4 children[6]
// mod_creepercharge
#define CREEPERCHARGE_HEAD children[0]
#define CREEPERCHARGE_CREEPERARMOR children[1]
#define CREEPERCHARGE_BODY children[2]
#define CREEPERCHARGE_LEG1 children[3]
#define CREEPERCHARGE_LEG2 children[4]
#define CREEPERCHARGE_LEG3 children[5]
#define CREEPERCHARGE_LEG4 children[6]
// mod_enderman
#define ENDERMAN_BIPEDHEAD children[0]
#define ENDERMAN_BIPEDHEADWEAR children[1]
#define ENDERMAN_BIPEDBODY children[2]
#define ENDERMAN_BIPEDRIGHTARM children[3]
#define ENDERMAN_BIPEDLEFTARM children[4]
#define ENDERMAN_BIPEDRIGHTLEG children[5]
#define ENDERMAN_BIPEDLEFTLEG children[6]
// mod_snowman
#define SNOWMAN_BODY children[0]
#define SNOWMAN_BOTTOMBODY children[1]
#define SNOWMAN_HEAD children[2]
#define SNOWMAN_RIGHTHAND children[3]
#define SNOWMAN_LEFTHAND children[4]
// mod_skeleton
#define SKELETON_BIPEDHEAD children[0]
#define SKELETON_BIPEDHEADWEAR children[1]
#define SKELETON_BIPEDBODY children[2]
#define SKELETON_BIPEDRIGHTARM children[3]
#define SKELETON_BIPEDLEFTARM children[4]
#define SKELETON_BIPEDRIGHTLEG children[5]
#define SKELETON_BIPEDLEFTLEG children[6]
// mod_skeletonleggings
#define SKELETONLEGGINGS_BIPEDHEAD children[0]
#define SKELETONLEGGINGS_BIPEDHEADWEAR children[1]
#define SKELETONLEGGINGS_BIPEDBODY children[2]
#define SKELETONLEGGINGS_BIPEDRIGHTARM children[3]
#define SKELETONLEGGINGS_BIPEDLEFTARM children[4]
#define SKELETONLEGGINGS_BIPEDRIGHTLEG children[5]
#define SKELETONLEGGINGS_BIPEDLEFTLEG children[6]
// mod_skeletonarmor
#define SKELETONARMOR_BIPEDHEAD children[0]
#define SKELETONARMOR_BIPEDHEADWEAR children[1]
#define SKELETONARMOR_BIPEDBODY children[2]
#define SKELETONARMOR_BIPEDRIGHTARM children[3]
#define SKELETONARMOR_BIPEDLEFTARM children[4]
#define SKELETONARMOR_BIPEDRIGHTLEG children[5]
#define SKELETONARMOR_BIPEDLEFTLEG children[6]
// mod_witch
#define WITCH_VILLAGERHEAD children[0]
#define WITCH_VILLAGERBODY children[1]
#define WITCH_VILLAGERARMS children[2]
#define WITCH_RIGHTVILLAGERLEG children[3]
#define WITCH_LEFTVILLAGERLEG children[4]
#define WITCH_VILLAGERNOSE children[5]
// mod_blaze
#define BLAZE_BLAZESTICKS1 children[0]
#define BLAZE_BLAZESTICKS2 children[1]
#define BLAZE_BLAZESTICKS3 children[2]
#define BLAZE_BLAZESTICKS4 children[3]
#define BLAZE_BLAZESTICKS5 children[4]
#define BLAZE_BLAZESTICKS6 children[5]
#define BLAZE_BLAZESTICKS7 children[6]
#define BLAZE_BLAZESTICKS8 children[7]
#define BLAZE_BLAZESTICKS9 children[8]
#define BLAZE_BLAZESTICKS10 children[9]
#define BLAZE_BLAZESTICKS11 children[10]
#define BLAZE_BLAZESTICKS12 children[11]
#define BLAZE_BLAZEHEAD children[12]
// mod_zombie
#define ZOMBIE_BIPEDHEAD children[0]
#define ZOMBIE_BIPEDHEADWEAR children[1]
#define ZOMBIE_BIPEDBODY children[2]
#define ZOMBIE_BIPEDRIGHTARM children[3]
#define ZOMBIE_BIPEDLEFTARM children[4]
#define ZOMBIE_BIPEDRIGHTLEG children[5]
#define ZOMBIE_BIPEDLEFTLEG children[6]
// mod_zombieleggings
#define ZOMBIELEGGINGS_BIPEDHEAD children[0]
#define ZOMBIELEGGINGS_BIPEDHEADWEAR children[1]
#define ZOMBIELEGGINGS_BIPEDBODY children[2]
#define ZOMBIELEGGINGS_BIPEDRIGHTARM children[3]
#define ZOMBIELEGGINGS_BIPEDLEFTARM children[4]
#define ZOMBIELEGGINGS_BIPEDRIGHTLEG children[5]
#define ZOMBIELEGGINGS_BIPEDLEFTLEG children[6]
// mod_zombiearmor
#define ZOMBIEARMOR_BIPEDHEAD children[0]
#define ZOMBIEARMOR_BIPEDHEADWEAR children[1]
#define ZOMBIEARMOR_BIPEDBODY children[2]
#define ZOMBIEARMOR_BIPEDRIGHTARM children[3]
#define ZOMBIEARMOR_BIPEDLEFTARM children[4]
#define ZOMBIEARMOR_BIPEDRIGHTLEG children[5]
#define ZOMBIEARMOR_BIPEDLEFTLEG children[6]
// mod_zombievillager
#define ZOMBIEVILLAGER_BIPEDHEAD children[0]
#define ZOMBIEVILLAGER_BIPEDHEADWEAR children[1]
#define ZOMBIEVILLAGER_BIPEDBODY children[2]
#define ZOMBIEVILLAGER_BIPEDRIGHTARM children[3]
#define ZOMBIEVILLAGER_BIPEDLEFTARM children[4]
#define ZOMBIEVILLAGER_BIPEDRIGHTLEG children[5]
#define ZOMBIEVILLAGER_BIPEDLEFTLEG children[6]
// mod_slime
#define SLIME_SLIMEBODIES children[0]
#define SLIME_SLIMERIGHTEYE children[1]
#define SLIME_SLIMELEFTEYE children[2]
#define SLIME_SLIMEMOUTH children[3]
// mod_slimegel
#define SLIMEGEL_SLIMEBODIES children[0]
#define SLIMEGEL_SLIMERIGHTEYE children[1]
#define SLIMEGEL_SLIMELEFTEYE children[2]
#define SLIMEGEL_SLIMEMOUTH children[3]
// mod_magmacube
#define MAGMACUBE_SEGMENTS1 children[0]
#define MAGMACUBE_SEGMENTS2 children[1]
#define MAGMACUBE_SEGMENTS3 children[2]
#define MAGMACUBE_SEGMENTS4 children[3]
#define MAGMACUBE_SEGMENTS5 children[4]
#define MAGMACUBE_SEGMENTS6 children[5]
#define MAGMACUBE_SEGMENTS7 children[6]
#define MAGMACUBE_SEGMENTS8 children[7]
#define MAGMACUBE_CORE children[8]
// mod_ghast
#define GHAST_BODY children[0]
#define GHAST_TENTACLES1 children[1]
#define GHAST_TENTACLES2 children[2]
#define GHAST_TENTACLES3 children[3]
#define GHAST_TENTACLES4 children[4]
#define GHAST_TENTACLES5 children[5]
#define GHAST_TENTACLES6 children[6]
#define GHAST_TENTACLES7 children[7]
#define GHAST_TENTACLES8 children[8]
#define GHAST_TENTACLES9 children[9]
// mod_squid
#define SQUID_SQUIDBODY children[0]
#define SQUID_SQUIDTENTACLES1 children[1]
#define SQUID_SQUIDTENTACLES2 children[2]
#define SQUID_SQUIDTENTACLES3 children[3]
#define SQUID_SQUIDTENTACLES4 children[4]
#define SQUID_SQUIDTENTACLES5 children[5]
#define SQUID_SQUIDTENTACLES6 children[6]
#define SQUID_SQUIDTENTACLES7 children[7]
#define SQUID_SQUIDTENTACLES8 children[8]
// mod_villager
#define VILLAGER_VILLAGERHEAD children[0]
#define VILLAGER_VILLAGERBODY children[1]
#define VILLAGER_VILLAGERARMS children[2]
#define VILLAGER_RIGHTVILLAGERLEG children[3]
#define VILLAGER_LEFTVILLAGERLEG children[4]
#define VILLAGER_VILLAGERNOSE children[5]
// mod_irongolem
#define IRONGOLEM_IRONGOLEMHEAD children[0]
#define IRONGOLEM_IRONGOLEMBODY children[1]
#define IRONGOLEM_IRONGOLEMRIGHTARM children[2]
#define IRONGOLEM_IRONGOLEMLEFTARM children[3]
#define IRONGOLEM_IRONGOLEMLEFTLEG children[4]
#define IRONGOLEM_IRONGOLEMRIGHTLEG children[5]
// mod_bat
#define BAT_BATHEAD children[0]
#define BAT_BATBODY children[1]
#define BAT_BATRIGHTWING children[2]
#define BAT_BATLEFTWING children[3]
#define BAT_BATOUTERRIGHTWING children[4]
#define BAT_BATOUTERLEFTWING children[5]
// mod_guardian
#define GUARDIAN_GUARDIANBODY children[0]
#define GUARDIAN_GUARDIANEYE children[1]
#define GUARDIAN_GUARDIANSPINES1 children[2]
#define GUARDIAN_GUARDIANSPINES2 children[3]
#define GUARDIAN_GUARDIANSPINES3 children[4]
#define GUARDIAN_GUARDIANSPINES4 children[5]
#define GUARDIAN_GUARDIANSPINES5 children[6]
#define GUARDIAN_GUARDIANSPINES6 children[7]
#define GUARDIAN_GUARDIANSPINES7 children[8]
#define GUARDIAN_GUARDIANSPINES8 children[9]
#define GUARDIAN_GUARDIANSPINES9 children[10]
#define GUARDIAN_GUARDIANSPINES10 children[11]
#define GUARDIAN_GUARDIANSPINES11 children[12]
#define GUARDIAN_GUARDIANSPINES12 children[13]
#define GUARDIAN_GUARDIANTAIL1 children[14]
#define GUARDIAN_GUARDIANTAIL2 children[15]
#define GUARDIAN_GUARDIANTAIL3 children[16]
// mod_shulker
#define SHULKER_FIELD_187066_A children[0]
// mod_dragon
#define DRAGON_HEAD children[0]
#define DRAGON_SPINE children[1]
#define DRAGON_JAW children[2]
#define DRAGON_BODY children[3]
#define DRAGON_REARLEG children[4]
#define DRAGON_FRONTLEG children[5]
#define DRAGON_REARLEGTIP children[6]
#define DRAGON_FRONTLEGTIP children[7]
#define DRAGON_REARFOOT children[8]
#define DRAGON_FRONTFOOT children[9]
#define DRAGON_WING children[10]
#define DRAGON_WINGTIP children[11]
// mod_endercrystal
#define ENDERCRYSTAL_CUBE children[0]
#define ENDERCRYSTAL_GLASS children[1]
#define ENDERCRYSTAL_BASE children[2]
// mod_endercrystalbaseless
#define ENDERCRYSTALBASELESS_CUBE children[0]
#define ENDERCRYSTALBASELESS_GLASS children[1]
#define ENDERCRYSTALBASELESS_BASE children[2]
// mod_wither
#define WITHER_WITHERHEAD1 children[0]
#define WITHER_WITHERHEAD2 children[1]
#define WITHER_WITHERHEAD3 children[2]
#define WITHER_WITHERBODY1 children[3]
#define WITHER_WITHERBODY2 children[4]
#define WITHER_WITHERBODY3 children[5]
// mod_witheraura
#define WITHERAURA_WITHERHEAD1 children[0]
#define WITHERAURA_WITHERHEAD2 children[1]
#define WITHERAURA_WITHERHEAD3 children[2]
#define WITHERAURA_WITHERBODY1 children[3]
#define WITHERAURA_WITHERBODY2 children[4]
#define WITHERAURA_WITHERBODY3 children[5]
// mod_leashknot
#define LEASHKNOT_FIELD_110723_A children[0]
// mod_witherskull
#define WITHERSKULL_SKELETONHEAD children[0]
// mod_shulkerbullet
#define SHULKERBULLET_FIELD_187069_A children[0]
// mod_armorstand
#define ARMORSTAND_STANDRIGHTSIDE children[0]
#define ARMORSTAND_STANDLEFTSIDE children[1]
#define ARMORSTAND_STANDWAIST children[2]
#define ARMORSTAND_STANDBASE children[3]
#define ARMORSTAND_BIPEDHEAD children[4]
#define ARMORSTAND_BIPEDHEADWEAR children[5]
#define ARMORSTAND_BIPEDBODY children[6]
#define ARMORSTAND_BIPEDRIGHTARM children[7]
#define ARMORSTAND_BIPEDLEFTARM children[8]
#define ARMORSTAND_BIPEDRIGHTLEG children[9]
#define ARMORSTAND_BIPEDLEFTLEG children[10]
// mod_armorstandleggings
#define ARMORSTANDLEGGINGS_BIPEDHEAD children[0]
#define ARMORSTANDLEGGINGS_BIPEDHEADWEAR children[1]
#define ARMORSTANDLEGGINGS_BIPEDBODY children[2]
#define ARMORSTANDLEGGINGS_BIPEDRIGHTARM children[3]
#define ARMORSTANDLEGGINGS_BIPEDLEFTARM children[4]
#define ARMORSTANDLEGGINGS_BIPEDRIGHTLEG children[5]
#define ARMORSTANDLEGGINGS_BIPEDLEFTLEG children[6]
// mod_armorstandarmor
#define ARMORSTANDARMOR_BIPEDHEAD children[0]
#define ARMORSTANDARMOR_BIPEDHEADWEAR children[1]
#define ARMORSTANDARMOR_BIPEDBODY children[2]
#define ARMORSTANDARMOR_BIPEDRIGHTARM children[3]
#define ARMORSTANDARMOR_BIPEDLEFTARM children[4]
#define ARMORSTANDARMOR_BIPEDRIGHTLEG children[5]
#define ARMORSTANDARMOR_BIPEDLEFTLEG children[6]
// mod_minecarttnt
#define MINECARTTNT_SIDEMODELS1 children[0]
#define MINECARTTNT_SIDEMODELS2 children[1]
#define MINECARTTNT_SIDEMODELS3 children[2]
#define MINECARTTNT_SIDEMODELS4 children[3]
#define MINECARTTNT_SIDEMODELS5 children[4]
#define MINECARTTNT_SIDEMODELS6 children[5]
// mod_minecartmobspawner
#define MINECARTMOBSPAWNER_SIDEMODELS1 children[0]
#define MINECARTMOBSPAWNER_SIDEMODELS2 children[1]
#define MINECARTMOBSPAWNER_SIDEMODELS3 children[2]
#define MINECARTMOBSPAWNER_SIDEMODELS4 children[3]
#define MINECARTMOBSPAWNER_SIDEMODELS5 children[4]
#define MINECARTMOBSPAWNER_SIDEMODELS6 children[5]
// mod_minecart
#define MINECART_SIDEMODELS1 children[0]
#define MINECART_SIDEMODELS2 children[1]
#define MINECART_SIDEMODELS3 children[2]
#define MINECART_SIDEMODELS4 children[3]
#define MINECART_SIDEMODELS5 children[4]
#define MINECART_SIDEMODELS6 children[5]
// mod_boat
#define BOAT_BOATSIDES1 children[0]
#define BOAT_BOATSIDES2 children[1]
#define BOAT_BOATSIDES3 children[2]
#define BOAT_BOATSIDES4 children[3]
#define BOAT_BOATSIDES5 children[4]
#define BOAT_BOATSIDES21 children[5]
#define BOAT_BOATSIDES22 children[6]
#define BOAT_BOATFLOOR children[7]
// mod_horse
#define HORSE_HEAD children[0]
#define HORSE_HORSEUNK2 children[1]
#define HORSE_HORSEUNK1 children[2]
#define HORSE_HORSELEFTEAR children[3]
#define HORSE_HORSERIGHTEAR children[4]
#define HORSE_MULELEFTEAR children[5]
#define HORSE_MULERIGHTEAR children[6]
#define HORSE_NECK children[7]
#define HORSE_HORSEFACEROPES children[8]
#define HORSE_MANE children[9]
#define HORSE_BODY children[10]
#define HORSE_TAILBASE children[11]
#define HORSE_TAILMIDDLE children[12]
#define HORSE_TAILTIP children[13]
#define HORSE_BACKLEFTLEG children[14]
#define HORSE_BACKLEFTSHIN children[15]
#define HORSE_BACKLEFTHOOF children[16]
#define HORSE_BACKRIGHTLEG children[17]
#define HORSE_BACKRIGHTSHIN children[18]
#define HORSE_BACKRIGHTHOOF children[19]
#define HORSE_FRONTLEFTLEG children[20]
#define HORSE_FRONTLEFTSHIN children[21]
#define HORSE_FRONTLEFTHOOF children[22]
#define HORSE_FRONTRIGHTLEG children[23]
#define HORSE_FRONTRIGHTSHIN children[24]
#define HORSE_FRONTRIGHTHOOF children[25]
#define HORSE_MULELEFTCHEST children[26]
#define HORSE_MULERIGHTCHEST children[27]
#define HORSE_HORSESADDLEBOTTOM children[28]
#define HORSE_HORSESADDLEFRONT children[29]
#define HORSE_HORSESADDLEBACK children[30]
#define HORSE_HORSELEFTSADDLEROPE children[31]
#define HORSE_HORSELEFTSADDLEMETAL children[32]
#define HORSE_HORSERIGHTSADDLEROPE children[33]
#define HORSE_HORSERIGHTSADDLEMETAL children[34]
#define HORSE_HORSELEFTFACEMETAL children[35]
#define HORSE_HORSERIGHTFACEMETAL children[36]
#define HORSE_HORSELEFTREIN children[37]
#define HORSE_HORSERIGHTREIN children[38]
// mod_player
#define PLAYER_BIPEDLEFTARMWEAR children[0]
#define PLAYER_BIPEDRIGHTARMWEAR children[1]
#define PLAYER_BIPEDLEFTLEGWEAR children[2]
#define PLAYER_BIPEDRIGHTLEGWEAR children[3]
#define PLAYER_BIPEDBODYWEAR children[4]
#define PLAYER_BIPEDHEAD children[5]
#define PLAYER_BIPEDHEADWEAR children[6]
#define PLAYER_BIPEDBODY children[7]
#define PLAYER_BIPEDRIGHTARM children[8]
#define PLAYER_BIPEDLEFTARM children[9]
#define PLAYER_BIPEDRIGHTLEG children[10]
#define PLAYER_BIPEDLEFTLEG children[11]
// mod_playerleggings
#define PLAYERLEGGINGS_BIPEDHEAD children[0]
#define PLAYERLEGGINGS_BIPEDHEADWEAR children[1]
#define PLAYERLEGGINGS_BIPEDBODY children[2]
#define PLAYERLEGGINGS_BIPEDRIGHTARM children[3]
#define PLAYERLEGGINGS_BIPEDLEFTARM children[4]
#define PLAYERLEGGINGS_BIPEDRIGHTLEG children[5]
#define PLAYERLEGGINGS_BIPEDLEFTLEG children[6]
// mod_playerarmor
#define PLAYERARMOR_BIPEDHEAD children[0]
#define PLAYERARMOR_BIPEDHEADWEAR children[1]
#define PLAYERARMOR_BIPEDBODY children[2]
#define PLAYERARMOR_BIPEDRIGHTARM children[3]
#define PLAYERARMOR_BIPEDLEFTARM children[4]
#define PLAYERARMOR_BIPEDRIGHTLEG children[5]
#define PLAYERARMOR_BIPEDLEFTLEG children[6]
// mod_playerelytra
#define PLAYERELYTRA_WING1 children[0]
#define PLAYERELYTRA_WING2 children[1]
// mod_splayer
#define SPLAYER_BIPEDLEFTARMWEAR children[0]
#define SPLAYER_BIPEDRIGHTARMWEAR children[1]
#define SPLAYER_BIPEDLEFTLEGWEAR children[2]
#define SPLAYER_BIPEDRIGHTLEGWEAR children[3]
#define SPLAYER_BIPEDBODYWEAR children[4]
#define SPLAYER_BIPEDHEAD children[5]
#define SPLAYER_BIPEDHEADWEAR children[6]
#define SPLAYER_BIPEDBODY children[7]
#define SPLAYER_BIPEDRIGHTARM children[8]
#define SPLAYER_BIPEDLEFTARM children[9]
#define SPLAYER_BIPEDRIGHTLEG children[10]
#define SPLAYER_BIPEDLEFTLEG children[11]
// mod_splayerleggings
#define SPLAYERLEGGINGS_BIPEDHEAD children[0]
#define SPLAYERLEGGINGS_BIPEDHEADWEAR children[1]
#define SPLAYERLEGGINGS_BIPEDBODY children[2]
#define SPLAYERLEGGINGS_BIPEDRIGHTARM children[3]
#define SPLAYERLEGGINGS_BIPEDLEFTARM children[4]
#define SPLAYERLEGGINGS_BIPEDRIGHTLEG children[5]
#define SPLAYERLEGGINGS_BIPEDLEFTLEG children[6]
// mod_splayerarmor
#define SPLAYERARMOR_BIPEDHEAD children[0]
#define SPLAYERARMOR_BIPEDHEADWEAR children[1]
#define SPLAYERARMOR_BIPEDBODY children[2]
#define SPLAYERARMOR_BIPEDRIGHTARM children[3]
#define SPLAYERARMOR_BIPEDLEFTARM children[4]
#define SPLAYERARMOR_BIPEDRIGHTLEG children[5]
#define SPLAYERARMOR_BIPEDLEFTLEG children[6]
// mod_splayerelytra
#define SPLAYERELYTRA_WING1 children[0]
#define SPLAYERELYTRA_WING2 children[1]

struct modr {
		int txx;
		int txy;
		int txw;
		int txh;
		float rotX;
		float defRotX;
		float rotY;
		float defRotY;
		float rotZ;
		float defRotZ;
		float rpX;
		float defrpX;
		float rpY;
		float defrpY;
		float rpZ;
		float defrpZ;
		struct vao* vao;
		struct modr** children;
		size_t child_count;
};

void newModel(struct model* model, int width, int height);

void newModr(struct modr* modr, int txx, int txy, int txw, int txh, float rpX, float rpY, float rpZ);

void setModrAngles(struct modr* modr, float rotX, float rotY, float rotZ);

void setModrDefAngles(struct modr* modr, float rotX, float rotY, float rotZ);

void setModrAnglePoint(struct modr* modr, float rpX, float rpY, float rpZ);

void setModrDefAnglePoint(struct modr* modr, float rpX, float rpY, float rpZ);

void resetModr(struct modr* modr);

void resetModel(struct model* model);

void addModrChild(struct modr* modr, struct modr* child);

void addModelChild(struct model* model, struct modr* child);

void createModelCube(struct modr* modr, struct vertex_tex* vexs, float x, float y, float z, int width, int height, int depth, float scale, int mirror);

void drawModr(struct modr* modr);

void drawModel(struct model* model);

int loadTexturePNG(char* path, int id, int s);

int loadTexturesPNG(char* path, int wrap, int* w, int* h, int id, int s, char** map, int maps, int* smap);

void loadTextureData(int id, size_t width, size_t height, void* data, int s);

#endif /* MODELS_H_ */
