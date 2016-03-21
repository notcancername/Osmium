/*
 * entity.c
 *
 *  Created on: Feb 22, 2016
 *      Author: root
 */

#include "entity.h"
#include <stdint.h>
#include <stdlib.h>
#include <GL/gl.h>
#include "models.h"
#include "globals.h"

int entNetworkConvert(int type, int id) {
	if (type == 0) {
		if (id == 1) return ENT_BOAT;
		else if (id == 2) return ENT_ITEMSTACK;
		else if (id == 3) return ENT_AREAEFFECT;
		else if (id == 10) return ENT_MINECART;
		else if (id == 50) return ENT_TNT;
		else if (id == 51) return ENT_ENDERCRYSTAL;
		else if (id == 60) return ENT_ARROW;
		else if (id == 61) return ENT_SNOWBALL;
		else if (id == 62) return ENT_EGG;
		else if (id == 63) return ENT_FIREBALL;
		else if (id == 64) return ENT_FIRECHARGE;
		else if (id == 65) return ENT_ENDERPEARL;
		else if (id == 66) return ENT_WITHERSKULL;
		else if (id == 67) return ENT_SHULKERBULLET;
		else if (id == 70) return ENT_FALLINGBLOCK;
		else if (id == 71) return ENT_ITEMFRAME;
		else if (id == 72) return ENT_EYEENDER;
		else if (id == 73) return ENT_THROWNPOTION;
		else if (id == 74) return ENT_FALLINGEGG;
		else if (id == 75) return ENT_EXPBOTTLE;
		else if (id == 76) return ENT_FIREWORK;
		else if (id == 77) return ENT_LEASHKNOT;
		else if (id == 78) return ENT_ARMORSTAND;
		else if (id == 90) return ENT_FISHINGFLOAT;
		else if (id == 91) return ENT_SPECTRALARROW;
		else if (id == 92) return ENT_TIPPEDARROW;
		else if (id == 93) return ENT_DRAGONFIREBALL;
	} else if (type == 1) {
		if (id == 50) return ENT_CREEPER;
		else if (id == 51) return ENT_SKELETON;
		else if (id == 52) return ENT_SPIDER;
		else if (id == 53) return ENT_GIANT;
		else if (id == 54) return ENT_ZOMBIE;
		else if (id == 55) return ENT_SLIME;
		else if (id == 56) return ENT_GHAST;
		else if (id == 57) return ENT_ZPIGMAN;
		else if (id == 58) return ENT_ENDERMAN;
		else if (id == 59) return ENT_CAVESPIDER;
		else if (id == 60) return ENT_SILVERFISH;
		else if (id == 61) return ENT_BLAZE;
		else if (id == 62) return ENT_MAGMACUBE;
		else if (id == 63) return ENT_ENDERDRAGON;
		else if (id == 64) return ENT_WITHER;
		else if (id == 65) return ENT_BAT;
		else if (id == 66) return ENT_WITCH;
		else if (id == 67) return ENT_ENDERMITE;
		else if (id == 68) return ENT_GUARDIAN;
		else if (id == 69) return ENT_SHULKER;
		else if (id == 90) return ENT_PIG;
		else if (id == 91) return ENT_SHEEP;
		else if (id == 92) return ENT_COW;
		else if (id == 93) return ENT_CHICKEN;
		else if (id == 94) return ENT_SQUID;
		else if (id == 95) return ENT_WOLF;
		else if (id == 96) return ENT_MOOSHROOM;
		else if (id == 97) return ENT_SNOWMAN;
		else if (id == 98) return ENT_OCELOT;
		else if (id == 99) return ENT_IRONGOLEM;
		else if (id == 100) return ENT_HORSE;
		else if (id == 101) return ENT_RABBIT;
		else if (id == 120) return ENT_VILLAGER;
	}
	return -1;
}

struct entity* newEntity(int32_t id, float x, float y, float z, uint8_t type, float yaw, float pitch) {
	struct entity* e = malloc(sizeof(struct entity));
	e->id = id;
	e->x = x;
	e->y = y;
	e->z = z;
	e->lx = x;
	e->ly = y;
	e->lz = z;
	e->type = type;
	e->yaw = yaw;
	e->lyaw = yaw;
	e->pitch = pitch;
	e->lpitch = pitch;
	e->headpitch = 0.;
	e->lheadpitch = 0.;
	e->onGround = 1;
	e->motX = 0.;
	e->motY = 0.;
	e->motZ = 0.;
	e->objectData = 0;
	e->markedKill = 0;
	return e;
}

void drawEntity(float partialTick, struct entity* ent) {
	glPushMatrix();
	float ppitch = ent->pitch * (1. - partialTick) + ent->lpitch * partialTick;
	float pyaw = ent->yaw * (1. - partialTick) + ent->lyaw * partialTick;
	double px = ent->x * (1. - partialTick) + ent->lx * partialTick;
	double py = ent->y * (1. - partialTick) + ent->ly * partialTick;
	double pz = ent->z * (1. - partialTick) + ent->lz * partialTick;
	glTranslatef(px, py, pz);
	glRotatef(-pyaw + 180., 0., 1., 0.);
	//begin debug draw
	if (ent->type == ENT_MPPLAYER) {
		mod_biped.children[0]->rotX = ppitch / (180. / PI);
		drawModel (&mod_biped);
	} else {
		struct boundingbox* bb = getEntityCollision(ent);
		if (bb->minX != bb->maxX && bb->minY != bb->maxY && bb->minZ != bb->maxZ && bb->ovao != NULL) {
			glDisable (GL_TEXTURE_2D);
			glColor4f(1., 0., 0., 1.);
			drawQuads(bb->ovao);
			glColor4f(1., 1., 1., 1.);
			glEnable(GL_TEXTURE_2D);
		}
	}
	//end debug draw
	glPopMatrix();
}

struct boundingbox no_bb;
struct boundingbox bb_player;
struct boundingbox bb_skeleton;

void load_entities() {
	no_bb.minX = 0.;
	no_bb.minY = 0.;
	no_bb.minZ = 0.;
	no_bb.maxX = 0.;
	no_bb.maxY = 0.;
	no_bb.maxZ = 0.;
	bb_player.minX = -.3;
	bb_player.minY = 0.;
	bb_player.minZ = -.3;
	bb_player.maxX = .3;
	bb_player.maxY = 1.8;
	bb_player.maxZ = .3;
	createBBVao(&bb_player);
	bb_skeleton.minX = -.3;
	bb_skeleton.minY = 0.;
	bb_skeleton.minZ = -.3;
	bb_skeleton.maxX = .3;
	bb_skeleton.maxY = 1.95;
	bb_skeleton.maxZ = .3;
	createBBVao(&bb_skeleton);
}

struct boundingbox* getEntityCollision(struct entity* ent) {
	if (ent->type == ENT_OURPLAYER || ent->type == ENT_MPPLAYER || ent->type == ENT_CREEPER || ent->type == ENT_ZOMBIE || ent->type == ENT_ZPIGMAN || ent->type == ENT_BLAZE || ent->type == ENT_WITCH || ent->type == ENT_VILLAGER) return &bb_player;
	else if (ent->type == ENT_SKELETON) return &bb_skeleton;
	return &no_bb;
}

void freeEntity(struct entity* entity) {
	free(entity);
}
