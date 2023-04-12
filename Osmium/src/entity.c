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
#include "ingame.h"
#include <math.h>
#include "xstring.h"

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
	e->swingProgress = 0.;
	e->prevSwingProgress = 0.;
	e->swingProgressInt = -1;
	e->effects = NULL;
	e->effect_count = 0;
	e->sneaking = 0;
	e->sprinting = 0;
	e->usingItem = 0;
	e->limbSwingAmount = 0.;
	e->prevLimbSwingAmount = 0.;
	e->limbSwing = 0.;
	e->renderYawOffset = 0.;
	e->prevRenderYawOffset = 0.;
	e->ticksExisted = 0;
	e->subtype = 0;
	return e;
}

void handleMetaByte(struct entity* ent, int index, signed char b) {
	if (index == 0) {
		ent->sneaking = b & 0x02 ? 1 : 0;
		ent->sprinting = b & 0x08 ? 1 : 0;
		ent->usingItem = b & 0x10 ? 1 : 0;
	}
}

void handleMetaVarInt(struct entity* ent, int index, int32_t i) {
	if ((ent->type == ENT_SKELETON || ent->type == ENT_SLIME || ent->type == ENT_MAGMACUBE || ent->type == ENT_GUARDIAN) && index == 11) {
		ent->subtype = i;
	}
}

void handleMetaFloat(struct entity* ent, int index, float f) {

}

void handleMetaString(struct entity* ent, int index, char* str) {

	free(str);
}

void handleMetaSlot(struct entity* ent, int index, struct slot* slot) {

}

void handleMetaVector(struct entity* ent, int index, float f1, float f2, float f3) {

}

void handleMetaPosition(struct entity* ent, int index, struct encpos* pos) {

}

void handleMetaUUID(struct entity* ent, int index, struct uuid* pos) {

}

void readMetadata(struct entity* ent, unsigned char* meta, size_t size) {
	while (size > 0) {
		unsigned char index = meta[0];
		meta++;
		size--;
		if (index == 0xff || size == 0) break;
		unsigned char type = meta[0];
		meta++;
		size--;
		if (type == 0 || type == 6) {
			if (size == 0) break;
			signed char b = meta[0];
			meta++;
			size--;
			handleMetaByte(ent, index, b);
		} else if (type == 1 || type == 10 || type == 12) {
			int32_t vi = 0;
			int r = readVarInt(&vi, meta, size);
			meta += r;
			size -= r;
			handleMetaVarInt(ent, index, vi);
		} else if (type == 2) {
			if (size < 4) break;
			float f = 0.;
			memcpy(&f, meta, 4);
			meta += 4;
			size -= 4;
			swapEndian(&f, 4);
			handleMetaFloat(ent, index, f);
		} else if (type == 3 || type == 4) {
			char* str = NULL;
			int r = readString(&str, meta, size);
			meta += r;
			size -= r;
			handleMetaString(ent, index, str);
		} else if (type == 5) {
			struct slot slot;
			int r = readSlot(&slot, meta, size);
			meta += r;
			size -= r;
			handleMetaSlot(ent, index, &slot);
		} else if (type == 7) {
			if (size < 12) break;
			float f1 = 0.;
			float f2 = 0.;
			float f3 = 0.;
			memcpy(&f1, meta, 4);
			meta += 4;
			size -= 4;
			memcpy(&f2, meta, 4);
			meta += 4;
			size -= 4;
			memcpy(&f3, meta, 4);
			meta += 4;
			size -= 4;
			swapEndian(&f1, 4);
			swapEndian(&f2, 4);
			swapEndian(&f3, 4);
			handleMetaVector(ent, index, f1, f2, f3);
		} else if (type == 8) {
			struct encpos pos;
			if (size < sizeof(struct encpos)) break;
			memcpy(&pos, meta, sizeof(struct encpos));
			meta += sizeof(struct encpos);
			size -= sizeof(struct encpos);
			handleMetaPosition(ent, index, &pos);
		} else if (type == 9) {
			if (size == 0) break;
			signed char b = meta[0];
			meta++;
			size--;
			if (b) {
				struct encpos pos;
				if (size < sizeof(struct encpos)) break;
				memcpy(&pos, meta, sizeof(struct encpos));
				meta += sizeof(struct encpos);
				size -= sizeof(struct encpos);
				handleMetaPosition(ent, index, &pos);
			}
		} else if (type == 11) {
			if (size == 0) break;
			signed char b = meta[0];
			meta++;
			size--;
			if (b) {
				struct uuid uuid;
				if (size < sizeof(struct uuid)) break;
				memcpy(&uuid, meta, sizeof(struct uuid));
				meta += sizeof(struct uuid);
				size -= sizeof(struct uuid);
				handleMetaUUID(ent, index, &uuid);
			}
		}
	}
}

int getSwingTime(struct entity* ent) {
	for (size_t i = 0; i < ent->effect_count; i++) {
		if (ent->effects[i].effectID == 3) {
			return 6 - (1 + ent->effects[i].amplifier);
		} else if (ent->effects[i].effectID == 4) {
			return 6 + (1 + ent->effects[i].amplifier) * 2;
		}
	}
	return 6;
}

void copyModrState(struct modr* to, struct modr* from) {
	to->rotX = from->rotX;
	to->rotY = from->rotY;
	to->rotZ = from->rotZ;
	to->rpX = from->rpX;
	to->rpY = from->rpY;
	to->rpZ = from->rpZ;
}

void animateBipedLimbs(struct modr** modr, int i, struct entity* ent, float partialTick, int flags) {
	float sp = ent->limbSwing - ent->limbSwingAmount * (1. - partialTick);
	float rsp = ent->prevLimbSwingAmount + (ent->limbSwingAmount - ent->prevLimbSwingAmount) * (partialTick);
	if (flags & 0x01) { //arms
		modr[i]->rotX = cos(sp * .6662 + PI) * 2. * rsp * .5;
		modr[i + 1]->rotX = cos(sp * .6662) * 2. * rsp * .5;
	}
	if (flags & 0x04) {
		float timeExisted = (float) ent->ticksExisted + partialTick;
		float tcos = cos(timeExisted * .09) * .05;
		float tsin = sin(timeExisted * .067) * .05;
		modr[i]->rotZ += tcos + .05;
		modr[i + 1]->rotZ -= tcos + .05;
		modr[i]->rotX += tsin;
		modr[i + 1]->rotX -= tsin;
	}
	if (flags & 0x02) { //legs
		modr[i + 2]->rotX = cos(sp * .6662) * 1.4 * rsp;
		modr[i + 3]->rotX = cos(sp * .6662 + PI) * 1.4 * rsp;
	}
}

void animateQuadrupedLimbs(struct modr** modr, int i, struct entity* ent, float partialTick) {
	float sp = ent->limbSwing - ent->limbSwingAmount * (1. - partialTick);
	float rsp = ent->prevLimbSwingAmount + (ent->limbSwingAmount - ent->prevLimbSwingAmount) * (partialTick);
	modr[i]->rotX = cos(sp * .6662) * 1.4 * rsp;
	modr[i + 1]->rotX = cos(sp * .6662 + PI) * 1.4 * rsp;
	modr[i + 2]->rotX = cos(sp * .6662 + PI) * 1.4 * rsp;
	modr[i + 3]->rotX = cos(sp * .6662) * 1.4 * rsp;
}

void drawEntity(float partialTick, struct entity* ent) {
	glPushMatrix();
	float ppitch = interpolateAngle(ent->pitch, ent->lpitch, partialTick);
	float pyaw = interpolateAngle(ent->yaw, ent->lyaw, partialTick);
	double px = ent->x * partialTick + ent->lx * (1. - partialTick);
	double py = ent->y * partialTick + ent->ly * (1. - partialTick);
	double pz = ent->z * partialTick + ent->lz * (1. - partialTick);
	if (ent->type == ENT_MPPLAYER && distEntitySq(ent, gs.player) < 64.) {
		struct boundingbox* obb = getEntityCollision(ent);
		double lpy = py + (obb->maxY - obb->minY) + .5 - (ent->sneaking ? .25 : 0.);
		renderLivingLabel(px, lpy, pz, ent->sneaking, "username ;)", partialTick);
	}
	glTranslatef(px, py, pz);
	//
	if (ent->type == ENT_MPPLAYER) {
		resetModel (&mod_player);
		mod_player.PLAYER_BIPEDHEAD->rotX = ppitch / (180. / PI);
		float ryof = interpolateAngle(ent->prevRenderYawOffset, ent->renderYawOffset, partialTick);
		float yoff = pyaw - ryof;
		glRotatef(-ryof + 180., 0., 1., 0.);
		mod_player.PLAYER_BIPEDHEAD->rotY = yoff / (180. / PI);
		animateBipedLimbs(mod_player.children, 8, ent, partialTick, 0x07);
		if (ent->swingProgressInt > -1) {
			float swp = ent->swingProgress - ent->prevSwingProgress;
			if (swp < 0.) swp++;
			swp = ent->prevSwingProgress + swp * partialTick;
			mod_player.PLAYER_BIPEDBODY->rotY += sin(sqrt(swp) * PI * 2.) * .2;
			mod_player.PLAYER_BIPEDRIGHTARM->rpZ = sin(mod_player.PLAYER_BIPEDBODY->rotY) * 5.;
			mod_player.PLAYER_BIPEDRIGHTARM->rpX = -cos(mod_player.PLAYER_BIPEDBODY->rotY) * 5.;
			mod_player.PLAYER_BIPEDLEFTARM->rpZ = -sin(mod_player.PLAYER_BIPEDBODY->rotY) * 5.;
			mod_player.PLAYER_BIPEDLEFTARM->rpX = cos(mod_player.PLAYER_BIPEDBODY->rotY) * 5.;
			mod_player.PLAYER_BIPEDRIGHTARM->rotY += mod_player.PLAYER_BIPEDBODY->rotY;
			mod_player.PLAYER_BIPEDLEFTARM->rotY += mod_player.PLAYER_BIPEDBODY->rotY;
			mod_player.PLAYER_BIPEDLEFTARM->rotX += mod_player.PLAYER_BIPEDBODY->rotY;
			float v8 = 1. - swp;
			v8 *= v8;
			v8 *= v8;
			v8 = 1. - v8;
			float v9 = sin(v8 * PI);
			float v10 = sin(swp * PI) * -(mod_player.PLAYER_BIPEDHEAD->rotX - .7) * .75;
			mod_player.PLAYER_BIPEDRIGHTARM->rotX -= v9 * 1.2 + v10;
			mod_player.PLAYER_BIPEDRIGHTARM->rotY += mod_player.PLAYER_BIPEDBODY->rotY * 2.;
			mod_player.PLAYER_BIPEDRIGHTARM->rotZ += sin(swp * PI) * -.4;
		}
		if (ent->sneaking) {
			mod_player.PLAYER_BIPEDBODY->rotX = .5;
			mod_player.PLAYER_BIPEDRIGHTARM->rotX += .4;
			mod_player.PLAYER_BIPEDLEFTARM->rotX += .4;
			mod_player.PLAYER_BIPEDRIGHTLEG->rpZ = 4.;
			mod_player.PLAYER_BIPEDLEFTLEG->rpZ = 4.;
			mod_player.PLAYER_BIPEDRIGHTLEG->rpY = 9.;
			mod_player.PLAYER_BIPEDLEFTLEG->rpY = 9.;
			mod_player.PLAYER_BIPEDHEAD->rpY = 1.;
		}
		glBindTexture(GL_TEXTURE_2D, TX_STEVE);
		drawModel(&mod_player);
	} else {
		glRotatef(-pyaw + 180., 0., 1., 0.);
		if (ent->type == ENT_CREEPER) {
			resetModel (&mod_creeper);
			animateQuadrupedLimbs(mod_creeper.children, 3, ent, partialTick);
			glBindTexture(GL_TEXTURE_2D, TX_CREEPER);
			drawModel(&mod_creeper);
		} else if (ent->type == ENT_SKELETON) {
			if (ent->subtype == 1) {
				glPushMatrix();
				glScalef(1.2, 1.2, 1.2);
			}
			resetModel (&mod_skeleton);
			animateBipedLimbs(mod_skeleton.children, 3, ent, partialTick, 0x06);
			glBindTexture(GL_TEXTURE_2D, ent->subtype == 1 ? TX_WITHERSKELETON : TX_SKELETON);
			drawModel(&mod_skeleton);
			if (ent->subtype == 1) glPopMatrix();
		} else if (ent->type == ENT_SPIDER || ent->type == ENT_CAVESPIDER) {
			if (ent->type == ENT_CAVESPIDER) {
				glPushMatrix();
				glScalef(.7, .7, .7);
			}
			resetModel (&mod_spider);
			glBindTexture(GL_TEXTURE_2D, ent->type == ENT_SPIDER ? TX_SPIDER : TX_CAVESPIDER);
			drawModel(&mod_spider);
			if (ent->type == ENT_CAVESPIDER) glPopMatrix();
		} else if (ent->type == ENT_GIANT || ent->type == ENT_ZOMBIE || ent->type == ENT_ZPIGMAN) {
			if (ent->type == ENT_GIANT) {
				glPushMatrix();
				glScalef(6., 6., 6.);
			}
			resetModel (&mod_zombie);
			float swp = ent->swingProgress - ent->prevSwingProgress;
			if (swp < 0.) swp++;
			swp = ent->prevSwingProgress + swp * partialTick;
			float f = sin(swp * PI);
			float f1 = sin((1. - (1. - swp) * (1. - swp)) * PI);
			mod_zombie.ZOMBIE_BIPEDRIGHTARM->rotY = -(.1 - f * .6);
			mod_zombie.ZOMBIE_BIPEDLEFTARM->rotY = .1 - f * .6;
			mod_zombie.ZOMBIE_BIPEDRIGHTARM->rotX = mod_zombie.ZOMBIE_BIPEDLEFTARM->rotX = (-PI / 2.25) + (f * 1.2 - f1 * .4);
			animateBipedLimbs(mod_zombie.children, 3, ent, partialTick, 0x06);
			glBindTexture(GL_TEXTURE_2D, ent->type == ENT_ZPIGMAN ? TX_ZPIGMAN : TX_ZOMBIE);
			drawModel(&mod_zombie);
			if (ent->type == ENT_GIANT) glPopMatrix();
		} else if (ent->type == ENT_SLIME || ent->type == ENT_MAGMACUBE) {
			glPushMatrix();
			glScalef(.999, .999, .999);
			//TODO: squish factor
			glScalef((float) ent->subtype, (float) ent->subtype, (float) ent->subtype);
			struct model* mod = ent->type == ENT_SLIME ? &mod_slime : &mod_magmacube;
			resetModel(mod);
			glBindTexture(GL_TEXTURE_2D, ent->type == ENT_SLIME ? TX_SLIME : TX_MAGMACUBE);
			drawModel(mod);
			if (ent->type == ENT_SLIME) {
				resetModel (&mod_slimegel);
				drawModel(&mod_slimegel);
			}
			glPopMatrix();
		} else if (ent->type == ENT_GHAST) {
			resetModel (&mod_ghast);
			glBindTexture(GL_TEXTURE_2D, TX_GHAST);
			drawModel(&mod_ghast);
		} else if (ent->type == ENT_ENDERMAN) {
			resetModel (&mod_enderman);
			glBindTexture(GL_TEXTURE_2D, TX_ENDERMAN);
			drawModel(&mod_enderman);
		} else if (ent->type == ENT_SILVERFISH) {
			resetModel (&mod_silverfish);
			glBindTexture(GL_TEXTURE_2D, TX_SILVERFISH);
			drawModel(&mod_silverfish);
		} else if (ent->type == ENT_BLAZE) {
			resetModel (&mod_blaze);
			glBindTexture(GL_TEXTURE_2D, TX_BLAZE);
			drawModel(&mod_blaze);
		} else if (ent->type == ENT_ENDERDRAGON) {
			resetModel (&mod_dragon);
			glBindTexture(GL_TEXTURE_2D, TX_ENDERDRAGON);
			drawModel(&mod_dragon);
		} else if (ent->type == ENT_WITHER) {
			resetModel (&mod_wither);
			glBindTexture(GL_TEXTURE_2D, TX_WITHER);
			drawModel(&mod_wither);
		} else if (ent->type == ENT_BAT) {
			resetModel (&mod_bat);
			glBindTexture(GL_TEXTURE_2D, TX_BAT);
			drawModel(&mod_bat);
		} else if (ent->type == ENT_WITCH) {
			resetModel (&mod_witch);
			glBindTexture(GL_TEXTURE_2D, TX_WITCH);
			drawModel(&mod_witch);
		} else if (ent->type == ENT_ENDERMITE) {
			resetModel (&mod_endermite);
			glBindTexture(GL_TEXTURE_2D, TX_ENDERMITE);
			drawModel(&mod_endermite);
		} else if (ent->type == ENT_GUARDIAN) {
			if (ent->subtype & 0x04) {
				glPushMatrix();
				glScalef(2.35, 2.35, 2.35);
			}
			resetModel (&mod_guardian);
			glBindTexture(GL_TEXTURE_2D, (ent->subtype & 0x04) ? TX_ELDERGUARDIAN : TX_GUARDIAN);
			drawModel(&mod_guardian);
			if (ent->subtype & 0x04) glPopMatrix();
		} else if (ent->type == ENT_SHULKER) {
			resetModel (&mod_shulker);
			glBindTexture(GL_TEXTURE_2D, TX_SHULKER);
			drawModel(&mod_shulker);
		} else if (ent->type == ENT_PIG) {
			resetModel (&mod_pig);
			glBindTexture(GL_TEXTURE_2D, TX_PIG);
			drawModel(&mod_pig);
		} else if (ent->type == ENT_SHEEP) {
			resetModel (&mod_sheep);
			glBindTexture(GL_TEXTURE_2D, TX_SHEEP);
			drawModel(&mod_sheep);
		} else if (ent->type == ENT_COW || ent->type == ENT_MOOSHROOM) {
			resetModel (&mod_cow);
			glBindTexture(GL_TEXTURE_2D, ent->type == ENT_COW ? TX_COW : TX_MOOSHROOM);
			drawModel(&mod_cow);
		} else if (ent->type == ENT_CHICKEN) {
			resetModel (&mod_chicken);
			glBindTexture(GL_TEXTURE_2D, TX_CHICKEN);
			drawModel(&mod_chicken);
		} else if (ent->type == ENT_SQUID) {
			resetModel (&mod_squid);
			glBindTexture(GL_TEXTURE_2D, TX_SQUID);
			drawModel(&mod_squid);
		} else if (ent->type == ENT_WOLF) {
			resetModel (&mod_wolf);
			glBindTexture(GL_TEXTURE_2D, TX_WOLF);
			drawModel(&mod_wolf);
		} else if (ent->type == ENT_SNOWMAN) {
			resetModel (&mod_snowman);
			glBindTexture(GL_TEXTURE_2D, TX_SNOWMAN);
			drawModel(&mod_snowman);
		} else if (ent->type == ENT_OCELOT) {
			resetModel (&mod_ocelot);
			glBindTexture(GL_TEXTURE_2D, TX_OCELOT);
			drawModel(&mod_ocelot);
		} else if (ent->type == ENT_IRONGOLEM) {
			resetModel (&mod_irongolem);
			glBindTexture(GL_TEXTURE_2D, TX_IRONGOLEM);
			drawModel(&mod_irongolem);
		} else if (ent->type == ENT_HORSE) {
			resetModel (&mod_horse);
			glBindTexture(GL_TEXTURE_2D, TX_HORSEBLACK);
			drawModel(&mod_horse);
		} else if (ent->type == ENT_RABBIT) {
			resetModel (&mod_rabbit);
			glBindTexture(GL_TEXTURE_2D, TX_RABBITBLACK);
			drawModel(&mod_rabbit);
		} else if (ent->type == ENT_VILLAGER) {
			resetModel (&mod_villager);
			glBindTexture(GL_TEXTURE_2D, TX_VILLAGER);
			drawModel(&mod_villager);
		} else if (ent->type == ENT_BOAT) {
			resetModel (&mod_boat);
			glBindTexture(GL_TEXTURE_2D, TX_BOATSPRUCE);
			drawModel(&mod_boat);
		} else if (ent->type == ENT_ITEMSTACK) {

		} else if (ent->type == ENT_AREAEFFECT) {

		} else if (ent->type == ENT_MINECART) {
			resetModel (&mod_minecart);
			glBindTexture(GL_TEXTURE_2D, TX_MINECART);
			drawModel(&mod_minecart);
		} else if (ent->type == ENT_TNT) {

		} else if (ent->type == ENT_ENDERCRYSTAL) {
			resetModel (&mod_endercrystal);
			glBindTexture(GL_TEXTURE_2D, TX_ENDERCRYSTAL);
			drawModel(&mod_endercrystal);
		} else if (ent->type == ENT_ARROW) {

		} else if (ent->type == ENT_SNOWBALL) {

		} else if (ent->type == ENT_EGG) {

		} else if (ent->type == ENT_FIREBALL) {

		} else if (ent->type == ENT_FIRECHARGE) {

		} else if (ent->type == ENT_ENDERPEARL) {

		} else if (ent->type == ENT_WITHERSKULL) {
			resetModel (&mod_witherskull);
			glBindTexture(GL_TEXTURE_2D, TX_WITHER);
			drawModel(&mod_witherskull);
		} else if (ent->type == ENT_SHULKERBULLET) {
			resetModel (&mod_shulkerbullet);
			glBindTexture(GL_TEXTURE_2D, TX_SHULKERSPARK);
			drawModel(&mod_shulkerbullet);
		} else if (ent->type == ENT_FALLINGBLOCK) {

		} else if (ent->type == ENT_ITEMFRAME) {

		} else if (ent->type == ENT_EYEENDER) {

		} else if (ent->type == ENT_THROWNPOTION) {

		} else if (ent->type == ENT_FALLINGEGG) {

		} else if (ent->type == ENT_EXPBOTTLE) {

		} else if (ent->type == ENT_FIREWORK) {

		} else if (ent->type == ENT_LEASHKNOT) {
			resetModel (&mod_leashknot);
			glBindTexture(GL_TEXTURE_2D, TX_LEASHKNOT);
			drawModel(&mod_leashknot);
		} else if (ent->type == ENT_ARMORSTAND) {
			resetModel (&mod_armorstand);
			glBindTexture(GL_TEXTURE_2D, TX_ARMORSTAND);
			drawModel(&mod_armorstand);
		} else if (ent->type == ENT_FISHINGFLOAT) {

		} else if (ent->type == ENT_SPECTRALARROW) {

		} else if (ent->type == ENT_TIPPEDARROW) {

		} else if (ent->type == ENT_DRAGONFIREBALL) {

		} else if (ent->type == ENT_EXPERIENCEORB) {

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
	//
	bb_skeleton.minX = -.3;
	bb_skeleton.minY = 0.;
	bb_skeleton.minZ = -.3;
	bb_skeleton.maxX = .3;
	bb_skeleton.maxY = 1.95;
	bb_skeleton.maxZ = .3;
	//
}

struct boundingbox* getEntityCollision(struct entity* ent) {
	if (ent->type == ENT_OURPLAYER || ent->type == ENT_MPPLAYER || ent->type == ENT_CREEPER || ent->type == ENT_ZOMBIE || ent->type == ENT_ZPIGMAN || ent->type == ENT_BLAZE || ent->type == ENT_WITCH || ent->type == ENT_VILLAGER) return &bb_player;
	else if (ent->type == ENT_SKELETON) return &bb_skeleton;
	return &no_bb;
}

void freeEntity(struct entity* entity) {
	free(entity);
}
