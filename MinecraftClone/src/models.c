/*
 * models.c
 *
 *  Created on: Feb 26, 2016
 *      Author: root
 */
#include "models.h"
#include <png.h>
#include <GL/gl.h>
#include "xstring.h"
#include <errno.h>
#include <dirent.h>
#include <math.h>
#include "globals.h"

void loadBaseModels() {
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/steve.png", TX_STEVE, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/creeper/creeper.png", TX_CREEPER, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/creeper/creeper_armor.png", TX_CREEPERARMOR, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/skeleton/skeleton.png", TX_SKELETON, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/skeleton/wither_skeleton.png", TX_WITHERSKELETON, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/spider/spider.png", TX_SPIDER, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/zombie/zombie.png", TX_ZOMBIE, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/zombie_villager/zombie_butcher.png", TX_ZOMBIEBUTCHER, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/zombie_villager/zombie_farmer.png", TX_ZOMBIEFARMER, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/zombie_villager/zombie_librarian.png", TX_ZOMBIELIBRARIAN, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/zombie_villager/zombie_priest.png", TX_ZOMBIEPRIEST, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/zombie_villager/zombie_smith.png", TX_ZOMBIESMITH, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/zombie_villager/zombie_villager.png", TX_ZOMBIEVILLAGER, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/slime/slime.png", TX_SLIME, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/ghast/ghast.png", TX_GHAST, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/ghast/ghast_shooting.png", TX_GHASTSHOOTING, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/zombie_pigman.png", TX_ZPIGMAN, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/enderman/enderman.png", TX_ENDERMAN, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/enderman/enderman_eyes.png", TX_ENDERMANEYES, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/spider/cave_spider.png", TX_CAVESPIDER, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/silverfish.png", TX_SILVERFISH, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/blaze.png", TX_BLAZE, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/slime/magmacube.png", TX_MAGMACUBE, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/enderdragon/dragon.png", TX_ENDERDRAGON, 1);
	//TODO explosing, eyes, and fireball!
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/wither/wither.png", TX_WITHER, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/wither/wither_armor.png", TX_WITHERARMOR, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/wither/wither_invulnerable.png", TX_WITHERINVULNERABLE, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/bat.png", TX_BAT, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/witch.png", TX_WITCH, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/endermite.png", TX_ENDERMITE, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/guardian.png", TX_GUARDIAN, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/guardian_elder.png", TX_ELDERGUARDIAN, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/shulker/endergolem.png", TX_SHULKER, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/shulker/spark.png", TX_SHULKERSPARK, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/pig/pig.png", TX_PIG, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/pig/pig_saddle.png", TX_PIGSADDLE, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/sheep/sheep.png", TX_SHEEP, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/sheep/sheep_fur.png", TX_SHEEPFUR, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/cow/cow.png", TX_COW, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/chicken.png", TX_CHICKEN, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/squid.png", TX_SQUID, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/wolf/wolf.png", TX_WOLF, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/wolf/wold_angry.png", TX_WOLFANGRY, 1);
	//TODO collar
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/wolf/wolf_tame.png", TX_WOLFTAME, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/cow/mooshroom.png", TX_MOOSHROOM, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/snowman.png", TX_SNOWMAN, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/cat/ocelot.png", TX_OCELOT, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/cat/black.png", TX_OCELOTBLACK, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/cat/red.png", TX_OCELOTRED, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/cat/siamese.png", TX_OCELOTSIAMESE, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/iron_golem.png", TX_IRONGOLEM, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/horse/horse_black.png", TX_HORSEBLACK, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/horse/donkey.png", TX_HORSEDONKEY, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/horse/horse_brown.png", TX_HORSEBROWN, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/horse/horse_chestnut.png", TX_HORSECHESTNUT, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/horse/horse_creamy.png", TX_HORSECREAMY, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/horse/horse_darkbrown.png", TX_HORSEDARKBROWN, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/horse/horse_gray.png", TX_HORSEGRAY, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/horse/horse_skeleton.png", TX_HORSESKELETON, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/horse/horse_white.png", TX_HORSEWHITE, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/horse/horse_zombie.png", TX_HORSEZOMBIE, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/horse/muke.png", TX_HORSEMULE, 1);
	//TODO: there are some marking textures for horeses too!
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/horse/armor/house_armor_diamond.png", TX_HORSEDIAMONDARMOR, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/horse/armor/house_armor_gold.png", TX_HORSEGOLDARMOR, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/horse/armor/house_armor_iron.png", TX_HORSEIRONARMOR, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/rabbit/black.png", TX_RABBITBLACK, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/rabbit/brown.png", TX_RABBITBROWN, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/rabbit/caerbannog.png", TX_RABBITCAERBANNOG, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/rabbit/gold.png", TX_RABBITGOLD, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/rabbit/salt.png", TX_RABBITSALT, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/rabbit/toast.png", TX_RABBITTOAST, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/rabbit/white.png", TX_RABBITWHITE, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/rabbit/white_splotched.png", TX_RABBITWHITESPLOTCH, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/villager/butcher.png", TX_VILLAGERBUTCHER, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/villager/farmer.png", TX_VILLAGERFARMER, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/villager/librarian.png", TX_VILLAGERLIBRARIAN, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/villager/priest.png", TX_VILLAGERPRIEST, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/villager/smith.png", TX_VILLAGERSMITH, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/villager/villager.png", TX_VILLAGER, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/boat/boat_acacia.png", TX_BOATACACIA, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/boat/boat_birch.png", TX_BOATBIRCH, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/boat/boat_darkoak.png", TX_BOATDARKOAK, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/boat/boat_jungle.png", TX_BOATJUNGLE, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/boat/boat_oak.png", TX_BOATOAK, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/boat/boat_spruce.png", TX_BOATSPRUCE, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/minecart.png", TX_MINECART, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/endercrystal/endercrystal_beam.png", TX_ENDERCRYSTALBEAM, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/endercrystal/endercrystal.png", TX_ENDERCRYSTAL, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/projectiles/arrow.png", TX_ARROW, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/lead_knot.png", TX_LEASHKNOT, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/armorstand/wood.png", TX_ARMORSTAND, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/projectiles/spectral_arrow.png", TX_SPECTRALARROW, 1);
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/projectiles/tipped_arrow.png", TX_TIPPEDARROW, 1);

	// mod_spider
	{
		newModel(&mod_spider, 64, 32);
		{
			struct modr* spiderhead = malloc(sizeof(struct modr));
			newModr(spiderhead, 32, 4, 64.0, 32.0, 0.0, 15.0, -3.0);
			struct vertex_tex cubes[24];
			createModelCube(spiderhead, &cubes[0], -4.0, -4.0, -8.0, 8.0, 8.0, 8.0, 0.0, 0);
			spiderhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, spiderhead->vao, 1, 0);
			addModelChild(&mod_spider, spiderhead);
		}
		{
			struct modr* spiderneck = malloc(sizeof(struct modr));
			newModr(spiderneck, 0, 0, 64.0, 32.0, 0.0, 15.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(spiderneck, &cubes[0], -3.0, -3.0, -3.0, 6.0, 6.0, 6.0, 0.0, 0);
			spiderneck->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, spiderneck->vao, 1, 0);
			addModelChild(&mod_spider, spiderneck);
		}
		{
			struct modr* spiderbody = malloc(sizeof(struct modr));
			newModr(spiderbody, 0, 12, 64.0, 32.0, 0.0, 15.0, 9.0);
			struct vertex_tex cubes[24];
			createModelCube(spiderbody, &cubes[0], -5.0, -4.0, -6.0, 10.0, 8.0, 12.0, 0.0, 0);
			spiderbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, spiderbody->vao, 1, 0);
			addModelChild(&mod_spider, spiderbody);
		}
		{
			struct modr* spiderleg1 = malloc(sizeof(struct modr));
			newModr(spiderleg1, 18, 0, 64.0, 32.0, -4.0, 15.0, 2.0);
			struct vertex_tex cubes[24];
			createModelCube(spiderleg1, &cubes[0], -15.0, -1.0, -1.0, 16.0, 2.0, 2.0, 0.0, 0);
			spiderleg1->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, spiderleg1->vao, 1, 0);
			addModelChild(&mod_spider, spiderleg1);
		}
		{
			struct modr* spiderleg2 = malloc(sizeof(struct modr));
			newModr(spiderleg2, 18, 0, 64.0, 32.0, 4.0, 15.0, 2.0);
			struct vertex_tex cubes[24];
			createModelCube(spiderleg2, &cubes[0], -1.0, -1.0, -1.0, 16.0, 2.0, 2.0, 0.0, 0);
			spiderleg2->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, spiderleg2->vao, 1, 0);
			addModelChild(&mod_spider, spiderleg2);
		}
		{
			struct modr* spiderleg3 = malloc(sizeof(struct modr));
			newModr(spiderleg3, 18, 0, 64.0, 32.0, -4.0, 15.0, 1.0);
			struct vertex_tex cubes[24];
			createModelCube(spiderleg3, &cubes[0], -15.0, -1.0, -1.0, 16.0, 2.0, 2.0, 0.0, 0);
			spiderleg3->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, spiderleg3->vao, 1, 0);
			addModelChild(&mod_spider, spiderleg3);
		}
		{
			struct modr* spiderleg4 = malloc(sizeof(struct modr));
			newModr(spiderleg4, 18, 0, 64.0, 32.0, 4.0, 15.0, 1.0);
			struct vertex_tex cubes[24];
			createModelCube(spiderleg4, &cubes[0], -1.0, -1.0, -1.0, 16.0, 2.0, 2.0, 0.0, 0);
			spiderleg4->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, spiderleg4->vao, 1, 0);
			addModelChild(&mod_spider, spiderleg4);
		}
		{
			struct modr* spiderleg5 = malloc(sizeof(struct modr));
			newModr(spiderleg5, 18, 0, 64.0, 32.0, -4.0, 15.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(spiderleg5, &cubes[0], -15.0, -1.0, -1.0, 16.0, 2.0, 2.0, 0.0, 0);
			spiderleg5->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, spiderleg5->vao, 1, 0);
			addModelChild(&mod_spider, spiderleg5);
		}
		{
			struct modr* spiderleg6 = malloc(sizeof(struct modr));
			newModr(spiderleg6, 18, 0, 64.0, 32.0, 4.0, 15.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(spiderleg6, &cubes[0], -1.0, -1.0, -1.0, 16.0, 2.0, 2.0, 0.0, 0);
			spiderleg6->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, spiderleg6->vao, 1, 0);
			addModelChild(&mod_spider, spiderleg6);
		}
		{
			struct modr* spiderleg7 = malloc(sizeof(struct modr));
			newModr(spiderleg7, 18, 0, 64.0, 32.0, -4.0, 15.0, -1.0);
			struct vertex_tex cubes[24];
			createModelCube(spiderleg7, &cubes[0], -15.0, -1.0, -1.0, 16.0, 2.0, 2.0, 0.0, 0);
			spiderleg7->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, spiderleg7->vao, 1, 0);
			addModelChild(&mod_spider, spiderleg7);
		}
		{
			struct modr* spiderleg8 = malloc(sizeof(struct modr));
			newModr(spiderleg8, 18, 0, 64.0, 32.0, 4.0, 15.0, -1.0);
			struct vertex_tex cubes[24];
			createModelCube(spiderleg8, &cubes[0], -1.0, -1.0, -1.0, 16.0, 2.0, 2.0, 0.0, 0);
			spiderleg8->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, spiderleg8->vao, 1, 0);
			addModelChild(&mod_spider, spiderleg8);
		}
	}
	// mod_pig
	{
		newModel(&mod_pig, 64, 32);
		{
			struct modr* head = malloc(sizeof(struct modr));
			newModr(head, 16, 16, 64.0, 32.0, 0.0, 12.0, -6.0);
			struct vertex_tex cubes[48];
			createModelCube(head, &cubes[0], -4.0, -4.0, -8.0, 8.0, 8.0, 8.0, 0.0, 0);
			createModelCube(head, &cubes[24], -2.0, 0.0, -9.0, 4.0, 3.0, 1.0, 0.0, 0);
			head->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 48, head->vao, 1, 0);
			addModelChild(&mod_pig, head);
		}
		{
			struct modr* body = malloc(sizeof(struct modr));
			newModr(body, 28, 8, 64.0, 32.0, 0.0, 11.0, 2.0);
			struct vertex_tex cubes[24];
			createModelCube(body, &cubes[0], -5.0, -10.0, -7.0, 10.0, 16.0, 8.0, 0.0, 0);
			body->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, body->vao, 1, 0);
			addModelChild(&mod_pig, body);
		}
		{
			struct modr* leg1 = malloc(sizeof(struct modr));
			newModr(leg1, 0, 16, 64.0, 32.0, -3.0, 18.0, 7.0);
			struct vertex_tex cubes[24];
			createModelCube(leg1, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.0, 0);
			leg1->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg1->vao, 1, 0);
			addModelChild(&mod_pig, leg1);
		}
		{
			struct modr* leg2 = malloc(sizeof(struct modr));
			newModr(leg2, 0, 16, 64.0, 32.0, 3.0, 18.0, 7.0);
			struct vertex_tex cubes[24];
			createModelCube(leg2, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.0, 0);
			leg2->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg2->vao, 1, 0);
			addModelChild(&mod_pig, leg2);
		}
		{
			struct modr* leg3 = malloc(sizeof(struct modr));
			newModr(leg3, 0, 16, 64.0, 32.0, -3.0, 18.0, -5.0);
			struct vertex_tex cubes[24];
			createModelCube(leg3, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.0, 0);
			leg3->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg3->vao, 1, 0);
			addModelChild(&mod_pig, leg3);
		}
		{
			struct modr* leg4 = malloc(sizeof(struct modr));
			newModr(leg4, 0, 16, 64.0, 32.0, 3.0, 18.0, -5.0);
			struct vertex_tex cubes[24];
			createModelCube(leg4, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.0, 0);
			leg4->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg4->vao, 1, 0);
			addModelChild(&mod_pig, leg4);
		}
	}
	// mod_pigsaddle
	{
		newModel(&mod_pigsaddle, 64, 32);
		{
			struct modr* head = malloc(sizeof(struct modr));
			newModr(head, 16, 16, 64.0, 32.0, 0.0, 12.0, -6.0);
			struct vertex_tex cubes[48];
			createModelCube(head, &cubes[0], -4.0, -4.0, -8.0, 8.0, 8.0, 8.0, 0.5, 0);
			createModelCube(head, &cubes[24], -2.0, 0.0, -9.0, 4.0, 3.0, 1.0, 0.5, 0);
			head->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 48, head->vao, 1, 0);
			addModelChild(&mod_pigsaddle, head);
		}
		{
			struct modr* body = malloc(sizeof(struct modr));
			newModr(body, 28, 8, 64.0, 32.0, 0.0, 11.0, 2.0);
			struct vertex_tex cubes[24];
			createModelCube(body, &cubes[0], -5.0, -10.0, -7.0, 10.0, 16.0, 8.0, 0.5, 0);
			body->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, body->vao, 1, 0);
			addModelChild(&mod_pigsaddle, body);
		}
		{
			struct modr* leg1 = malloc(sizeof(struct modr));
			newModr(leg1, 0, 16, 64.0, 32.0, -3.0, 18.0, 7.0);
			struct vertex_tex cubes[24];
			createModelCube(leg1, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.5, 0);
			leg1->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg1->vao, 1, 0);
			addModelChild(&mod_pigsaddle, leg1);
		}
		{
			struct modr* leg2 = malloc(sizeof(struct modr));
			newModr(leg2, 0, 16, 64.0, 32.0, 3.0, 18.0, 7.0);
			struct vertex_tex cubes[24];
			createModelCube(leg2, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.5, 0);
			leg2->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg2->vao, 1, 0);
			addModelChild(&mod_pigsaddle, leg2);
		}
		{
			struct modr* leg3 = malloc(sizeof(struct modr));
			newModr(leg3, 0, 16, 64.0, 32.0, -3.0, 18.0, -5.0);
			struct vertex_tex cubes[24];
			createModelCube(leg3, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.5, 0);
			leg3->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg3->vao, 1, 0);
			addModelChild(&mod_pigsaddle, leg3);
		}
		{
			struct modr* leg4 = malloc(sizeof(struct modr));
			newModr(leg4, 0, 16, 64.0, 32.0, 3.0, 18.0, -5.0);
			struct vertex_tex cubes[24];
			createModelCube(leg4, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.5, 0);
			leg4->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg4->vao, 1, 0);
			addModelChild(&mod_pigsaddle, leg4);
		}
	}
	// mod_sheep
	{
		newModel(&mod_sheep, 64, 32);
		{
			struct modr* head = malloc(sizeof(struct modr));
			newModr(head, 0, 0, 64.0, 32.0, 0.0, 6.0, -8.0);
			struct vertex_tex cubes[24];
			createModelCube(head, &cubes[0], -3.0, -4.0, -6.0, 6.0, 6.0, 8.0, 0.0, 0);
			head->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, head->vao, 1, 0);
			addModelChild(&mod_sheep, head);
		}
		{
			struct modr* body = malloc(sizeof(struct modr));
			newModr(body, 28, 8, 64.0, 32.0, 0.0, 5.0, 2.0);
			struct vertex_tex cubes[24];
			createModelCube(body, &cubes[0], -4.0, -10.0, -7.0, 8.0, 16.0, 6.0, 0.0, 0);
			body->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, body->vao, 1, 0);
			addModelChild(&mod_sheep, body);
		}
		{
			struct modr* leg1 = malloc(sizeof(struct modr));
			newModr(leg1, 0, 16, 64.0, 32.0, -3.0, 12.0, 7.0);
			struct vertex_tex cubes[24];
			createModelCube(leg1, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			leg1->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg1->vao, 1, 0);
			addModelChild(&mod_sheep, leg1);
		}
		{
			struct modr* leg2 = malloc(sizeof(struct modr));
			newModr(leg2, 0, 16, 64.0, 32.0, 3.0, 12.0, 7.0);
			struct vertex_tex cubes[24];
			createModelCube(leg2, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			leg2->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg2->vao, 1, 0);
			addModelChild(&mod_sheep, leg2);
		}
		{
			struct modr* leg3 = malloc(sizeof(struct modr));
			newModr(leg3, 0, 16, 64.0, 32.0, -3.0, 12.0, -5.0);
			struct vertex_tex cubes[24];
			createModelCube(leg3, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			leg3->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg3->vao, 1, 0);
			addModelChild(&mod_sheep, leg3);
		}
		{
			struct modr* leg4 = malloc(sizeof(struct modr));
			newModr(leg4, 0, 16, 64.0, 32.0, 3.0, 12.0, -5.0);
			struct vertex_tex cubes[24];
			createModelCube(leg4, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			leg4->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg4->vao, 1, 0);
			addModelChild(&mod_sheep, leg4);
		}
	}
	// mod_sheepwool
	{
		newModel(&mod_sheepwool, 64, 32);
		{
			struct modr* head = malloc(sizeof(struct modr));
			newModr(head, 0, 0, 64.0, 32.0, 0.0, 6.0, -8.0);
			struct vertex_tex cubes[24];
			createModelCube(head, &cubes[0], -3.0, -4.0, -4.0, 6.0, 6.0, 6.0, 0.6, 0);
			head->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, head->vao, 1, 0);
			addModelChild(&mod_sheepwool, head);
		}
		{
			struct modr* body = malloc(sizeof(struct modr));
			newModr(body, 28, 8, 64.0, 32.0, 0.0, 5.0, 2.0);
			struct vertex_tex cubes[24];
			createModelCube(body, &cubes[0], -4.0, -10.0, -7.0, 8.0, 16.0, 6.0, 1.75, 0);
			body->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, body->vao, 1, 0);
			addModelChild(&mod_sheepwool, body);
		}
		{
			struct modr* leg1 = malloc(sizeof(struct modr));
			newModr(leg1, 0, 16, 64.0, 32.0, -3.0, 12.0, 7.0);
			struct vertex_tex cubes[24];
			createModelCube(leg1, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.5, 0);
			leg1->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg1->vao, 1, 0);
			addModelChild(&mod_sheepwool, leg1);
		}
		{
			struct modr* leg2 = malloc(sizeof(struct modr));
			newModr(leg2, 0, 16, 64.0, 32.0, 3.0, 12.0, 7.0);
			struct vertex_tex cubes[24];
			createModelCube(leg2, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.5, 0);
			leg2->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg2->vao, 1, 0);
			addModelChild(&mod_sheepwool, leg2);
		}
		{
			struct modr* leg3 = malloc(sizeof(struct modr));
			newModr(leg3, 0, 16, 64.0, 32.0, -3.0, 12.0, -5.0);
			struct vertex_tex cubes[24];
			createModelCube(leg3, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.5, 0);
			leg3->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg3->vao, 1, 0);
			addModelChild(&mod_sheepwool, leg3);
		}
		{
			struct modr* leg4 = malloc(sizeof(struct modr));
			newModr(leg4, 0, 16, 64.0, 32.0, 3.0, 12.0, -5.0);
			struct vertex_tex cubes[24];
			createModelCube(leg4, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.5, 0);
			leg4->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg4->vao, 1, 0);
			addModelChild(&mod_sheepwool, leg4);
		}
	}
	// mod_cow
	{
		newModel(&mod_cow, 64, 32);
		{
			struct modr* head = malloc(sizeof(struct modr));
			newModr(head, 22, 0, 64.0, 32.0, 0.0, 4.0, -8.0);
			struct vertex_tex cubes[72];
			createModelCube(head, &cubes[0], -4.0, -4.0, -6.0, 8.0, 8.0, 6.0, 0.0, 0);
			createModelCube(head, &cubes[24], -5.0, -5.0, -4.0, 1.0, 3.0, 1.0, 0.0, 0);
			createModelCube(head, &cubes[48], 4.0, -5.0, -4.0, 1.0, 3.0, 1.0, 0.0, 0);
			head->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 72, head->vao, 1, 0);
			addModelChild(&mod_cow, head);
		}
		{
			struct modr* body = malloc(sizeof(struct modr));
			newModr(body, 52, 0, 64.0, 32.0, 0.0, 5.0, 2.0);
			struct vertex_tex cubes[48];
			createModelCube(body, &cubes[0], -6.0, -10.0, -7.0, 12.0, 18.0, 10.0, 0.0, 0);
			createModelCube(body, &cubes[24], -2.0, 2.0, -8.0, 4.0, 6.0, 1.0, 0.0, 0);
			body->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 48, body->vao, 1, 0);
			addModelChild(&mod_cow, body);
		}
		{
			struct modr* leg1 = malloc(sizeof(struct modr));
			newModr(leg1, 0, 16, 64.0, 32.0, -4.0, 12.0, 7.0);
			struct vertex_tex cubes[24];
			createModelCube(leg1, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			leg1->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg1->vao, 1, 0);
			addModelChild(&mod_cow, leg1);
		}
		{
			struct modr* leg2 = malloc(sizeof(struct modr));
			newModr(leg2, 0, 16, 64.0, 32.0, 4.0, 12.0, 7.0);
			struct vertex_tex cubes[24];
			createModelCube(leg2, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			leg2->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg2->vao, 1, 0);
			addModelChild(&mod_cow, leg2);
		}
		{
			struct modr* leg3 = malloc(sizeof(struct modr));
			newModr(leg3, 0, 16, 64.0, 32.0, -4.0, 12.0, -6.0);
			struct vertex_tex cubes[24];
			createModelCube(leg3, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			leg3->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg3->vao, 1, 0);
			addModelChild(&mod_cow, leg3);
		}
		{
			struct modr* leg4 = malloc(sizeof(struct modr));
			newModr(leg4, 0, 16, 64.0, 32.0, 4.0, 12.0, -6.0);
			struct vertex_tex cubes[24];
			createModelCube(leg4, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			leg4->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg4->vao, 1, 0);
			addModelChild(&mod_cow, leg4);
		}
	}
	// mod_wolf
	{
		newModel(&mod_wolf, 64, 32);
		{
			struct modr* wolfheadmain = malloc(sizeof(struct modr));
			newModr(wolfheadmain, 0, 10, 64.0, 32.0, -1.0, 13.5, -7.0);
			struct vertex_tex cubes[96];
			createModelCube(wolfheadmain, &cubes[0], -2.0, -3.0, -2.0, 6.0, 6.0, 4.0, 0.0, 0);
			createModelCube(wolfheadmain, &cubes[24], -2.0, -5.0, 0.0, 2.0, 2.0, 1.0, 0.0, 0);
			createModelCube(wolfheadmain, &cubes[48], 2.0, -5.0, 0.0, 2.0, 2.0, 1.0, 0.0, 0);
			createModelCube(wolfheadmain, &cubes[72], -0.5, 0.0, -5.0, 3.0, 3.0, 4.0, 0.0, 0);
			wolfheadmain->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 96, wolfheadmain->vao, 1, 0);
			addModelChild(&mod_wolf, wolfheadmain);
		}
		{
			struct modr* wolfbody = malloc(sizeof(struct modr));
			newModr(wolfbody, 18, 14, 64.0, 32.0, 0.0, 14.0, 2.0);
			struct vertex_tex cubes[24];
			createModelCube(wolfbody, &cubes[0], -3.0, -2.0, -3.0, 6.0, 9.0, 6.0, 0.0, 0);
			wolfbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, wolfbody->vao, 1, 0);
			addModelChild(&mod_wolf, wolfbody);
		}
		{
			struct modr* wolfleg1 = malloc(sizeof(struct modr));
			newModr(wolfleg1, 0, 18, 64.0, 32.0, -2.5, 16.0, 7.0);
			struct vertex_tex cubes[24];
			createModelCube(wolfleg1, &cubes[0], 0.0, 0.0, -1.0, 2.0, 8.0, 2.0, 0.0, 0);
			wolfleg1->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, wolfleg1->vao, 1, 0);
			addModelChild(&mod_wolf, wolfleg1);
		}
		{
			struct modr* wolfleg2 = malloc(sizeof(struct modr));
			newModr(wolfleg2, 0, 18, 64.0, 32.0, 0.5, 16.0, 7.0);
			struct vertex_tex cubes[24];
			createModelCube(wolfleg2, &cubes[0], 0.0, 0.0, -1.0, 2.0, 8.0, 2.0, 0.0, 0);
			wolfleg2->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, wolfleg2->vao, 1, 0);
			addModelChild(&mod_wolf, wolfleg2);
		}
		{
			struct modr* wolfleg3 = malloc(sizeof(struct modr));
			newModr(wolfleg3, 0, 18, 64.0, 32.0, -2.5, 16.0, -4.0);
			struct vertex_tex cubes[24];
			createModelCube(wolfleg3, &cubes[0], 0.0, 0.0, -1.0, 2.0, 8.0, 2.0, 0.0, 0);
			wolfleg3->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, wolfleg3->vao, 1, 0);
			addModelChild(&mod_wolf, wolfleg3);
		}
		{
			struct modr* wolfleg4 = malloc(sizeof(struct modr));
			newModr(wolfleg4, 0, 18, 64.0, 32.0, 0.5, 16.0, -4.0);
			struct vertex_tex cubes[24];
			createModelCube(wolfleg4, &cubes[0], 0.0, 0.0, -1.0, 2.0, 8.0, 2.0, 0.0, 0);
			wolfleg4->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, wolfleg4->vao, 1, 0);
			addModelChild(&mod_wolf, wolfleg4);
		}
	}
	// mod_chicken
	{
		newModel(&mod_chicken, 64, 32);
		{
			struct modr* head = malloc(sizeof(struct modr));
			newModr(head, 0, 0, 64.0, 32.0, 0.0, 15.0, -4.0);
			struct vertex_tex cubes[24];
			createModelCube(head, &cubes[0], -2.0, -6.0, -2.0, 4.0, 6.0, 3.0, 0.0, 0);
			head->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, head->vao, 1, 0);
			addModelChild(&mod_chicken, head);
		}
		{
			struct modr* body = malloc(sizeof(struct modr));
			newModr(body, 0, 9, 64.0, 32.0, 0.0, 16.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(body, &cubes[0], -3.0, -4.0, -3.0, 6.0, 8.0, 6.0, 0.0, 0);
			body->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, body->vao, 1, 0);
			addModelChild(&mod_chicken, body);
		}
		{
			struct modr* rightleg = malloc(sizeof(struct modr));
			newModr(rightleg, 26, 0, 64.0, 32.0, -2.0, 19.0, 1.0);
			struct vertex_tex cubes[24];
			createModelCube(rightleg, &cubes[0], -1.0, 0.0, -3.0, 3.0, 5.0, 3.0, 0.0, 0);
			rightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, rightleg->vao, 1, 0);
			addModelChild(&mod_chicken, rightleg);
		}
		{
			struct modr* leftleg = malloc(sizeof(struct modr));
			newModr(leftleg, 26, 0, 64.0, 32.0, 1.0, 19.0, 1.0);
			struct vertex_tex cubes[24];
			createModelCube(leftleg, &cubes[0], -1.0, 0.0, -3.0, 3.0, 5.0, 3.0, 0.0, 0);
			leftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leftleg->vao, 1, 0);
			addModelChild(&mod_chicken, leftleg);
		}
		{
			struct modr* rightwing = malloc(sizeof(struct modr));
			newModr(rightwing, 24, 13, 64.0, 32.0, -4.0, 13.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(rightwing, &cubes[0], 0.0, 0.0, -3.0, 1.0, 4.0, 6.0, 0.0, 0);
			rightwing->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, rightwing->vao, 1, 0);
			addModelChild(&mod_chicken, rightwing);
		}
		{
			struct modr* leftwing = malloc(sizeof(struct modr));
			newModr(leftwing, 24, 13, 64.0, 32.0, 4.0, 13.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(leftwing, &cubes[0], -1.0, 0.0, -3.0, 1.0, 4.0, 6.0, 0.0, 0);
			leftwing->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leftwing->vao, 1, 0);
			addModelChild(&mod_chicken, leftwing);
		}
		{
			struct modr* bill = malloc(sizeof(struct modr));
			newModr(bill, 14, 0, 64.0, 32.0, 0.0, 15.0, -4.0);
			struct vertex_tex cubes[24];
			createModelCube(bill, &cubes[0], -2.0, -4.0, -4.0, 4.0, 2.0, 2.0, 0.0, 0);
			bill->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bill->vao, 1, 0);
			addModelChild(&mod_chicken, bill);
		}
		{
			struct modr* chin = malloc(sizeof(struct modr));
			newModr(chin, 14, 4, 64.0, 32.0, 0.0, 15.0, -4.0);
			struct vertex_tex cubes[24];
			createModelCube(chin, &cubes[0], -1.0, -2.0, -3.0, 2.0, 2.0, 2.0, 0.0, 0);
			chin->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, chin->vao, 1, 0);
			addModelChild(&mod_chicken, chin);
		}
	}
	// mod_ocelot
	{
		newModel(&mod_ocelot, 64, 32);
	}
	// mod_rabbit
	{
		newModel(&mod_rabbit, 64, 32);
	}
	// mod_silverfish
	{
		newModel(&mod_silverfish, 64, 32);
	}
	// mod_endermite
	{
		newModel(&mod_endermite, 64, 32);
	}
	// mod_creeper
	{
		newModel(&mod_creeper, 64, 32);
		{
			struct modr* head = malloc(sizeof(struct modr));
			newModr(head, 0, 0, 64.0, 32.0, 0.0, 6.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(head, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.0, 0);
			head->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, head->vao, 1, 0);
			addModelChild(&mod_creeper, head);
		}
		{
			struct modr* creeperarmor = malloc(sizeof(struct modr));
			newModr(creeperarmor, 32, 0, 64.0, 32.0, 0.0, 6.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(creeperarmor, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.5, 0);
			creeperarmor->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, creeperarmor->vao, 1, 0);
			addModelChild(&mod_creeper, creeperarmor);
		}
		{
			struct modr* body = malloc(sizeof(struct modr));
			newModr(body, 16, 16, 64.0, 32.0, 0.0, 6.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(body, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 0.0, 0);
			body->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, body->vao, 1, 0);
			addModelChild(&mod_creeper, body);
		}
		{
			struct modr* leg1 = malloc(sizeof(struct modr));
			newModr(leg1, 0, 16, 64.0, 32.0, -2.0, 18.0, 4.0);
			struct vertex_tex cubes[24];
			createModelCube(leg1, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.0, 0);
			leg1->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg1->vao, 1, 0);
			addModelChild(&mod_creeper, leg1);
		}
		{
			struct modr* leg2 = malloc(sizeof(struct modr));
			newModr(leg2, 0, 16, 64.0, 32.0, 2.0, 18.0, 4.0);
			struct vertex_tex cubes[24];
			createModelCube(leg2, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.0, 0);
			leg2->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg2->vao, 1, 0);
			addModelChild(&mod_creeper, leg2);
		}
		{
			struct modr* leg3 = malloc(sizeof(struct modr));
			newModr(leg3, 0, 16, 64.0, 32.0, -2.0, 18.0, -4.0);
			struct vertex_tex cubes[24];
			createModelCube(leg3, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.0, 0);
			leg3->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg3->vao, 1, 0);
			addModelChild(&mod_creeper, leg3);
		}
		{
			struct modr* leg4 = malloc(sizeof(struct modr));
			newModr(leg4, 0, 16, 64.0, 32.0, 2.0, 18.0, -4.0);
			struct vertex_tex cubes[24];
			createModelCube(leg4, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 0.0, 0);
			leg4->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg4->vao, 1, 0);
			addModelChild(&mod_creeper, leg4);
		}
	}
	// mod_creepercharge
	{
		newModel(&mod_creepercharge, 64, 32);
		{
			struct modr* head = malloc(sizeof(struct modr));
			newModr(head, 0, 0, 64.0, 32.0, 0.0, 6.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(head, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 2.0, 0);
			head->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, head->vao, 1, 0);
			addModelChild(&mod_creepercharge, head);
		}
		{
			struct modr* creeperarmor = malloc(sizeof(struct modr));
			newModr(creeperarmor, 32, 0, 64.0, 32.0, 0.0, 6.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(creeperarmor, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 2.5, 0);
			creeperarmor->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, creeperarmor->vao, 1, 0);
			addModelChild(&mod_creepercharge, creeperarmor);
		}
		{
			struct modr* body = malloc(sizeof(struct modr));
			newModr(body, 16, 16, 64.0, 32.0, 0.0, 6.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(body, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 2.0, 0);
			body->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, body->vao, 1, 0);
			addModelChild(&mod_creepercharge, body);
		}
		{
			struct modr* leg1 = malloc(sizeof(struct modr));
			newModr(leg1, 0, 16, 64.0, 32.0, -2.0, 18.0, 4.0);
			struct vertex_tex cubes[24];
			createModelCube(leg1, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 2.0, 0);
			leg1->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg1->vao, 1, 0);
			addModelChild(&mod_creepercharge, leg1);
		}
		{
			struct modr* leg2 = malloc(sizeof(struct modr));
			newModr(leg2, 0, 16, 64.0, 32.0, 2.0, 18.0, 4.0);
			struct vertex_tex cubes[24];
			createModelCube(leg2, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 2.0, 0);
			leg2->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg2->vao, 1, 0);
			addModelChild(&mod_creepercharge, leg2);
		}
		{
			struct modr* leg3 = malloc(sizeof(struct modr));
			newModr(leg3, 0, 16, 64.0, 32.0, -2.0, 18.0, -4.0);
			struct vertex_tex cubes[24];
			createModelCube(leg3, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 2.0, 0);
			leg3->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg3->vao, 1, 0);
			addModelChild(&mod_creepercharge, leg3);
		}
		{
			struct modr* leg4 = malloc(sizeof(struct modr));
			newModr(leg4, 0, 16, 64.0, 32.0, 2.0, 18.0, -4.0);
			struct vertex_tex cubes[24];
			createModelCube(leg4, &cubes[0], -2.0, 0.0, -2.0, 4.0, 6.0, 4.0, 2.0, 0);
			leg4->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leg4->vao, 1, 0);
			addModelChild(&mod_creepercharge, leg4);
		}
	}
	// mod_enderman
	{
		newModel(&mod_enderman, 64, 32);
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 32.0, 0.0, -14.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.0, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_enderman, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 0, 16, 64.0, 32.0, 0.0, -14.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, -0.5, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_enderman, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 32, 16, 64.0, 32.0, 0.0, -14.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 0.0, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_enderman, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 56, 0, 64.0, 32.0, -3.0, -12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -1.0, -2.0, -1.0, 2.0, 30.0, 2.0, 0.0, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_enderman, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 56, 0, 64.0, 32.0, 5.0, -12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -1.0, 2.0, 30.0, 2.0, 0.0, 1);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_enderman, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 56, 0, 64.0, 32.0, -2.0, -2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -1.0, 0.0, -1.0, 2.0, 30.0, 2.0, 0.0, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_enderman, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 56, 0, 64.0, 32.0, 2.0, -2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -1.0, 0.0, -1.0, 2.0, 30.0, 2.0, 0.0, 1);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_enderman, bipedleftleg);
		}
	}
	// mod_snowman
	{
		newModel(&mod_snowman, 64, 32);
		{
			struct modr* body = malloc(sizeof(struct modr));
			newModr(body, 0, 16, 64.0, 64.0, 0.0, 13.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(body, &cubes[0], -5.0, -10.0, -5.0, 10.0, 10.0, 10.0, -0.5, 0);
			body->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, body->vao, 1, 0);
			addModelChild(&mod_snowman, body);
		}
		{
			struct modr* bottombody = malloc(sizeof(struct modr));
			newModr(bottombody, 0, 36, 64.0, 64.0, 0.0, 24.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bottombody, &cubes[0], -6.0, -12.0, -6.0, 12.0, 12.0, 12.0, -0.5, 0);
			bottombody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bottombody->vao, 1, 0);
			addModelChild(&mod_snowman, bottombody);
		}
		{
			struct modr* head = malloc(sizeof(struct modr));
			newModr(head, 0, 0, 64.0, 64.0, 0.0, 4.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(head, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, -0.5, 0);
			head->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, head->vao, 1, 0);
			addModelChild(&mod_snowman, head);
		}
		{
			struct modr* righthand = malloc(sizeof(struct modr));
			newModr(righthand, 32, 0, 64.0, 64.0, 0.0, 6.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(righthand, &cubes[0], -1.0, 0.0, -1.0, 12.0, 2.0, 2.0, -0.5, 0);
			righthand->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, righthand->vao, 1, 0);
			addModelChild(&mod_snowman, righthand);
		}
		{
			struct modr* lefthand = malloc(sizeof(struct modr));
			newModr(lefthand, 32, 0, 64.0, 64.0, 0.0, 6.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(lefthand, &cubes[0], -1.0, 0.0, -1.0, 12.0, 2.0, 2.0, -0.5, 0);
			lefthand->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, lefthand->vao, 1, 0);
			addModelChild(&mod_snowman, lefthand);
		}
	}
	// mod_skeleton
	{
		newModel(&mod_skeleton, 64, 32);
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.0, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_skeleton, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.5, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_skeleton, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 16, 16, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 0.0, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_skeleton, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 40, 16, 64.0, 32.0, -5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -1.0, -2.0, -1.0, 2.0, 12.0, 2.0, 0.0, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_skeleton, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 40, 16, 64.0, 32.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -1.0, 2.0, 12.0, 2.0, 0.0, 1);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_skeleton, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 0, 16, 64.0, 32.0, -2.0, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -1.0, 0.0, -1.0, 2.0, 12.0, 2.0, 0.0, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_skeleton, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 0, 16, 64.0, 32.0, 2.0, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -1.0, 0.0, -1.0, 2.0, 12.0, 2.0, 0.0, 1);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_skeleton, bipedleftleg);
		}
	}
	// mod_skeletonleggings
	{
		newModel(&mod_skeletonleggings, 64, 32);
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.5, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_skeletonleggings, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 1.0, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_skeletonleggings, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 16, 16, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 0.5, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_skeletonleggings, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 40, 16, 64.0, 32.0, -5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -3.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.5, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_skeletonleggings, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 40, 16, 64.0, 32.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.5, 1);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_skeletonleggings, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 0, 16, 64.0, 32.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.5, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_skeletonleggings, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 0, 16, 64.0, 32.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.5, 1);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_skeletonleggings, bipedleftleg);
		}
	}
	// mod_skeletonarmor
	{
		newModel(&mod_skeletonarmor, 64, 32);
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 1.0, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_skeletonarmor, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 1.5, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_skeletonarmor, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 16, 16, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 1.0, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_skeletonarmor, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 40, 16, 64.0, 32.0, -5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -3.0, -2.0, -2.0, 4.0, 12.0, 4.0, 1.0, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_skeletonarmor, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 40, 16, 64.0, 32.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -2.0, 4.0, 12.0, 4.0, 1.0, 1);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_skeletonarmor, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 0, 16, 64.0, 32.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 1.0, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_skeletonarmor, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 0, 16, 64.0, 32.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 1.0, 1);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_skeletonarmor, bipedleftleg);
		}
	}
	// mod_witch
	{
		newModel(&mod_witch, 64, 32);
		{
			struct modr* villagerhead = malloc(sizeof(struct modr));
			newModr(villagerhead, 0, 0, 64.0, 128.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(villagerhead, &cubes[0], -4.0, -10.0, -4.0, 8.0, 10.0, 8.0, 0.0, 0);
			villagerhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, villagerhead->vao, 1, 0);
			addModelChild(&mod_witch, villagerhead);
		}
		{
			struct modr* villagerbody = malloc(sizeof(struct modr));
			newModr(villagerbody, 0, 38, 64.0, 128.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[48];
			createModelCube(villagerbody, &cubes[0], -4.0, 0.0, -3.0, 8.0, 12.0, 6.0, 0.0, 0);
			createModelCube(villagerbody, &cubes[24], -4.0, 0.0, -3.0, 8.0, 18.0, 6.0, 0.5, 0);
			villagerbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 48, villagerbody->vao, 1, 0);
			addModelChild(&mod_witch, villagerbody);
		}
		{
			struct modr* villagerarms = malloc(sizeof(struct modr));
			newModr(villagerarms, 40, 38, 64.0, 128.0, 0.0, 2.0, 0.0);
			struct vertex_tex cubes[72];
			createModelCube(villagerarms, &cubes[0], -8.0, -2.0, -2.0, 4.0, 8.0, 4.0, 0.0, 0);
			createModelCube(villagerarms, &cubes[24], 4.0, -2.0, -2.0, 4.0, 8.0, 4.0, 0.0, 0);
			createModelCube(villagerarms, &cubes[48], -4.0, 2.0, -2.0, 8.0, 4.0, 4.0, 0.0, 0);
			villagerarms->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 72, villagerarms->vao, 1, 0);
			addModelChild(&mod_witch, villagerarms);
		}
		{
			struct modr* rightvillagerleg = malloc(sizeof(struct modr));
			newModr(rightvillagerleg, 0, 22, 64.0, 128.0, -2.0, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(rightvillagerleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			rightvillagerleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, rightvillagerleg->vao, 1, 0);
			addModelChild(&mod_witch, rightvillagerleg);
		}
		{
			struct modr* leftvillagerleg = malloc(sizeof(struct modr));
			newModr(leftvillagerleg, 0, 22, 64.0, 128.0, 2.0, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(leftvillagerleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 1);
			leftvillagerleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leftvillagerleg->vao, 1, 0);
			addModelChild(&mod_witch, leftvillagerleg);
		}
		{
			struct modr* villagernose = malloc(sizeof(struct modr));
			newModr(villagernose, 24, 0, 64.0, 128.0, 0.0, -2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(villagernose, &cubes[0], -1.0, -1.0, -6.0, 2.0, 4.0, 2.0, 0.0, 0);
			villagernose->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, villagernose->vao, 1, 0);
			addModelChild(&mod_witch, villagernose);
		}
	}
	// mod_blaze
	{
		newModel(&mod_blaze, 64, 32);
	}
	// mod_zombie
	{
		newModel(&mod_zombie, 64, 64);
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.0, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_zombie, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.5, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_zombie, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 16, 16, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 0.0, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_zombie, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 40, 16, 64.0, 64.0, -5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -3.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_zombie, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 40, 16, 64.0, 64.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.0, 1);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_zombie, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 0, 16, 64.0, 64.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_zombie, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 0, 16, 64.0, 64.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 1);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_zombie, bipedleftleg);
		}
	}
	// mod_zombieleggings
	{
		newModel(&mod_zombieleggings, 64, 32);
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.5, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_zombieleggings, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 1.0, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_zombieleggings, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 16, 16, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 0.5, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_zombieleggings, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 40, 16, 64.0, 32.0, -5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -3.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.5, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_zombieleggings, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 40, 16, 64.0, 32.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.5, 1);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_zombieleggings, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 0, 16, 64.0, 32.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.5, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_zombieleggings, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 0, 16, 64.0, 32.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.5, 1);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_zombieleggings, bipedleftleg);
		}
	}
	// mod_zombiearmor
	{
		newModel(&mod_zombiearmor, 64, 32);
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 1.0, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_zombiearmor, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 1.5, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_zombiearmor, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 16, 16, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 1.0, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_zombiearmor, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 40, 16, 64.0, 32.0, -5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -3.0, -2.0, -2.0, 4.0, 12.0, 4.0, 1.0, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_zombiearmor, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 40, 16, 64.0, 32.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -2.0, 4.0, 12.0, 4.0, 1.0, 1);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_zombiearmor, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 0, 16, 64.0, 32.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 1.0, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_zombiearmor, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 0, 16, 64.0, 32.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 1.0, 1);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_zombiearmor, bipedleftleg);
		}
	}
	// mod_zombievillager
	{
		newModel(&mod_zombievillager, 64, 64);
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 24, 0, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[48];
			createModelCube(bipedhead, &cubes[0], -4.0, -10.0, -4.0, 8.0, 10.0, 8.0, 0.0, 0);
			createModelCube(bipedhead, &cubes[24], -1.0, -3.0, -6.0, 2.0, 4.0, 2.0, 0.0, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 48, bipedhead->vao, 1, 0);
			addModelChild(&mod_zombievillager, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.5, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_zombievillager, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 0, 38, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[48];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -3.0, 8.0, 12.0, 6.0, 0.0, 0);
			createModelCube(bipedbody, &cubes[24], -4.0, 0.0, -3.0, 8.0, 18.0, 6.0, 0.05, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 48, bipedbody->vao, 1, 0);
			addModelChild(&mod_zombievillager, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 44, 38, 64.0, 64.0, -5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -3.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_zombievillager, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 44, 38, 64.0, 64.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.0, 1);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_zombievillager, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 0, 22, 64.0, 64.0, -2.0, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_zombievillager, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 0, 22, 64.0, 64.0, 2.0, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 1);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_zombievillager, bipedleftleg);
		}
	}
	// mod_slime
	{
		newModel(&mod_slime, 64, 32);
	}
	// mod_slimegel
	{
		newModel(&mod_slimegel, 64, 32);
	}
	// mod_magmacube
	{
		newModel(&mod_magmacube, 64, 32);
	}
	// mod_ghast
	{
		newModel(&mod_ghast, 64, 32);
	}
	// mod_squid
	{
		newModel(&mod_squid, 64, 32);
	}
	// mod_villager
	{
		newModel(&mod_villager, 64, 32);
		{
			struct modr* villagerhead = malloc(sizeof(struct modr));
			newModr(villagerhead, 0, 0, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(villagerhead, &cubes[0], -4.0, -10.0, -4.0, 8.0, 10.0, 8.0, 0.0, 0);
			villagerhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, villagerhead->vao, 1, 0);
			addModelChild(&mod_villager, villagerhead);
		}
		{
			struct modr* villagerbody = malloc(sizeof(struct modr));
			newModr(villagerbody, 0, 38, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[48];
			createModelCube(villagerbody, &cubes[0], -4.0, 0.0, -3.0, 8.0, 12.0, 6.0, 0.0, 0);
			createModelCube(villagerbody, &cubes[24], -4.0, 0.0, -3.0, 8.0, 18.0, 6.0, 0.5, 0);
			villagerbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 48, villagerbody->vao, 1, 0);
			addModelChild(&mod_villager, villagerbody);
		}
		{
			struct modr* villagerarms = malloc(sizeof(struct modr));
			newModr(villagerarms, 40, 38, 64.0, 64.0, 0.0, 2.0, 0.0);
			struct vertex_tex cubes[72];
			createModelCube(villagerarms, &cubes[0], -8.0, -2.0, -2.0, 4.0, 8.0, 4.0, 0.0, 0);
			createModelCube(villagerarms, &cubes[24], 4.0, -2.0, -2.0, 4.0, 8.0, 4.0, 0.0, 0);
			createModelCube(villagerarms, &cubes[48], -4.0, 2.0, -2.0, 8.0, 4.0, 4.0, 0.0, 0);
			villagerarms->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 72, villagerarms->vao, 1, 0);
			addModelChild(&mod_villager, villagerarms);
		}
		{
			struct modr* rightvillagerleg = malloc(sizeof(struct modr));
			newModr(rightvillagerleg, 0, 22, 64.0, 64.0, -2.0, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(rightvillagerleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			rightvillagerleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, rightvillagerleg->vao, 1, 0);
			addModelChild(&mod_villager, rightvillagerleg);
		}
		{
			struct modr* leftvillagerleg = malloc(sizeof(struct modr));
			newModr(leftvillagerleg, 0, 22, 64.0, 64.0, 2.0, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(leftvillagerleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 1);
			leftvillagerleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, leftvillagerleg->vao, 1, 0);
			addModelChild(&mod_villager, leftvillagerleg);
		}
		{
			struct modr* villagernose = malloc(sizeof(struct modr));
			newModr(villagernose, 24, 0, 64.0, 64.0, 0.0, -2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(villagernose, &cubes[0], -1.0, -1.0, -6.0, 2.0, 4.0, 2.0, 0.0, 0);
			villagernose->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, villagernose->vao, 1, 0);
			addModelChild(&mod_villager, villagernose);
		}
	}
	// mod_irongolem
	{
		newModel(&mod_irongolem, 64, 32);
		{
			struct modr* irongolemhead = malloc(sizeof(struct modr));
			newModr(irongolemhead, 24, 0, 128.0, 128.0, 0.0, -7.0, -2.0);
			struct vertex_tex cubes[48];
			createModelCube(irongolemhead, &cubes[0], -4.0, -12.0, -5.5, 8.0, 10.0, 8.0, 0.0, 0);
			createModelCube(irongolemhead, &cubes[24], -1.0, -5.0, -7.5, 2.0, 4.0, 2.0, 0.0, 0);
			irongolemhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 48, irongolemhead->vao, 1, 0);
			addModelChild(&mod_irongolem, irongolemhead);
		}
		{
			struct modr* irongolembody = malloc(sizeof(struct modr));
			newModr(irongolembody, 0, 70, 128.0, 128.0, 0.0, -7.0, 0.0);
			struct vertex_tex cubes[48];
			createModelCube(irongolembody, &cubes[0], -9.0, -2.0, -6.0, 18.0, 12.0, 11.0, 0.0, 0);
			createModelCube(irongolembody, &cubes[24], -4.5, 10.0, -3.0, 9.0, 5.0, 6.0, 0.5, 0);
			irongolembody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 48, irongolembody->vao, 1, 0);
			addModelChild(&mod_irongolem, irongolembody);
		}
		{
			struct modr* irongolemrightarm = malloc(sizeof(struct modr));
			newModr(irongolemrightarm, 60, 21, 128.0, 128.0, 0.0, -7.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(irongolemrightarm, &cubes[0], -13.0, -2.5, -3.0, 4.0, 30.0, 6.0, 0.0, 0);
			irongolemrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, irongolemrightarm->vao, 1, 0);
			addModelChild(&mod_irongolem, irongolemrightarm);
		}
		{
			struct modr* irongolemleftarm = malloc(sizeof(struct modr));
			newModr(irongolemleftarm, 60, 58, 128.0, 128.0, 0.0, -7.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(irongolemleftarm, &cubes[0], 9.0, -2.5, -3.0, 4.0, 30.0, 6.0, 0.0, 0);
			irongolemleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, irongolemleftarm->vao, 1, 0);
			addModelChild(&mod_irongolem, irongolemleftarm);
		}
		{
			struct modr* irongolemleftleg = malloc(sizeof(struct modr));
			newModr(irongolemleftleg, 37, 0, 128.0, 128.0, -4.0, 11.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(irongolemleftleg, &cubes[0], -3.5, -3.0, -3.0, 6.0, 16.0, 5.0, 0.0, 0);
			irongolemleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, irongolemleftleg->vao, 1, 0);
			addModelChild(&mod_irongolem, irongolemleftleg);
		}
		{
			struct modr* irongolemrightleg = malloc(sizeof(struct modr));
			newModr(irongolemrightleg, 60, 0, 128.0, 128.0, 5.0, 11.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(irongolemrightleg, &cubes[0], -3.5, -3.0, -3.0, 6.0, 16.0, 5.0, 0.0, 1);
			irongolemrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, irongolemrightleg->vao, 1, 0);
			addModelChild(&mod_irongolem, irongolemrightleg);
		}
	}
	// mod_bat
	{
		newModel(&mod_bat, 64, 64);
	}
	// mod_guardian
	{
		newModel(&mod_guardian, 64, 64);
	}
	// mod_shulker
	{
		newModel(&mod_shulker, 64, 64);
		{
			struct modr* field_187066_a = malloc(sizeof(struct modr));
			newModr(field_187066_a, 0, 52, 64.0, 64.0, 0.0, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(field_187066_a, &cubes[0], -3.0, 0.0, -3.0, 6.0, 6.0, 6.0, 0.0, 0);
			field_187066_a->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, field_187066_a->vao, 1, 0);
			addModelChild(&mod_shulker, field_187066_a);
		}
	}
	// mod_dragon
	{
		newModel(&mod_dragon, 256, 256);
	}
	// mod_endercrystal
	{
		newModel(&mod_endercrystal, 64, 32);
	}
	// mod_endercrystalbaseless
	{
		newModel(&mod_endercrystalbaseless, 64, 32);
	}
	// mod_wither
	{
		newModel(&mod_wither, 64, 64);
	}
	// mod_witheraura
	{
		newModel(&mod_witheraura, 64, 64);
	}
	// mod_leashknot
	{
		newModel(&mod_leashknot, 32, 32);
		{
			struct modr* field_110723_a = malloc(sizeof(struct modr));
			newModr(field_110723_a, 0, 0, 32.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(field_110723_a, &cubes[0], -3.0, -6.0, -3.0, 6.0, 8.0, 6.0, 0.0, 0);
			field_110723_a->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, field_110723_a->vao, 1, 0);
			addModelChild(&mod_leashknot, field_110723_a);
		}
	}
	// mod_witherskull
	{
		newModel(&mod_witherskull, 64, 64);
		{
			struct modr* skeletonhead = malloc(sizeof(struct modr));
			newModr(skeletonhead, 0, 35, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(skeletonhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.0, 0);
			skeletonhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, skeletonhead->vao, 1, 0);
			addModelChild(&mod_witherskull, skeletonhead);
		}
	}
	// mod_shulkerbullet
	{
		newModel(&mod_shulkerbullet, 64, 32);
		{
			struct modr* field_187069_a = malloc(sizeof(struct modr));
			newModr(field_187069_a, 20, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[72];
			createModelCube(field_187069_a, &cubes[0], -4.0, -4.0, -1.0, 8.0, 8.0, 2.0, 0.0, 0);
			createModelCube(field_187069_a, &cubes[24], -1.0, -4.0, -4.0, 2.0, 8.0, 8.0, 0.0, 0);
			createModelCube(field_187069_a, &cubes[48], -4.0, -1.0, -4.0, 8.0, 2.0, 8.0, 0.0, 0);
			field_187069_a->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 72, field_187069_a->vao, 1, 0);
			addModelChild(&mod_shulkerbullet, field_187069_a);
		}
	}
	// mod_armorstand
	{
		newModel(&mod_armorstand, 64, 64);
		{
			struct modr* standrightside = malloc(sizeof(struct modr));
			newModr(standrightside, 16, 0, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(standrightside, &cubes[0], -3.0, 3.0, -1.0, 2.0, 7.0, 2.0, 0.0, 0);
			standrightside->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, standrightside->vao, 1, 0);
			addModelChild(&mod_armorstand, standrightside);
		}
		{
			struct modr* standleftside = malloc(sizeof(struct modr));
			newModr(standleftside, 48, 16, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(standleftside, &cubes[0], 1.0, 3.0, -1.0, 2.0, 7.0, 2.0, 0.0, 0);
			standleftside->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, standleftside->vao, 1, 0);
			addModelChild(&mod_armorstand, standleftside);
		}
		{
			struct modr* standwaist = malloc(sizeof(struct modr));
			newModr(standwaist, 0, 48, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(standwaist, &cubes[0], -4.0, 10.0, -1.0, 8.0, 2.0, 2.0, 0.0, 0);
			standwaist->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, standwaist->vao, 1, 0);
			addModelChild(&mod_armorstand, standwaist);
		}
		{
			struct modr* standbase = malloc(sizeof(struct modr));
			newModr(standbase, 0, 32, 64.0, 64.0, 0.0, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(standbase, &cubes[0], -6.0, 11.0, -6.0, 12.0, 1.0, 12.0, 0.0, 0);
			standbase->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, standbase->vao, 1, 0);
			addModelChild(&mod_armorstand, standbase);
		}
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -1.0, -7.0, -1.0, 2.0, 7.0, 2.0, 0.0, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_armorstand, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.5, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_armorstand, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 0, 26, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -6.0, 0.0, -1.5, 12.0, 3.0, 3.0, 0.0, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_armorstand, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 24, 0, 64.0, 64.0, -5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -2.0, -2.0, -1.0, 2.0, 12.0, 2.0, 0.0, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_armorstand, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 32, 16, 64.0, 64.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], 0.0, -2.0, -1.0, 2.0, 12.0, 2.0, 0.0, 1);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_armorstand, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 8, 0, 64.0, 64.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -1.0, 0.0, -1.0, 2.0, 11.0, 2.0, 0.0, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_armorstand, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 40, 16, 64.0, 64.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -1.0, 0.0, -1.0, 2.0, 11.0, 2.0, 0.0, 1);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_armorstand, bipedleftleg);
		}
	}
	// mod_armorstandleggings
	{
		newModel(&mod_armorstandleggings, 64, 32);
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.5, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_armorstandleggings, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 1.0, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_armorstandleggings, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 16, 16, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 0.5, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_armorstandleggings, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 40, 16, 64.0, 32.0, -5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -3.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.5, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_armorstandleggings, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 40, 16, 64.0, 32.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.5, 1);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_armorstandleggings, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 0, 16, 64.0, 32.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.5, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_armorstandleggings, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 0, 16, 64.0, 32.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.5, 1);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_armorstandleggings, bipedleftleg);
		}
	}
	// mod_armorstandarmor
	{
		newModel(&mod_armorstandarmor, 64, 32);
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 1.0, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_armorstandarmor, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 1.5, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_armorstandarmor, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 16, 16, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 1.0, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_armorstandarmor, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 40, 16, 64.0, 32.0, -5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -3.0, -2.0, -2.0, 4.0, 12.0, 4.0, 1.0, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_armorstandarmor, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 40, 16, 64.0, 32.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -2.0, 4.0, 12.0, 4.0, 1.0, 1);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_armorstandarmor, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 0, 16, 64.0, 32.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 1.0, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_armorstandarmor, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 0, 16, 64.0, 32.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 1.0, 1);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_armorstandarmor, bipedleftleg);
		}
	}
	// mod_minecarttnt
	{
		newModel(&mod_minecarttnt, 64, 32);
	}
	// mod_minecartmobspawner
	{
		newModel(&mod_minecartmobspawner, 64, 32);
	}
	// mod_minecart
	{
		newModel(&mod_minecart, 64, 32);
	}
	// mod_boat
	{
		newModel(&mod_boat, 64, 32);
		{
			struct modr* field_187058_c = malloc(sizeof(struct modr));
			newModr(field_187058_c, 0, 0, 128.0, 64.0, 0.0, -3.0, 1.0);
			struct vertex_tex cubes[24];
			createModelCube(field_187058_c, &cubes[0], -14.0, -9.0, -3.0, 28.0, 16.0, 3.0, 0.0, 0);
			field_187058_c->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, field_187058_c->vao, 1, 0);
			addModelChild(&mod_boat, field_187058_c);
		}
	}
	// mod_horse
	{
		newModel(&mod_horse, 128, 128);
	}
	// mod_player
	{
		newModel(&mod_player, 64, 64);
		{
			struct modr* bipedleftarmwear = malloc(sizeof(struct modr));
			newModr(bipedleftarmwear, 48, 48, 64.0, 64.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarmwear, &cubes[0], -1.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.25, 0);
			bipedleftarmwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarmwear->vao, 1, 0);
			addModelChild(&mod_player, bipedleftarmwear);
		}
		{
			struct modr* bipedrightarmwear = malloc(sizeof(struct modr));
			newModr(bipedrightarmwear, 40, 32, 64.0, 64.0, -5.0, 2.0, 10.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarmwear, &cubes[0], -3.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.25, 0);
			bipedrightarmwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarmwear->vao, 1, 0);
			addModelChild(&mod_player, bipedrightarmwear);
		}
		{
			struct modr* bipedleftlegwear = malloc(sizeof(struct modr));
			newModr(bipedleftlegwear, 0, 48, 64.0, 64.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftlegwear, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.25, 0);
			bipedleftlegwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftlegwear->vao, 1, 0);
			addModelChild(&mod_player, bipedleftlegwear);
		}
		{
			struct modr* bipedrightlegwear = malloc(sizeof(struct modr));
			newModr(bipedrightlegwear, 0, 32, 64.0, 64.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightlegwear, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.25, 0);
			bipedrightlegwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightlegwear->vao, 1, 0);
			addModelChild(&mod_player, bipedrightlegwear);
		}
		{
			struct modr* bipedbodywear = malloc(sizeof(struct modr));
			newModr(bipedbodywear, 16, 32, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbodywear, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 0.25, 0);
			bipedbodywear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbodywear->vao, 1, 0);
			addModelChild(&mod_player, bipedbodywear);
		}
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.0, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_player, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.5, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_player, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 16, 16, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 0.0, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_player, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 40, 16, 64.0, 64.0, -5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -3.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_player, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 32, 48, 64.0, 64.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_player, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 0, 16, 64.0, 64.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_player, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 16, 48, 64.0, 64.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_player, bipedleftleg);
		}
	}
	// mod_playerleggings
	{
		newModel(&mod_playerleggings, 64, 32);
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.5, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_playerleggings, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 1.0, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_playerleggings, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 16, 16, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 0.5, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_playerleggings, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 40, 16, 64.0, 32.0, -5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -3.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.5, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_playerleggings, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 40, 16, 64.0, 32.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.5, 1);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_playerleggings, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 0, 16, 64.0, 32.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.5, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_playerleggings, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 0, 16, 64.0, 32.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.5, 1);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_playerleggings, bipedleftleg);
		}
	}
	// mod_playerarmor
	{
		newModel(&mod_playerarmor, 64, 32);
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 1.0, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_playerarmor, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 1.5, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_playerarmor, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 16, 16, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 1.0, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_playerarmor, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 40, 16, 64.0, 32.0, -5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -3.0, -2.0, -2.0, 4.0, 12.0, 4.0, 1.0, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_playerarmor, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 40, 16, 64.0, 32.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -2.0, 4.0, 12.0, 4.0, 1.0, 1);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_playerarmor, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 0, 16, 64.0, 32.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 1.0, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_playerarmor, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 0, 16, 64.0, 32.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 1.0, 1);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_playerarmor, bipedleftleg);
		}
	}
	// mod_playerelytra
	{
		newModel(&mod_playerelytra, 64, 32);
	}
	// mod_splayer
	{
		newModel(&mod_splayer, 64, 64);
		{
			struct modr* bipedleftarmwear = malloc(sizeof(struct modr));
			newModr(bipedleftarmwear, 48, 48, 64.0, 64.0, 5.0, 2.5, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarmwear, &cubes[0], -1.0, -2.0, -2.0, 3.0, 12.0, 4.0, 0.25, 0);
			bipedleftarmwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarmwear->vao, 1, 0);
			addModelChild(&mod_splayer, bipedleftarmwear);
		}
		{
			struct modr* bipedrightarmwear = malloc(sizeof(struct modr));
			newModr(bipedrightarmwear, 40, 32, 64.0, 64.0, -5.0, 2.5, 10.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarmwear, &cubes[0], -2.0, -2.0, -2.0, 3.0, 12.0, 4.0, 0.25, 0);
			bipedrightarmwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarmwear->vao, 1, 0);
			addModelChild(&mod_splayer, bipedrightarmwear);
		}
		{
			struct modr* bipedleftlegwear = malloc(sizeof(struct modr));
			newModr(bipedleftlegwear, 0, 48, 64.0, 64.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftlegwear, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.25, 0);
			bipedleftlegwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftlegwear->vao, 1, 0);
			addModelChild(&mod_splayer, bipedleftlegwear);
		}
		{
			struct modr* bipedrightlegwear = malloc(sizeof(struct modr));
			newModr(bipedrightlegwear, 0, 32, 64.0, 64.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightlegwear, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.25, 0);
			bipedrightlegwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightlegwear->vao, 1, 0);
			addModelChild(&mod_splayer, bipedrightlegwear);
		}
		{
			struct modr* bipedbodywear = malloc(sizeof(struct modr));
			newModr(bipedbodywear, 16, 32, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbodywear, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 0.25, 0);
			bipedbodywear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbodywear->vao, 1, 0);
			addModelChild(&mod_splayer, bipedbodywear);
		}
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.0, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_splayer, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.5, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_splayer, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 16, 16, 64.0, 64.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 0.0, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_splayer, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 40, 16, 64.0, 64.0, -5.0, 2.5, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -2.0, -2.0, -2.0, 3.0, 12.0, 4.0, 0.0, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_splayer, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 32, 48, 64.0, 64.0, 5.0, 2.5, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -2.0, 3.0, 12.0, 4.0, 0.0, 0);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_splayer, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 0, 16, 64.0, 64.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_splayer, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 16, 48, 64.0, 64.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.0, 0);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_splayer, bipedleftleg);
		}
	}
	// mod_splayerleggings
	{
		newModel(&mod_splayerleggings, 64, 32);
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 0.5, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_splayerleggings, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 1.0, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_splayerleggings, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 16, 16, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 0.5, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_splayerleggings, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 40, 16, 64.0, 32.0, -5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -3.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.5, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_splayerleggings, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 40, 16, 64.0, 32.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -2.0, 4.0, 12.0, 4.0, 0.5, 1);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_splayerleggings, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 0, 16, 64.0, 32.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.5, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_splayerleggings, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 0, 16, 64.0, 32.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 0.5, 1);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_splayerleggings, bipedleftleg);
		}
	}
	// mod_splayerarmor
	{
		newModel(&mod_splayerarmor, 64, 32);
		{
			struct modr* bipedhead = malloc(sizeof(struct modr));
			newModr(bipedhead, 0, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedhead, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 1.0, 0);
			bipedhead->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedhead->vao, 1, 0);
			addModelChild(&mod_splayerarmor, bipedhead);
		}
		{
			struct modr* bipedheadwear = malloc(sizeof(struct modr));
			newModr(bipedheadwear, 32, 0, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedheadwear, &cubes[0], -4.0, -8.0, -4.0, 8.0, 8.0, 8.0, 1.5, 0);
			bipedheadwear->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedheadwear->vao, 1, 0);
			addModelChild(&mod_splayerarmor, bipedheadwear);
		}
		{
			struct modr* bipedbody = malloc(sizeof(struct modr));
			newModr(bipedbody, 16, 16, 64.0, 32.0, 0.0, 0.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedbody, &cubes[0], -4.0, 0.0, -2.0, 8.0, 12.0, 4.0, 1.0, 0);
			bipedbody->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedbody->vao, 1, 0);
			addModelChild(&mod_splayerarmor, bipedbody);
		}
		{
			struct modr* bipedrightarm = malloc(sizeof(struct modr));
			newModr(bipedrightarm, 40, 16, 64.0, 32.0, -5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightarm, &cubes[0], -3.0, -2.0, -2.0, 4.0, 12.0, 4.0, 1.0, 0);
			bipedrightarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightarm->vao, 1, 0);
			addModelChild(&mod_splayerarmor, bipedrightarm);
		}
		{
			struct modr* bipedleftarm = malloc(sizeof(struct modr));
			newModr(bipedleftarm, 40, 16, 64.0, 32.0, 5.0, 2.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftarm, &cubes[0], -1.0, -2.0, -2.0, 4.0, 12.0, 4.0, 1.0, 1);
			bipedleftarm->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftarm->vao, 1, 0);
			addModelChild(&mod_splayerarmor, bipedleftarm);
		}
		{
			struct modr* bipedrightleg = malloc(sizeof(struct modr));
			newModr(bipedrightleg, 0, 16, 64.0, 32.0, -1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedrightleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 1.0, 0);
			bipedrightleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedrightleg->vao, 1, 0);
			addModelChild(&mod_splayerarmor, bipedrightleg);
		}
		{
			struct modr* bipedleftleg = malloc(sizeof(struct modr));
			newModr(bipedleftleg, 0, 16, 64.0, 32.0, 1.9, 12.0, 0.0);
			struct vertex_tex cubes[24];
			createModelCube(bipedleftleg, &cubes[0], -2.0, 0.0, -2.0, 4.0, 12.0, 4.0, 1.0, 1);
			bipedleftleg->vao = malloc(sizeof(struct vao));
			createVAO(cubes, 24, bipedleftleg->vao, 1, 0);
			addModelChild(&mod_splayerarmor, bipedleftleg);
		}
	}
	// mod_splayerelytra
	{
		newModel(&mod_splayerelytra, 64, 32);
	}

}

void newModel(struct model* model, int width, int height) {
	model->txh = height;
	model->txw = width;
	model->children = NULL;
	model->child_count = 0;
}

void newModr(struct modr* modr, int txx, int txy, int txw, int txh, float rpX, float rpY, float rpZ) {
	modr->child_count = 0;
	modr->children = NULL;
	modr->txx = txx;
	modr->txy = txy;
	modr->txh = txh;
	modr->txw = txw;
	modr->vao = NULL;
	modr->rotX = 0.;
	modr->rotY = 0.;
	modr->rotZ = 0.;
	modr->defRotX = 0.;
	modr->defRotY = 0.;
	modr->defRotZ = 0.;
	modr->defrpX = rpX;
	modr->defrpY = rpY;
	modr->defrpZ = rpZ;
	modr->rpX = rpX;
	modr->rpY = rpY;
	modr->rpZ = rpZ;
}

void setModrAngles(struct modr* modr, float rotX, float rotY, float rotZ) {
	modr->rotX = rotX;
	modr->rotY = rotY;
	modr->rotZ = rotZ;
}

void setModrDefAngles(struct modr* modr, float rotX, float rotY, float rotZ) {
	modr->defRotX = rotX;
	modr->defRotY = rotY;
	modr->defRotZ = rotZ;
}

void setModrAnglePoint(struct modr* modr, float rpX, float rpY, float rpZ) {
	modr->rpX = rpX;
	modr->rpY = rpY;
	modr->rpZ = rpZ;
}

void setModrDefAnglePoint(struct modr* modr, float rpX, float rpY, float rpZ) {
	modr->defrpX = rpX;
	modr->defrpY = rpY;
	modr->defrpZ = rpZ;
}

void resetModr(struct modr* modr) {
	modr->rpX = modr->defrpX;
	modr->rpY = modr->defrpY;
	modr->rpZ = modr->defrpZ;
	modr->rotX = modr->defRotX;
	modr->rotY = modr->defRotY;
	modr->rotZ = modr->defRotZ;
	for (size_t i = 0; i < modr->child_count; i++) {
		resetModr(modr->children[i]);
	}
}

void resetModel(struct model* model) {
	for (size_t i = 0; i < model->child_count; i++) {
		resetModr(model->children[i]);
	}
}

void addModrChild(struct modr* modr, struct modr* child) {
	if (modr->children == NULL) {
		modr->children = malloc(sizeof(struct modr*));
		modr->child_count = 0;
	} else {
		modr->children = realloc(modr->children, sizeof(struct modr*) * (1 + modr->child_count));
	}
	modr->children[modr->child_count++] = child;
}

void addModelChild(struct model* model, struct modr* child) {
	if (model->children == NULL) {
		model->children = malloc(sizeof(struct modr*));
		model->child_count = 0;
	} else {
		model->children = realloc(model->children, sizeof(struct modr*) * (1 + model->child_count));
	}
	model->children[model->child_count++] = child;
}

void xferVerticiesQuad(struct vertex_tex* to, struct vertex_tex** from, int x1, int y1, int x2, int y2, float txw, float txh, int mirror) {
	struct vertex_tex* mir[4];
	struct vertex_tex** rt = mir;
	if (mirror) {
		mir[0] = &to[3];
		mir[1] = &to[2];
		mir[2] = &to[1];
		mir[3] = &to[0];
	} else {
		mir[0] = &to[0];
		mir[1] = &to[1];
		mir[2] = &to[2];
		mir[3] = &to[3];
	}
	for (int i = 0; i < 4; i++) {
		(rt)[i]->x = from[i]->x * .0625;
		(rt)[i]->y = from[i]->y * .0625;
		(rt)[i]->z = from[i]->z * .0625;
	}
	(rt)[0]->texX = (float) x2 / txw;
	(rt)[0]->texY = (float) y1 / txh;
	(rt)[1]->texX = (float) x1 / txw;
	(rt)[1]->texY = (float) y1 / txh;
	(rt)[2]->texX = (float) x1 / txw;
	(rt)[2]->texY = (float) y2 / txh;
	(rt)[3]->texX = (float) x2 / txw;
	(rt)[3]->texY = (float) y2 / txh;
}

void createModelCube(struct modr* modr, struct vertex_tex* vexs, float x, float y, float z, int width, int height, int depth, float scale, int mirror) {
	float x2 = x + (float) width;
	float y2 = y + (float) height;
	float z2 = z + (float) depth;
	x -= scale;
	y -= scale;
	z -= scale;
	x2 += scale;
	y2 += scale;
	z2 += scale;
	if (mirror) {
		float t = x2;
		x2 = x;
		x = t;
	}
	struct vertex_tex tt[8];
	virtVertex3f(&tt[0], x, y, z);
	virtTexCoord2f(&tt[0], 0., 0.);
	virtVertex3f(&tt[1], x2, y, z);
	virtTexCoord2f(&tt[1], 0., 8.);
	virtVertex3f(&tt[2], x2, y2, z);
	virtTexCoord2f(&tt[2], 8., 8.);
	virtVertex3f(&tt[3], x, y2, z);
	virtTexCoord2f(&tt[3], 8., 0.);
	virtVertex3f(&tt[4], x, y, z2);
	virtTexCoord2f(&tt[4], 0., 0.);
	virtVertex3f(&tt[5], x2, y, z2);
	virtTexCoord2f(&tt[5], 0., 8.);
	virtVertex3f(&tt[6], x2, y2, z2);
	virtTexCoord2f(&tt[6], 8., 8.);
	virtVertex3f(&tt[7], x, y2, z2);
	virtTexCoord2f(&tt[7], 8., 0.);
	//
	struct vertex_tex* tv[4];
	tv[0] = &tt[5];
	tv[1] = &tt[1];
	tv[2] = &tt[2];
	tv[3] = &tt[6];
	xferVerticiesQuad(&(vexs[0]), tv, modr->txx + depth + width, modr->txy + depth, modr->txx + depth + width + depth, modr->txy + depth + height, modr->txw, modr->txh, mirror);
	tv[0] = &tt[0];
	tv[1] = &tt[4];
	tv[2] = &tt[7];
	tv[3] = &tt[3];
	xferVerticiesQuad(&(vexs[4]), tv, modr->txx, modr->txy + depth, modr->txx + depth, modr->txy + depth + height, modr->txw, modr->txh, mirror);
	tv[0] = &tt[5];
	tv[1] = &tt[4];
	tv[2] = &tt[0];
	tv[3] = &tt[1];
	xferVerticiesQuad(&(vexs[8]), tv, modr->txx + depth, modr->txy, modr->txx + depth + width, modr->txy + depth, modr->txw, modr->txh, mirror);
	tv[0] = &tt[2];
	tv[1] = &tt[3];
	tv[2] = &tt[7];
	tv[3] = &tt[6];
	xferVerticiesQuad(&(vexs[12]), tv, modr->txx + depth + width, modr->txy + depth, modr->txx + depth + width + width, modr->txy, modr->txw, modr->txh, mirror);
	tv[0] = &tt[1];
	tv[1] = &tt[0];
	tv[2] = &tt[3];
	tv[3] = &tt[2];
	xferVerticiesQuad(&(vexs[16]), tv, modr->txx + depth, modr->txy + depth, modr->txx + depth + width, modr->txy + depth + height, modr->txw, modr->txh, mirror);
	tv[0] = &tt[4];
	tv[1] = &tt[5];
	tv[2] = &tt[6];
	tv[3] = &tt[7];
	xferVerticiesQuad(&(vexs[20]), tv, modr->txx + depth + width + depth, modr->txy + depth, modr->txx + depth + width + depth + width, modr->txy + depth + height, modr->txw, modr->txh, mirror);
}

void drawModr(struct modr* modr) {
	glPushMatrix();
	if (modr->rpX != 0. || modr->rpY != 0. || modr->rpZ != 0.) glTranslatef(modr->rpX * .0625, modr->rpY * .0625, modr->rpZ * .0625);
	if (modr->rotZ != 0.) glRotatef(modr->rotZ * (180. / PI), 0., 0., 1.);
	if (modr->rotY != 0.) glRotatef(modr->rotY * (180. / PI), 0., 1., 0.);
	if (modr->rotX != 0.) glRotatef(modr->rotX * (180. / PI), 1., 0., 0.);
	drawQuads(modr->vao);
	for (int i = 0; i < modr->child_count; i++) {
		drawModr(modr->children[i]);
	}
	glPopMatrix();
}

void drawModel(struct model* model) {
	glPushMatrix();
	glScalef(-1., -1., 1.);
	glTranslatef(0., -1.5078125, 0.);
	for (int i = 0; i < model->child_count; i++) {
		drawModr(model->children[i]);
	}
	glPopMatrix();
}

int loadTexturePNG(char* path, int id, int s) {
	FILE* fd = fopen(path, "rb");
	if (!fd) return -1;
	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png) {
		fclose(fd);
		return -1;
	}
	png_infop info = png_create_info_struct(png);
	if (!info) {
		fclose(fd);
		return -1;
	}
	png_init_io(png, fd);
	png_read_info(png, info);
	int width = png_get_image_width(png, info);
	int height = png_get_image_height(png, info);
	png_byte color_type = png_get_color_type(png, info);
	png_byte bit_depth = png_get_bit_depth(png, info);
	if (bit_depth == 16) png_set_strip_16(png);
	if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png);
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png);
	if (png_get_valid(png, info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png);
	if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE) png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(png);
	png_read_update_info(png, info);
	void* pngd = malloc(height * png_get_rowbytes(png, info));
	png_bytep* row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
	for (int y = 0; y < height; y++) {
		row_pointers[y] = (png_byte*) (pngd + (png_get_rowbytes(png, info) * y));
	}
	png_read_image(png, row_pointers);
	free(row_pointers);
	loadTextureData(id, width, height, pngd, s);
	free(pngd);
	fclose(fd);
	return 0;
}

int loadTexturesPNG(char* path, int wrap, int* w, int* h, int id, int s, char** map, int maps, int* smap) {
	void* tpngd = NULL;
	int rw = 0;
	int rh = 0;
	int mo = 0;
	for (int mi = 0; mi < maps;) {
		char* me = map[mi];
		char cx[strlen(path) + strlen(me) + 1];
		memcpy(cx, path, strlen(path));
		memcpy(cx + strlen(path), me, strlen(me) + 1);
		FILE* fd = fopen(cx, "rb");
		if (!fd) return -1;
		png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png) {
			fclose(fd);
			return -1;
		}
		png_infop info = png_create_info_struct(png);
		if (!info) {
			fclose(fd);
			return -1;
		}
		png_init_io(png, fd);
		png_read_info(png, info);
		int width = png_get_image_width(png, info);
		if (rw == 0) rw = width + (2 * TEXTURE_BUFFER);
		int height = png_get_image_height(png, info);
		if (rh == 0) rh = height + (2 * TEXTURE_BUFFER);
		if (tpngd == NULL) {
			tpngd = malloc((rh * 4 * rw) * maps);
		}
		png_byte color_type = png_get_color_type(png, info);
		png_byte bit_depth = png_get_bit_depth(png, info);
		if (bit_depth == 16) png_set_strip_16(png);
		if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png);
		if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png);
		if (png_get_valid(png, info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png);
		if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE) png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
		if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(png);
		png_read_update_info(png, info);
		smap[mi] = mo;
		png_byte** row_pointers = (png_byte**) malloc(sizeof(png_byte*) * height);
		int rx = mo % wrap;
		int ry = mo / wrap;
		int prx = rx;
		int pry = ry;
		mo++;
		int bry = 0;
		int ph = height;
		for (int y = TEXTURE_BUFFER; y < height + TEXTURE_BUFFER; y++) {
			if (y >= rh - TEXTURE_BUFFER) {
				height -= rh - (2 * TEXTURE_BUFFER);
				y = TEXTURE_BUFFER;
				rx++;
				if (rx >= wrap) {
					rx = 0;
					ry++;
				}
				mo++;
				//printf("%i vs %i\n", (rh * 4 * rw) * (maps + (mo - (mi - 1))), (rh * 4 * rw) * maps + (mo - (mi - 1)));
				*w = wrap * rw;
				*h = (((maps + mo - mi + wrap) / wrap) + 1) * rh;
				//printf("%i\n", *h * *w * 4);
				tpngd = realloc(tpngd, *h * *w * 4);
			}
			//printf("ri = %i size = %i len = %i\n", (ry * rw * 4 * rh * wrap) + (y * 4 * rw * wrap) + (rx * rw * 4), (rh * 4 * rw) * (maps + (mo - (mi - 1))), png_get_rowbytes(png, info));
			row_pointers[bry] = (png_byte*) ((ry * rw * 4 * rh * wrap) + (y * 4 * rw * wrap) + (rx * rw * 4)) + (4 * TEXTURE_BUFFER);
			bry++;
		}
		height = ph;
		for (int y = 0; y < bry; y++) {
			row_pointers[y] = (uint64_t) row_pointers[y] + (uint64_t) tpngd;
		}
		png_read_image(png, row_pointers);
		rx = prx;
		ry = pry;
		for (int y = 0; y < height + (2 * TEXTURE_BUFFER); y++) {
			if (y >= rh) {
				height -= rh;
				y = 0;
				rx++;
				if (rx >= wrap) {
					rx = 0;
					ry++;
				}
			}
			unsigned char* row = tpngd + ((ry * rw * 4 * rh * wrap) + (y * 4 * rw * wrap) + (rx * rw * 4));
			if (y < TEXTURE_BUFFER) {
				unsigned char* nrow = tpngd + ((ry * rw * 4 * rh * wrap) + (TEXTURE_BUFFER * 4 * rw * wrap) + (rx * rw * 4));
				memcpy(row + (4 * TEXTURE_BUFFER), nrow + (4 * TEXTURE_BUFFER), (rw - (2 * TEXTURE_BUFFER)) * 4);
				for (int i = 0; i < TEXTURE_BUFFER; i++) {
					memcpy(row + (i * 4), row + (4 * TEXTURE_BUFFER), 4);
					memcpy(row + (rw - 1 - i) * 4, row + (rw - 1 - TEXTURE_BUFFER) * 4, 4);
				}
			} else if (y >= rh - TEXTURE_BUFFER) {
				unsigned char* prow = tpngd + ((ry * rw * 4 * rh * wrap) + ((rh - 1 - TEXTURE_BUFFER) * 4 * rw * wrap) + (rx * rw * 4));
				memcpy(row + (4 * TEXTURE_BUFFER), prow + (4 * TEXTURE_BUFFER), (rw - (2 * TEXTURE_BUFFER)) * 4);
				for (int i = 0; i < TEXTURE_BUFFER; i++) {
					memcpy(row + (i * 4), row + (4 * TEXTURE_BUFFER), 4);
					memcpy(row + (rw - 1 - i) * 4, row + (rw - 1 - TEXTURE_BUFFER) * 4, 4);
				}
			} else {
				for (int i = 0; i < TEXTURE_BUFFER; i++) {
					memcpy(row + (i * 4), row + (4 * TEXTURE_BUFFER), 4);
					memcpy(row + (rw - 1 - i) * 4, row + (rw - 1 - TEXTURE_BUFFER) * 4, 4);
				}
			}
		}
		if (streq(me, "grass_top.png") || streq(me, "fern.png") || streq(me, "tallgrass.png") || startsWith(me, "double_plant_grass") || startsWith(me, "double_plant_fern") || startsWith(me, "leaves_")) { // TODO: implement dynamic textures better than this
			for (int y = 0; y < bry; y++) {
				uint32_t* pix = row_pointers[y];
				for (int x = 0; x < rw; x++) {
					//printf("%08X", pix[x]);
					int cc = (pix[x] & 0xFF);
					int r = 71 * ((float) cc / 255.);
					int g = 205 * ((float) cc / 255.);
					int b = 51 * ((float) cc / 255.);
					if (r > 255 || g > 255 || b > 255) {
						int total = r + g + b;
						int h = (r >= g && r >= b) ? r : ((g >= b) ? g : b);
						if (total < 765) {
							float m = (float) (765 - total) / (float) (3 * h - total);
							int g = 255 - m * (float) h;
							r = g + m * r;
							g = g + m * g;
							b = g + m * b;
						} else {
							r = 255;
							g = 255;
							b = 255;
						}
					}
					if (r < 0) r = 0;
					if (g < 0) g = 0;
					if (b < 0) b = 0;
					pix[x] = r | (g << 8) | (b << 16) | (pix[x] & 0xFF000000);
				}
				//printf("\n");
			}
		}
		free(row_pointers);
		png_destroy_read_struct(&png, &info, (png_infopp) 0);
		fclose(fd);
		mi++;
	}
	*w = wrap * rw;
	*h = ((mo / wrap) + 1) * rh;
	tpngd = realloc(tpngd, *h * *w * 4);
	/*FILE *fp = NULL;
	 png_structp png_ptr = NULL;
	 png_infop info_ptr = NULL;
	 png_bytep row = NULL;
	 fp = fopen("/dsk/test.png", "w+");
	 if (fp == NULL) {
	 free(tpngd);
	 return -1;
	 }
	 png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	 if (png_ptr == NULL) {
	 printf("e2\n");
	 }
	 info_ptr = png_create_info_struct(png_ptr);
	 if (info_ptr == NULL) {
	 printf("e3\n");
	 }
	 png_init_io(png_ptr, fp);
	 png_set_IHDR(png_ptr, info_ptr, *w, *h, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	 png_write_info(png_ptr, info_ptr);
	 for (int i = 0; i < *h; i++) {
	 row = tpngd + (*w * 4 * i);
	 png_write_row(png_ptr, row);
	 }
	 png_write_end(png_ptr, NULL);
	 fclose(fp);
	 png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	 png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
	 printf("wrote /dsk/test.png\n");*/
	loadTextureData(id, *w, *h, tpngd, s);
	free(tpngd);
	return 0;
}

void loadTextureData(int id, size_t width, size_t height, void* data, int s) {
	glBindTexture(GL_TEXTURE_2D, id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
//glGenerateMipmap (GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, s ? GL_NEAREST : GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
#ifdef GL_TEXTURE_MAX_ANISOTROPY_EXT
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0);
#endif
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}
