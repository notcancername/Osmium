/*
 * ingame.c
 *
 *  Created on: Mar 6, 2016
 *      Author: root
 */

#include "ingame.h"
#include "network.h"
#include "world.h"
#include "entity.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "globals.h"
#include "render.h"
#include "gui.h"
#include "block.h"
#include <errno.h>
#include "inventory.h"

int running = 0;
struct vao skybox;

void loadIngame() {
	gs.moveSpeed = 0.1;
	struct vertex vts[676];
	int vi = 0;
	for (int x1 = -384; x1 <= 384; x1 += 64) {
		for (int x2 = -384; x2 <= 384; x2 += 64) {
			virtVertex3f(&vts[vi++], x1, 16., x2);
			virtVertex3f(&vts[vi++], x1 + 64., 16., x2);
			virtVertex3f(&vts[vi++], x1 + 64., 16., x2 + 64.);
			virtVertex3f(&vts[vi++], x1, 16., x2 + 64.);
		}
	}
	createVAO(vts, 676, &skybox, 0, 0, 4);
	gs.playerinv = malloc(sizeof(struct inventory));
	newInventory(gs.playerinv, INVTYPE_PLAYERINVENTORY, 0);
	gs.playerinv->slot_count = 46;
	viewBobbing = 1;
}

void ingame_keyboardCallback(int key, int scancode, int action, int mods) {
	if (gs.inMenu) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			gs.inMenu = 0;
		}
	} else if (gs.openinv != NULL) {
		if ((key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) || (key == GLFW_KEY_E && action == GLFW_PRESS)) {
			struct packet pkt;
			pkt.id = PKT_PLAY_CLIENT_CLOSEWINDOW;
			pkt.data.play_client.closewindow.windowID = gs.openinv->windowID;
			writePacket(gs.conn, &pkt);
			if (gs.openinv != gs.playerinv) {
				freeInventory(gs.openinv);
				free(gs.openinv);
			}
			gs.shiftDown = 0;
			gs.openinv = NULL;
		} else if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT) {
			gs.shiftDown = action == GLFW_PRESS || action == GLFW_REPEAT;
		}
	} else {
		if (key == GLFW_KEY_W) {
			gs.moveForward = action == GLFW_PRESS || action == GLFW_REPEAT;
		} else if (key == GLFW_KEY_S) {
			gs.moveBackward = action == GLFW_PRESS || action == GLFW_REPEAT;
		} else if (key == GLFW_KEY_A) {
			gs.moveLeft = action == GLFW_PRESS || action == GLFW_REPEAT;
		} else if (key == GLFW_KEY_D) {
			gs.moveRight = action == GLFW_PRESS || action == GLFW_REPEAT;
		} else if (key == GLFW_KEY_SPACE) {
			gs.jumping = action == GLFW_PRESS || action == GLFW_REPEAT;
		} else if (key == GLFW_KEY_LEFT_CONTROL) {
			gs.player->sprinting = action == GLFW_PRESS || action == GLFW_REPEAT;
		} else if (key == GLFW_KEY_LEFT_SHIFT) {
			gs.player->sneaking = action == GLFW_PRESS || action == GLFW_REPEAT;
		} else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			gs.inMenu = 1;
			gs.player->sneaking = 0;
			gs.player->sprinting = 0;
		} else if (key == GLFW_KEY_E && action == GLFW_PRESS) {
			gs.openinv = gs.playerinv;
			gs.player->sneaking = 0;
			gs.player->sprinting = 0;
		} else if (action == GLFW_PRESS && key >= GLFW_KEY_1 && key <= GLFW_KEY_9) {
			gs.heldItem = key - GLFW_KEY_1;
			struct packet pkt;
			pkt.id = PKT_PLAY_CLIENT_HELDITEMCHANGE;
			pkt.data.play_client.helditemchange.slot = gs.heldItem;
			writePacket(gs.conn, &pkt);
		}
	}
}

int moc = 0;
double lmx = 0.;
double lmy = 0.;

void ingame_scrollCallback(double x, double y) {
	if (moc) {
		gs.heldItem -= y;
		if (gs.heldItem < 0) gs.heldItem = 8;
		if (gs.heldItem > 8) gs.heldItem = 0;
		struct packet pkt;
		pkt.id = PKT_PLAY_CLIENT_HELDITEMCHANGE;
		pkt.data.play_client.helditemchange.slot = gs.heldItem;
		writePacket(gs.conn, &pkt);
	}
}

void ingame_mouseMotionCallback(double x, double y) {
	if (gs.player != NULL && spawnedIn && hasMouse && !gs.inMenu && gs.openinv == NULL) {
		if (!moc) {
			moc = 1;
			claimMouse();
		}
		int dx = lmx - x;
		int dy = lmy - y;
		gs.player->pitch -= dy * 0.1;
		if (gs.player->pitch > 89.9) gs.player->pitch = 89.9;
		if (gs.player->pitch < -89.9) gs.player->pitch = -89.9;
		gs.player->yaw -= dx * 0.1;
	} else if (moc) {
		moc = 0;
		unclaimMouse();
	}
	lmx = x;
	lmy = y;
}

double distEntitySq(struct entity* ent1, struct entity* ent2) {
	return (ent1->x - ent2->x) * (ent1->x - ent2->x) + (ent1->y - ent2->y) * (ent1->y - ent2->y) + (ent1->z - ent2->z) * (ent1->z - ent2->z);
}

void renderLivingLabel(double x, double y, double z, int hide, char* str, float partialTick) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glNormal3f(0., 1., 0.);
	float pyaw = interpolateAngle(gs.player->yaw, gs.player->lyaw, partialTick);
	glRotatef(-pyaw, 0., 1., 0.);
	glScalef(-.025, -.025, -.025);
	glDepthMask(0);
	if (!hide) glDisable (GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable (GL_TEXTURE_2D);
	int sw = stringWidth(str);
	glColor4f(0., 0., 0., .25);
	glBegin (GL_QUADS);
	glVertex3f((float) -sw / 2. - 1., -1., 0.);
	glVertex3f((float) -sw / 2. - 1., 8., 0.);
	glVertex3f((float) sw / 2. + 1., 8., 0.);
	glVertex3f((float) sw / 2. + 1., -1., 0.);
	glEnd();
	glColor4f(1., 1., 1., 1.);
	glEnable(GL_TEXTURE_2D);
	if (!hide) {
		drawString(str, -sw / 2, 0, 553648127);
		glEnable (GL_DEPTH_TEST);
	}
	glDepthMask(1);
	drawString(str, -sw / 2, 0, hide ? 553648127 : -1);
	glDisable(GL_BLEND);
	glPopMatrix();
}

float wrapAngle(float ang) {
	ang = fmod(ang, 360.);
	if (ang >= 180.) ang -= 360.;
	if (ang < -180.) ang += 360.;
	return ang;
}

void ingame_tick() {
	if (!running) return;
	for (size_t i = 0; i < gs.world->entity_count; i++) {
		struct entity* ent = gs.world->entities[i];
		if (ent != NULL) {
			if (ent->markedKill) {
				gs.world->entities[i] = NULL;
				freeEntity(ent);
				continue;
			}
			ent->prevLimbSwingAmount = ent->limbSwingAmount;
			ent->prevRenderYawOffset = ent->renderYawOffset;
			float dx = ent->x - ent->lx;
			float dz = ent->z - ent->lz;
			float dd = sqrt(dx * dx + dz * dz) * 4.;
			if (dd > 1.) dd = 1.;
			ent->limbSwingAmount += (dd - ent->limbSwingAmount) * .4;
			ent->limbSwing += ent->limbSwingAmount;
			float adjyo = ent->renderYawOffset;
			float expd = 0.;
			if (ent->swingProgress > 0.) {
				adjyo = ent->yaw;
				expd = sqrt(dd) * 3.;
			} else if (dd > 0.0025000002) {
				expd = sqrt(dd) * 3.;
				adjyo = atan2(dz, dx) * 180. / PI - 90.;
			}
			float wrdelta = wrapAngle(adjyo - ent->renderYawOffset);
			ent->renderYawOffset += wrdelta * .3;
			float wroff = wrapAngle(ent->yaw - ent->renderYawOffset);
			if (wroff < -75) wroff = -75.;
			if (wroff >= 75.) wroff = 75.;
			ent->renderYawOffset = ent->yaw - wroff;
			if (wroff * wroff > 2500.) {
				ent->renderYawOffset += wroff * .2;
			}
			ent->lx = ent->x;
			ent->ly = ent->y;
			ent->lz = ent->z;
			ent->lyaw = ent->yaw;
			ent->lpitch = ent->pitch;
			if (fabs(ent->motX) < 0.005) ent->motX = 0.;
			if (fabs(ent->motY) < 0.005) ent->motY = 0.;
			if (fabs(ent->motZ) < 0.005) ent->motZ = 0.;
			ent->prevSwingProgress = ent->swingProgress;
			if (ent->swingProgressInt >= 0) {
				float max = getSwingTime(ent);
				ent->swingProgress = 1. - ((float) ent->swingProgressInt / max);
				ent->swingProgressInt--;
			} else {
				ent->swingProgressInt = -1;
				ent->swingProgress = 0.;
			}
			ent->ticksExisted++;
		}
	}
	if (gs.player->sprinting && !gs.wsprinting) {
		struct packet pkt;
		pkt.id = PKT_PLAY_CLIENT_ENTITYACTION;
		pkt.data.play_client.entityaction.entityID = gs.player->id;
		pkt.data.play_client.entityaction.actionID = 3;
		pkt.data.play_client.entityaction.actionParameter = 0;
		writePacket(gs.conn, &pkt);
	} else if (!gs.player->sprinting && gs.wsprinting) {
		struct packet pkt;
		pkt.id = PKT_PLAY_CLIENT_ENTITYACTION;
		pkt.data.play_client.entityaction.entityID = gs.player->id;
		pkt.data.play_client.entityaction.actionID = 4;
		pkt.data.play_client.entityaction.actionParameter = 0;
		writePacket(gs.conn, &pkt);
	}
	gs.wsprinting = gs.player->sprinting;
	if (gs.player->sneaking && !gs.wcrouching) {
		struct packet pkt;
		pkt.id = PKT_PLAY_CLIENT_ENTITYACTION;
		pkt.data.play_client.entityaction.entityID = gs.player->id;
		pkt.data.play_client.entityaction.actionID = 0;
		pkt.data.play_client.entityaction.actionParameter = 0;
		writePacket(gs.conn, &pkt);
	} else if (!gs.player->sneaking && gs.wcrouching) {
		struct packet pkt;
		pkt.id = PKT_PLAY_CLIENT_ENTITYACTION;
		pkt.data.play_client.entityaction.entityID = gs.player->id;
		pkt.data.play_client.entityaction.actionID = 1;
		pkt.data.play_client.entityaction.actionParameter = 0;
		writePacket(gs.conn, &pkt);
	}
	gs.wcrouching = gs.player->sneaking;
	if (gs.jumping) {
		//if inwater
		//motY += 0.03999999910593033
		//else
		if (gs.player->onGround && gs.jumpTicks <= 0) {
			gs.player->motY = 0.42;
			//TODO: speed potion
			if (gs.player->sprinting) {
				float v1 = gs.player->yaw * .017453292;
				gs.player->motX -= sin(v1) * 0.2;
				gs.player->motZ += cos(v1) * 0.2;
			}
			gs.jumpTicks = 10;
		} else if (gs.jumpTicks > 0) gs.jumpTicks--;
	} else if (gs.jumpTicks > 0) gs.jumpTicks--;
	if (gs.player->health <= 0.) {
		gs.moveForward = 0;
		gs.moveBackward = 0;
		gs.moveLeft = 0;
		gs.moveRight = 0;
	}
	float moveForward = gs.moveForward ? 1. : 0.;
	if (gs.moveBackward) moveForward -= 1;
//printf("move %f %i %i\n", moveForward, gs.moveForward, gs.moveBackward);
	float moveStrafe = gs.moveLeft ? -1. : 0.;
	if (gs.moveRight) moveStrafe += 1;
	if (gs.player->sneaking) {
		moveForward *= .3;
		moveStrafe *= .3;
	}
	if (gs.flying && gs.riding == NULL) {
		//TODO: flight
	} else {
		//TODO if in water and not flying

		//TODO else if in lava and not flying

		//ELSE
		moveStrafe *= 0.98;
		moveForward *= 0.98;
		if (gs.usingItem) {
			moveForward *= .2;
			moveStrafe *= .2;
		}
		double v3 = .91;
		if (gs.player->onGround) {
			v3 *= 0.6;
			//TODO get slipperniss of block below, multiply by .91 set to v3
		}
		float v4 = .16277136 / (v3 * v3 * v3);
		float v5 = .02;
		if (gs.player->onGround) {
			v5 = gs.moveSpeed * (gs.player->sprinting ? 1.3 : 1.) * v4;
		} else {
			v5 = .02;
		}
		v4 = moveStrafe * moveStrafe + moveForward * moveForward;
		if (v4 > 0.0001) {
			v4 = sqrt(v4);
			if (v4 < 1.) v4 = 1.;
			float ff = v5 / v4;
			float f5 = sin(-gs.player->yaw * 0.017453292);
			float f6 = cos(-gs.player->yaw * 0.017453292);
			float nmx = moveStrafe * ff * f6 - moveForward * ff * f5;
			float nmz = moveForward * ff * f6 + moveStrafe * ff * f5;
			gs.player->motX -= nmx;
			gs.player->motZ += nmz;
		}
		v3 = .91;
		if (gs.player->onGround) {
			v3 *= 0.6;
			//TODO get slipperniss of block below, multiply by .91 set to v3
		}
		//
		//TODO: if in web
		if (gs.player->onGround && gs.player->sneaking) {		//TODO set crouching
			//TODO: crouch bounding
		}
		struct boundingbox obb;
		obb.minX = gs.player->x - 0.3;
		obb.maxX = gs.player->x + 0.3;
		obb.minZ = gs.player->z - 0.3;
		obb.maxZ = gs.player->z + 0.3;
		obb.minY = gs.player->y;
		obb.maxY = gs.player->y + 1.8;
		if (gs.player->motX < 0.) {
			obb.minX += gs.player->motX;
		} else {
			obb.maxX += gs.player->motX;
		}
		if (gs.player->motY < 0.) {
			obb.minY += gs.player->motY;
		} else {
			obb.maxY += gs.player->motY;
		}
		if (gs.player->motZ < 0.) {
			obb.minZ += gs.player->motZ;
		} else {
			obb.maxZ += gs.player->motZ;
		}
		struct boundingbox pbb;
		pbb.minX = gs.player->x - 0.3;
		pbb.maxX = gs.player->x + 0.3;
		pbb.minZ = gs.player->z - 0.3;
		pbb.maxZ = gs.player->z + 0.3;
		pbb.minY = gs.player->y;
		pbb.maxY = gs.player->y + 1.8;
		double ny = gs.player->motY;
		for (int32_t x = floor(obb.minX); x < floor(obb.maxX + 1.); x++) {
			for (int32_t z = floor(obb.minZ); z < floor(obb.maxZ + 1.); z++) {
				for (int32_t y = floor(obb.minY); y < floor(obb.maxY + 1.); y++) {
					block b = getBlockWorld(gs.world, x, y, z);
					struct boundingbox* bb = getBlockCollision(b);
					if (b > 0 && bb != NULL) {
						if (bb->maxX + x > obb.minX && bb->minX + x < obb.maxX ? (bb->maxY + y > obb.minY && bb->minY + y < obb.maxY ? bb->maxZ + z > obb.minZ && bb->minZ + z < obb.maxZ : 0) : 0) {
							if (pbb.maxX > bb->minX + x && pbb.minX < bb->maxX + x && pbb.maxZ > bb->minZ + z && pbb.minZ < bb->maxZ + z) {
								double t;
								if (ny > 0. && pbb.maxY <= bb->minY + y) {
									t = bb->minY + y - pbb.maxY;
									if (t < ny) {
										ny = t;
									}
								} else if (ny < 0. && pbb.minY >= bb->maxY + y) {
									t = bb->maxY + y - pbb.minY;
									if (t > ny) {
										ny = t;
									}
								}
							}
						}
					}
				}
			}
		}
		gs.player->y += ny;
		pbb.minY += ny;
		pbb.maxY += ny;
		double nx = gs.player->motX;
		for (int32_t x = floor(obb.minX); x < floor(obb.maxX + 1.); x++) {
			for (int32_t z = floor(obb.minZ); z < floor(obb.maxZ + 1.); z++) {
				for (int32_t y = floor(obb.minY); y < floor(obb.maxY + 1.); y++) {
					block b = getBlockWorld(gs.world, x, y, z);
					struct boundingbox* bb = getBlockCollision(b);
					if (b > 0 && bb != NULL) {
						if (bb->maxX + x > obb.minX && bb->minX + x < obb.maxX ? (bb->maxY + y > obb.minY && bb->minY + y < obb.maxY ? bb->maxZ + z > obb.minZ && bb->minZ + z < obb.maxZ : 0) : 0) {
							if (pbb.maxY > bb->minY + y && pbb.minY < bb->maxY + y && pbb.maxZ > bb->minZ + z && pbb.minZ < bb->maxZ + z) {
								double t;
								if (nx > 0. && pbb.maxX <= bb->minX + x) {
									t = bb->minX + x - pbb.maxX;
									if (t < nx) {
										nx = t;
									}
								} else if (nx < 0. && pbb.minX >= bb->maxX + x) {
									t = bb->maxX + x - pbb.minX;
									if (t > nx) {
										nx = t;
									}
								}
							}
						}
					}
				}
			}
		}
		gs.player->x += nx;
		pbb.minX += nx;
		pbb.maxX += nx;
		double nz = gs.player->motZ;
		for (int32_t x = floor(obb.minX); x < floor(obb.maxX + 1.); x++) {
			for (int32_t z = floor(obb.minZ); z < floor(obb.maxZ + 1.); z++) {
				for (int32_t y = floor(obb.minY); y < floor(obb.maxY + 1.); y++) {
					block b = getBlockWorld(gs.world, x, y, z);
					struct boundingbox* bb = getBlockCollision(b);
					if (b > 0 && bb != NULL) {
						if (bb->maxX + x > obb.minX && bb->minX + x < obb.maxX ? (bb->maxY + y > obb.minY && bb->minY + y < obb.maxY ? bb->maxZ + z > obb.minZ && bb->minZ + z < obb.maxZ : 0) : 0) {
							if (pbb.maxX > bb->minX + x && pbb.minX < bb->maxX + x && pbb.maxY > bb->minY + y && pbb.minY < bb->maxY + y) {
								double t;
								if (nz > 0. && pbb.maxZ <= bb->minZ + z) {
									t = bb->minZ + z - pbb.maxZ;
									if (t < nz) {
										nz = t;
									}
								} else if (nz < 0. && pbb.minZ >= bb->maxZ + z) {
									t = bb->maxZ + z - pbb.minZ;
									if (t > nz) {
										nz = t;
									}
								}
							}
						}
					}
				}
			}
		}
		//TODO step
		gs.player->z += nz;
		pbb.minZ += nz;
		pbb.maxZ += nz;
		gs.isCollidedHorizontally = gs.player->motX != nx || gs.player->motZ != nz;
		gs.isCollidedVertically = gs.player->motY != ny;
		gs.player->onGround = gs.isCollidedVertically && gs.player->motY < 0.;
		int32_t bx = floor(gs.player->x);
		int32_t by = floor(gs.player->y - .20000000298023224);
		int32_t bz = floor(gs.player->z);
		block lb = getBlockWorld(gs.world, bx, by, bz);
		if (lb == BLK_AIR) {
			block lbb = getBlockWorld(gs.world, bx, by - 1, bz);
			uint16_t lbi = lbb >> 4;
			if (lbi == BLK_FENCEOAK >> 4 || lbi == BLK_FENCEGATEOAK >> 4 || lbi == BLK_NETHERBRICKFENCE >> 4 || lbi == BLK_FENCEGATESPRUCE >> 4 || lbi == BLK_FENCEGATEBIRCH >> 4 || lbi == BLK_FENCEGATEJUNGLE >> 4 || lbi == BLK_FENCEGATEDARKOAK >> 4 || lbi == BLK_FENCEGATEACACIA >> 4 || lbi == BLK_FENCESPRUCE >> 4 || lbi == BLK_FENCEBIRCH >> 4 || lbi == BLK_FENCEJUNGLE >> 4 || lbi == BLK_FENCEDARKOAK >> 4 || lbi == BLK_FENCEACACIA >> 4 || lbi == BLK_COBBLESTONEWALL >> 4 || lbi == BLK_MOSSYCOBBLESTONEWALL >> 4) {
				lb = lbb;
				by--;
			}
		}
		if (gs.player->motX != nx) gs.player->motX = 0.;
		if (gs.player->motZ != nz) gs.player->motZ = 0.;

		if (gs.player->motY != ny) {
			if (lb != BLK_SLIMEBLOCK || gs.player->sneaking) {
				gs.player->motY = 0.;
			} else {
				gs.player->motY = -gs.player->motY;
			}
		}
		//
		//TODO if on ladder
		if (gs.player->onGround) {
			//TODO: soul sand
		}
		gs.player->motY -= .08;
		gs.player->motY *= .9800000190734863;
		gs.player->motX *= v3;
		gs.player->motZ *= v3;
	}
	struct packet pkt;
	pkt.id = PKT_PLAY_CLIENT_PLAYERPOSLOOK;
	pkt.data.play_client.playerposlook.x = gs.player->x;
	pkt.data.play_client.playerposlook.y = gs.player->y;
	pkt.data.play_client.playerposlook.z = gs.player->z;
	pkt.data.play_client.playerposlook.yaw = gs.player->yaw;
	pkt.data.play_client.playerposlook.pitch = gs.player->pitch;
	pkt.data.play_client.playerposlook.onGround = gs.player->onGround;
	if (writePacket(gs.conn, &pkt) != 0) {
		printf("Failed to write packet: %s\n", strerror(errno));
	}
}

//struct vao tb;
//int tbx = 0;

void drawIngame(float partialTick) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	float fov = (gs.player->sprinting && gs.moveForward && !gs.moveBackward) ? 90 : 70.;
	double whratio = (double) width / (double) height;
	gluPerspective(fov, whratio, 0.05, viewDistance);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	float ppitch = interpolateAngle(gs.player->pitch, gs.player->lpitch, partialTick);
	float pyaw = interpolateAngle(gs.player->yaw, gs.player->lyaw, partialTick);
	double px = gs.player->x * partialTick + gs.player->lx * (1. - partialTick);
	double py = gs.player->y * partialTick + gs.player->ly * (1. - partialTick);
	double pz = gs.player->z * partialTick + gs.player->lz * (1. - partialTick);
	eyeX = px;
	eyeY = py + (gs.player->sneaking ? 1.54 : 1.62);
	eyeZ = pz;
	double v3 = cos(-gs.player->lyaw * 0.017453292 - PI);
	double v4 = sin(-pyaw * 0.017453292 - PI);
	double v5 = -cos(-ppitch * 0.017453292);
	lookY = sin(-ppitch * 0.017453292);
	lookX = v4 * v5;
	lookZ = v3 * v5;
	double llen = sqrt(lookX * lookX + lookY * lookY + lookZ * lookZ);
	lookY /= llen;
	lookX /= llen;
	lookZ /= llen;
	hnear = 2 * tan(fov / 2.) * 0.05;
	wnear = hnear * whratio;
	hfar = 2 * tan(fov / 2.) * viewDistance;
	wfar = hfar * whratio;
	glRotatef(ppitch, 1., 0., 0.);
	glRotatef(pyaw + 180, 0., 1., 0.);
	if (gs.world->dimension == 1) {
		//TODO
	} else {
		glDisable (GL_TEXTURE_2D);
		glEnable (GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		float ca = 0.;
		{
			int tod = gs.world->time % 24000;
			ca = ((float) tod + partialTick) / 24000. - 0.25;
			if (ca < 0.) {
				ca++;
			} else if (ca > 1.) {
				ca--;
			}
			float cat = ca;
			ca = 1. - (float) ((cos(ca * PI) + 1) / 2.);
			ca = cat + (ca - cat) / 3.;
		}
		float cmod = cos(ca * PI * 2.) * 2. + .5;
		if (cmod < 0.) cmod = 0.;
		if (cmod > 1.) cmod = 1.;
		int pax = floor(gs.player->x);
		//int py = floor(gs.player->y);
		int paz = floor(gs.player->z);
		int bio = getBiome(gs.world, pax, paz);
		float temp = 0.8;
		if (bio == 2) temp = 2.;
		else if (bio == 3) temp = .2;
		else if (bio == 4) temp = .7;
		else if (bio == 5) temp = .25;
		else if (bio == 6) temp = .8;
		else if (bio == 8) temp = 2.;
		else if (bio == 10) temp = 0.;
		else if (bio == 11) temp = 0.;
		else if (bio == 12) temp = 0.;
		else if (bio == 13) temp = 0.;
		else if (bio == 14) temp = .9;
		else if (bio == 15) temp = .9;
		else if (bio == 16) temp = .8;
		else if (bio == 17) temp = 2.;
		else if (bio == 18) temp = .7;
		else if (bio == 19) temp = .25;
		else if (bio == 20) temp = .2;
		else if (bio == 21) temp = .95;
		else if (bio == 22) temp = .95;
		else if (bio == 23) temp = .95;
		else if (bio == 25) temp = .2;
		else if (bio == 26) temp = .05;
		else if (bio == 27) temp = .7;
		else if (bio == 28) temp = .7;
		else if (bio == 29) temp = .7;
		else if (bio == 30) temp = -.5;
		else if (bio == 31) temp = -.5;
		else if (bio == 32) temp = .3;
		else if (bio == 33) temp = .3;
		else if (bio == 34) temp = .2;
		else if (bio == 35) temp = 1.2;
		else if (bio == 36) temp = 1.;
		else if (bio == 37) temp = 2.;
		else if (bio == 38) temp = 2.;
		else if (bio == 39) temp = 2.;
		else if (bio == 129) temp = .8;
		else if (bio == 132) temp = .7;
		else if (bio == 140) temp = 0.;
		else if (bio == 165) temp = 2.;
		else if (bio == 166) temp = 2.;
		else if (bio == 167) temp = 2.;
		else if (bio == 160) temp = .25;
		else if (bio == 131) temp = .2;
		else if (bio == 162) temp = .2;
		else if (bio == 161) temp = .25;
		float fr = .7529412;
		float fg = .84705883;
		float fb = 1.;
		fr *= cmod * .94 + .06;
		fg *= cmod * .94 + .06;
		fb *= cmod * .91 + .09;
		//TODO: sunrise

		temp /= 3.;
		if (temp < -1.) temp = -1.;
		if (temp > 1.) temp = 1.;
		float h = .62222224 - temp * .05;
		float s = .5 + temp * .1;
		float br = 1.;
		float r = 0.;
		float g = 0.;
		float b = 0.;
		h = (h - (float) floor(h)) * 6.;
		float f = h - (float) floor(h);
		float p = br * (1. - s);
		float q = br * (1. - s * f);
		float t = br * (1. - (s * (1. - f)));
		int hi = (int) h;
		if (hi == 0) {
			r = br * 255. + .5;
			g = t * 255. + .5;
			b = p * 255. + .5;
		} else if (hi == 1) {
			r = q * 255. + .5;
			g = br * 255. + .5;
			b = p * 255. + .5;
		} else if (hi == 2) {
			r = p * 255. + .5;
			g = br * 255. + .5;
			b = t * 255. + .5;
		} else if (hi == 3) {
			r = p * 255. + .5;
			g = q * 255. + .5;
			b = br * 255. + .5;
		} else if (hi == 4) {
			r = t * 255. + .5;
			g = p * 255. + .5;
			b = br * 255. + .5;
		} else if (hi == 5) {
			r = br * 255. + .5;
			g = p * 255. + .5;
			b = q * 255. + .5;
		}
		r /= 255.;
		g /= 255.;
		b /= 255.;
		r *= cmod;
		g *= cmod;
		b *= cmod;
		//TODO: some kind of render distance effect on fog color
		glClearColor(fr, fg, fb, 1.);
		//TODO: rain
		//TODO: thunder
		glColor4f(r, g, b, 1.);
		glDepthMask (GL_FALSE);
		drawQuads(&skybox);
		glDepthMask (GL_TRUE);
		glColor4f(1., 1., 1., 1.);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}
	glTranslatef(-eyeX, -eyeY, -eyeZ);
	drawWorld(gs.world);
	for (int32_t i = 0; i < gs.world->entity_count; i++) {
		struct entity* ent = gs.world->entities[i];
		if (ent != NULL && ent != gs.player) {
			drawEntity(partialTick, ent);
		}
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0., swidth, sheight, 0., -1., 1.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	int ci = 0;
	glDisable (GL_DEPTH_TEST);
	glDepthMask(0);
	//glClear (GL_DEPTH_BUFFER_BIT);
	{
		glBindTexture(GL_TEXTURE_2D, TX_WIDGETS);
		drawTexturedModalRect(swidth / 2 - 91, sheight - 22, 0, 0, 0, 182, 22);
		drawTexturedModalRect(swidth / 2 - 92 + gs.heldItem * 20, sheight - 23, 1, 0, 22, 24, 22);
		for (int i = 0; i < 9; i++) {
			drawSlot(NULL, -2, gs.playerinv->slots[36 + i], swidth / 2 - 90 + i * 20 + 2, sheight - 19);
		}
	}
	if (gs.inMenu || gs.openinv != NULL) {
		glEnable (GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		ci = 1;
		glDisable (GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glDepthMask (GL_FALSE);
		glColor4f(0.0625, 0.0625, 0.0625, 0.75);
		glBegin (GL_QUADS);
		glVertex3f(0., sheight, 0.);
		glVertex3f(swidth, sheight, 0.);
		glVertex3f(swidth, 0., 0.);
		glVertex3f(0., 0., 0.);
		glEnd();
		glEnable(GL_TEXTURE_2D);
		glColor4f(1., 1., 1., 1.);
		glDisable(GL_BLEND);
	}
	if (gs.openinv != NULL) {
		drawInventory(gs.openinv, gs.playerinv);
	}
	if (gs.inMenu) {
		drawString("Game menu", swidth / 2 - stringWidth("Game menu") / 2, 36, 16777215);
		glEnable(GL_DEPTH_TEST);
		glDepthMask (GL_TRUE);
		if (drawButton(swidth / 2 - 100, sheight / 4 + 120 - 16, 200, 20, "Disconnect", 1) && mouseButton == 0) {

		}
		if (drawButton(swidth / 2 - 100, sheight / 4 + 24 - 16, 200, 20, "Back to Game", 0) && mouseButton == 0) {
			gs.inMenu = 0;
		}
		if (drawButton(swidth / 2 - 100, sheight / 4 + 96 - 16, 98, 20, "Options", 1) && mouseButton == 0) {

		}
		drawButton(swidth / 2 + 2, sheight / 4 + 96 - 16, 98, 20, "Open to LAN", 1);
		if (drawButton(swidth / 2 - 100, sheight / 4 + 48 - 16, 98, 20, "Achievements", 1) && mouseButton == 0) {

		}
		if (drawButton(swidth / 2 + 2, sheight / 4 + 48 - 16, 98, 20, "Statistics", 1) && mouseButton == 0) {

		}
	}
	glColor4f(1., 1., 1., 1.);
	if (!ci && mouseButton == 0) {
		gs.player->swingProgressInt = getSwingTime(gs.player);
		struct packet pkt;
		pkt.id = PKT_PLAY_CLIENT_ANIMATION;
		pkt.data.play_client.animation.hand = 0;
		writePacket(gs.conn, &pkt);
	}
//
	glDepthMask(1);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	fov = 70.;
	gluPerspective(fov, whratio, 0.05, viewDistance);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear (GL_DEPTH_BUFFER_BIT);
	{
		float swp = gs.player->swingProgress - gs.player->prevSwingProgress;
		if (swp < 0.) swp++;
		swp = gs.player->prevSwingProgress + swp * partialTick;
		float ewp = 0.;
		glPushMatrix();
		float v4 = -.3 * sin(sqrt(swp) * PI);
		float v5 = .4 * sin(sqrt(swp) * PI * 2);
		float v6 = -.4 * sin(swp * PI);
		glTranslatef(v4 + .64000005, v5 - .6 + ewp * -.6, v6 - .71999997);
		glRotatef(45., 0., 1., 0.);
		float v7 = sin(swp * swp * PI);
		float v8 = sin(sqrt(swp) * PI);
		glRotatef(v8 * 70., 0., 1., 0.);
		glRotatef(v7 * -20., 0., 0., 1.);
		glTranslatef(-1., 3.6, 3.5);
		glRotatef(120., 0., 0., 1.);
		glRotatef(200., 1., 0., 0.);
		glRotatef(-135., 0., 1., 0.);
		glTranslatef(5.6, 0., 0.);
		glBindTexture(GL_TEXTURE_2D, TX_STEVE);
		resetModel (&mod_player);
		mod_player.PLAYER_BIPEDRIGHTARM->rotX = 0.;
		mod_player.PLAYER_BIPEDRIGHTARM->rotY = 0.;
		mod_player.PLAYER_BIPEDRIGHTARM->rotZ = 0.;
		glBindTexture(GL_TEXTURE_2D, TX_STEVE);
		drawModr(mod_player.PLAYER_BIPEDRIGHTARM);
		glPopMatrix();
	}
}

void runNetwork(struct conn* conn) {
	spawnedIn = 0;
	gs.conn = conn;
	viewDistance = 16. * 10.;
	struct packet pkt;
	struct packet rpkt;
	while (1) {
		if (readPacket(conn, &pkt)) {
			printf("closed\n");
			return;
		}
		//printf("recv: %i\n", pkt.id);
		if (pkt.id == PKT_PLAY_SERVER_SPAWNOBJECT) {
			struct entity* ent = newEntity(pkt.data.play_server.spawnobject.entityID, pkt.data.play_server.spawnobject.x, pkt.data.play_server.spawnobject.y, pkt.data.play_server.spawnobject.z, entNetworkConvert(0, pkt.data.play_server.spawnobject.type), pkt.data.play_server.spawnobject.yaw, pkt.data.play_server.spawnobject.pitch);
			ent->motX = pkt.data.play_server.spawnobject.velX;
			ent->motY = pkt.data.play_server.spawnobject.velY;
			ent->motZ = pkt.data.play_server.spawnobject.velZ;
			ent->objectData = pkt.data.play_server.spawnobject.data;
			spawnEntity(gs.world, ent);
		} else if (pkt.id == PKT_PLAY_SERVER_SPAWNEXPERIENCEORB) {
			struct entity* ent = newEntity(pkt.data.play_server.spawnexperienceorb.entityID, pkt.data.play_server.spawnexperienceorb.x, pkt.data.play_server.spawnexperienceorb.y, pkt.data.play_server.spawnexperienceorb.z, ENT_EXPERIENCEORB, 0., 0.);
			ent->objectData = pkt.data.play_server.spawnexperienceorb.count;
			spawnEntity(gs.world, ent);
		} else if (pkt.id == PKT_PLAY_SERVER_SPAWNGLOBALENTITY) {
			//TODO:
		} else if (pkt.id == PKT_PLAY_SERVER_SPAWNMOB) {
			struct entity* ent = newEntity(pkt.data.play_server.spawnmob.entityID, pkt.data.play_server.spawnmob.x, pkt.data.play_server.spawnmob.y, pkt.data.play_server.spawnmob.z, entNetworkConvert(1, pkt.data.play_server.spawnmob.type), pkt.data.play_server.spawnmob.yaw, pkt.data.play_server.spawnmob.pitch);
			ent->motX = pkt.data.play_server.spawnmob.velX;
			ent->motY = pkt.data.play_server.spawnmob.velY;
			ent->motZ = pkt.data.play_server.spawnmob.velZ;
			ent->headpitch = pkt.data.play_server.spawnmob.headPitch;
			ent->lheadpitch = pkt.data.play_server.spawnmob.headPitch;
			readMetadata(ent, pkt.data.play_server.spawnmob.metadata, pkt.data.play_server.spawnmob.metadata_size);
			free(pkt.data.play_server.spawnmob.metadata);
			spawnEntity(gs.world, ent);
		} else if (pkt.id == PKT_PLAY_SERVER_SPAWNPAINTING) {
			//TODO:
		} else if (pkt.id == PKT_PLAY_SERVER_SPAWNPLAYER) {
			struct entity* ent = newEntity(pkt.data.play_server.spawnplayer.entityID, pkt.data.play_server.spawnplayer.x, pkt.data.play_server.spawnplayer.y, pkt.data.play_server.spawnplayer.z, ENT_MPPLAYER, pkt.data.play_server.spawnplayer.yaw, pkt.data.play_server.spawnplayer.pitch);
			readMetadata(ent, pkt.data.play_server.spawnplayer.metadata, pkt.data.play_server.spawnplayer.metadata_size);
			free(pkt.data.play_server.spawnplayer.metadata);
			spawnEntity(gs.world, ent);
		} else if (pkt.id == PKT_PLAY_SERVER_ANIMATION) {
			struct entity* ent = getEntity(gs.world, pkt.data.play_server.animation.entityID);
			if (ent != NULL) {
				if (pkt.data.play_server.animation.anim == 0) ent->swingProgressInt = getSwingTime(ent);
			}
		} else if (pkt.id == PKT_PLAY_SERVER_STATISTICS) {

		} else if (pkt.id == PKT_PLAY_SERVER_BLOCKBREAKANIMATION) {

		} else if (pkt.id == PKT_PLAY_SERVER_UPDATEBLOCKENTITY) {

		} else if (pkt.id == PKT_PLAY_SERVER_BLOCKACTION) {

		} else if (pkt.id == PKT_PLAY_SERVER_BLOCKCHANGE) {
			setBlockWorld(gs.world, pkt.data.play_server.blockchange.blockID, pkt.data.play_server.blockchange.pos.x, pkt.data.play_server.blockchange.pos.y, pkt.data.play_server.blockchange.pos.z);
		} else if (pkt.id == PKT_PLAY_SERVER_BOSSBAR) {

		} else if (pkt.id == PKT_PLAY_SERVER_SERVERDIFFICULTY) {
			gs.difficulty = pkt.data.play_server.serverdifficulty.difficulty;
		} else if (pkt.id == PKT_PLAY_SERVER_TABCOMPLETE) {

		} else if (pkt.id == PKT_PLAY_SERVER_CHATMESSAGE) {

		} else if (pkt.id == PKT_PLAY_SERVER_MULTIBLOCKCHANGE) {
			struct chunk* ch = getChunk(gs.world, pkt.data.play_server.multiblockchange.x, pkt.data.play_server.multiblockchange.z);
			if (ch == NULL) {
				free(pkt.data.play_server.multiblockchange.records);
				continue;
			}
			for (size_t i = 0; i < pkt.data.play_server.multiblockchange.record_count; i++) {
				struct mbc_record* mbcr = &pkt.data.play_server.multiblockchange.records[i];
				setBlockChunk(ch, mbcr->blockID, mbcr->x, mbcr->y, mbcr->z);
			}
			free(pkt.data.play_server.multiblockchange.records);
		} else if (pkt.id == PKT_PLAY_SERVER_CONFIRMTRANSACTION) {
			if (!pkt.data.play_server.confirmtransaction.accepted) {
				struct inventory* inv = NULL;
				if (gs.openinv != NULL && pkt.data.play_server.confirmtransaction.windowID == gs.openinv->windowID) inv = gs.openinv;
				else if (pkt.data.play_server.confirmtransaction.windowID == gs.playerinv->windowID) inv = gs.playerinv;
				else continue;
				inv->desync = pkt.data.play_server.confirmtransaction.actionID;
			}
		} else if (pkt.id == PKT_PLAY_SERVER_CLOSEWINDOW) {
			if (gs.openinv != NULL && gs.openinv->windowID == pkt.data.play_server.closewindow.windowID) {
				if (gs.openinv != gs.playerinv) {
					freeInventory(gs.openinv);
					free(gs.openinv);
				}
				gs.openinv = NULL;
			}
		} else if (pkt.id == PKT_PLAY_SERVER_OPENWINDOW) {
			if (gs.openinv != NULL) {
				if (gs.openinv != gs.playerinv) {
					freeInventory(gs.openinv);
					free(gs.openinv);
				}
				gs.openinv = NULL;
			}
			gs.openinv = malloc(sizeof(struct inventory));
			int wt = 0;
			if (streq(pkt.data.play_server.openwindow.type, "minecraft:chest")) wt = INVTYPE_CHEST;
			else if (streq(pkt.data.play_server.openwindow.type, "minecraft:crafting_table")) wt = INVTYPE_WORKBENCH;
			else if (streq(pkt.data.play_server.openwindow.type, "minecraft:furnace")) wt = INVTYPE_FURNACE;
			else if (streq(pkt.data.play_server.openwindow.type, "minecraft:dispenser")) wt = INVTYPE_DISPENSER;
			else if (streq(pkt.data.play_server.openwindow.type, "minecraft:enchanting_table")) wt = INVTYPE_ENCHANTINGTABLE;
			else if (streq(pkt.data.play_server.openwindow.type, "minecraft:brewing_stand")) wt = INVTYPE_BREWINGSTAND;
			else if (streq(pkt.data.play_server.openwindow.type, "minecraft:villager")) wt = INVTYPE_VILLAGER;
			else if (streq(pkt.data.play_server.openwindow.type, "minecraft:beacon")) wt = INVTYPE_BEACON;
			else if (streq(pkt.data.play_server.openwindow.type, "minecraft:anvil")) wt = INVTYPE_ANVIL;
			else if (streq(pkt.data.play_server.openwindow.type, "minecraft:hopper")) wt = INVTYPE_HOPPER;
			else if (streq(pkt.data.play_server.openwindow.type, "minecraft:dropper")) wt = INVTYPE_DROPPER;
			else if (streq(pkt.data.play_server.openwindow.type, "EntityHorse")) wt = INVTYPE_HORSE;
			free(pkt.data.play_server.openwindow.type);
			newInventory(gs.openinv, wt, pkt.data.play_server.openwindow.windowID);
			gs.openinv->slot_count = pkt.data.play_server.openwindow.slot_count;
			gs.openinv->title = pkt.data.play_server.openwindow.title;
		} else if (pkt.id == PKT_PLAY_SERVER_WINDOWITEMS) {
			struct inventory* inv = NULL;
			if (gs.openinv != NULL && pkt.data.play_server.windowitems.windowID == gs.openinv->windowID) inv = gs.openinv;
			else if (pkt.data.play_server.windowitems.windowID == gs.playerinv->windowID) inv = gs.playerinv;
			else {
				for (size_t i = 0; i < pkt.data.play_server.windowitems.count; i++) {
					if (pkt.data.play_server.windowitems.slots[i].nbt != NULL) {
						freeNBT(pkt.data.play_server.windowitems.slots[i].nbt);
						free(pkt.data.play_server.windowitems.slots[i].nbt);
					}
				}
				free(pkt.data.play_server.windowitems.slots);
				continue;
			}
			struct slot** slots = malloc(sizeof(struct slot*) * pkt.data.play_server.windowitems.count);
			for (size_t i = 0; i < pkt.data.play_server.windowitems.count; i++) {
				slots[i] = malloc(sizeof(struct slot));
				memcpy(slots[i], &pkt.data.play_server.windowitems.slots[i], sizeof(struct slot));
			}
			if (inv->desync != -1) {
				struct packet rpkt;
				rpkt.id = PKT_PLAY_CLIENT_CONFIRMTRANSACTION;
				rpkt.data.play_client.confirmtransaction.accepted = 1;
				rpkt.data.play_client.confirmtransaction.windowID = inv->windowID;
				rpkt.data.play_client.confirmtransaction.actionNumber = inv->desync;
				inv->desync = -1;
				if (gs.inCursor != NULL) {
					if (gs.inCursor->nbt != NULL) {
						freeNBT(gs.inCursor->nbt);
						free(gs.inCursor->nbt);
					}
					free(gs.inCursor);
					gs.inCursor = NULL;
				}
				writePacket(gs.conn, &rpkt);
			}
			setInventoryItems(inv, slots, pkt.data.play_server.windowitems.count);
		} else if (pkt.id == PKT_PLAY_SERVER_WINDOWPROPERTY) {
			struct inventory* inv = NULL;
			if (gs.openinv != NULL && pkt.data.play_server.windowproperty.windowID == gs.openinv->windowID) inv = gs.openinv;
			else if (pkt.data.play_server.windowproperty.windowID == gs.playerinv->windowID) inv = gs.playerinv;
			else continue;
			setInventoryProperty(inv, pkt.data.play_server.windowproperty.property, pkt.data.play_server.windowproperty.value);
		} else if (pkt.id == PKT_PLAY_SERVER_SETSLOT) {
			struct inventory* inv = NULL;
			if (gs.openinv != NULL && pkt.data.play_server.setslot.windowID == gs.openinv->windowID) inv = gs.openinv;
			else if (pkt.data.play_server.setslot.windowID == gs.playerinv->windowID) inv = gs.playerinv;
			else {
				freeNBT(pkt.data.play_server.setslot.data.nbt);
				free(pkt.data.play_server.setslot.data.nbt);
				continue;
			}
			struct slot* sc = malloc(sizeof(struct slot));
			memcpy(sc, &pkt.data.play_server.setslot.data, sizeof(struct slot));
			if (pkt.data.play_server.setslot.slot == -1) {
				if (gs.inCursor != NULL) {
					if (gs.inCursor->nbt != NULL) {
						freeNBT(gs.inCursor->nbt);
						free(gs.inCursor->nbt);
					}
					free(gs.inCursor);
				}
				gs.inCursor = sc;
			} else setInventorySlot(inv, sc, pkt.data.play_server.setslot.slot);
		} else if (pkt.id == PKT_PLAY_SERVER_SETCOOLDOWN) {

		} else if (pkt.id == PKT_PLAY_SERVER_PLUGINMESSAGE) {

		} else if (pkt.id == PKT_PLAY_SERVER_NAMEDSOUNDEFFECT) {

		} else if (pkt.id == PKT_PLAY_SERVER_DISCONNECT) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYSTATUS) {

		} else if (pkt.id == PKT_PLAY_SERVER_EXPLOSION) {
			for (size_t i = 0; i < pkt.data.play_server.explosion.record_count; i++) {
				struct exp_record* expr = &pkt.data.play_server.explosion.records[i];
				setBlockWorld(gs.world, 0, expr->x + (int32_t) pkt.data.play_server.explosion.x, expr->y + (int32_t) pkt.data.play_server.explosion.y, expr->z + (int32_t) pkt.data.play_server.explosion.z);
			}
			free(pkt.data.play_server.explosion.records);
			gs.player->motX += pkt.data.play_server.explosion.velX;
			gs.player->motY += pkt.data.play_server.explosion.velY;
			gs.player->motZ += pkt.data.play_server.explosion.velZ;
		} else if (pkt.id == PKT_PLAY_SERVER_UNLOADCHUNK) {
			struct chunk* ch = getChunk(gs.world, pkt.data.play_server.unloadchunk.chunkX, pkt.data.play_server.unloadchunk.chunkZ);
			if (ch != NULL) {
				removeChunk(gs.world, ch);
				freeChunk(ch);
			}
		} else if (pkt.id == PKT_PLAY_SERVER_CHANGEGAMESTATE) {

		} else if (pkt.id == PKT_PLAY_SERVER_KEEPALIVE) {
			rpkt.id = PKT_PLAY_CLIENT_KEEPALIVE;
			rpkt.data.play_client.keepalive.key = pkt.data.play_server.keepalive.key;
			writePacket(conn, &rpkt);
		} else if (pkt.id == PKT_PLAY_SERVER_CHUNKDATA) {
			unsigned char* data = pkt.data.play_server.chunkdata.data;
			size_t size = pkt.data.play_server.chunkdata.size;
			struct chunk* chunk = pkt.data.play_server.chunkdata.continuous ? newChunk(pkt.data.play_server.chunkdata.x, pkt.data.play_server.chunkdata.z) : getChunk(gs.world, pkt.data.play_server.chunkdata.x, pkt.data.play_server.chunkdata.z);
			size_t bo = 0;
			for (int32_t x = 0; x < 16; x++) { // could be more!
				if (!(pkt.data.play_server.chunkdata.bitMask & (1 << x))) {
					continue;
				}
				if (size < 1) {
					if (pkt.data.play_server.chunkdata.continuous) free(chunk);
					goto rcmp;
				}
				unsigned char bpb = data[0];
				unsigned char bpbr = bpb;
				data++;
				size--;
				int32_t plen = 0;
				int32_t* pal = NULL;
				if (bpb == 0) {
					bpbr = 13;
				} else {
					int rx = readVarInt(&plen, data, size);
					data += rx;
					size -= rx;
					pal = malloc(sizeof(int32_t) * plen);
					for (int32_t i = 0; i < plen; i++) {
						rx = readVarInt(&pal[i], data, size);
						data += rx;
						size -= rx;
					}
				}
				int32_t bks_l;
				int rx = readVarInt(&bks_l, data, size);
				data += rx;
				size -= rx;
				bks_l *= 8;
				if (bks_l < 0 || bks_l > size || bpbr > 16) {
					if (pal != NULL) free(pal);
					if (pkt.data.play_server.chunkdata.continuous) free(chunk);
					goto rcmp;
				}
				for (size_t i = 0; i < bks_l; i += 8) {
					swapEndian(data + i, 8);
				}
				size_t bs = 4096 * bpbr;
				size_t tx = (bs + (bs % 8) + bo);
				if (tx / 8 + (tx % 8 > 0 ? 1 : 0) > bks_l) {
					if (pal != NULL) free(pal);
					if (pkt.data.play_server.chunkdata.continuous) free(chunk);
					goto rcmp;
				}
				block cv = 0;
				unsigned char cvi = 0;
				int16_t bi = 0;
				for (size_t i = bo; i < bs + bo; i++) {
					unsigned char bit = data[i / 8] & (1 << (i % 8));
					if (bit) cv |= (1 << cvi);
					cvi++;
					if (cvi == bpbr) {
						cvi = 0;
						if (bpb == 0) {
							chunk->blocks[bi & 0x0f][(bi & 0xf0) >> 4][(x * 16) + ((bi & 0xf00) >> 8)] = cv;
						} else if (plen > 0 && cv < plen) {
							chunk->blocks[bi & 0x0f][(bi & 0xf0) >> 4][(x * 16) + ((bi & 0xf00) >> 8)] = pal[cv];
						} else {
							chunk->blocks[bi & 0x0f][(bi & 0xf0) >> 4][(x * 16) + ((bi & 0xf00) >> 8)] = 0;
						}
						bi++;
						cv = 0;
					}
				}
				bo = bs % 8;
				size -= bs / 8;
				data += bs / 8;
				for (size_t i = 0; i < 4096; i++) {
					unsigned char lb = data[0];
					if (i % 2 == 0) {
						lb >>= 4;
					} else {
						lb &= 0x0f;
					}
					if (i % 2 == 0) {
						chunk->blockLight[i & 0x0f][(i & 0xf0) >> 4][(x * 8) + ((i & 0xf00) >> 8)] = lb << 4;
					} else {
						chunk->blockLight[i & 0x0f][(i & 0xf0) >> 4][(x * 8) + ((i & 0xf00) >> 9)] |= lb & 0x0f;
					}
					if (i % 2 == 1) {
						data++;
						size--;
					}
				}
				if (gs.world->dimension == 0) {
					chunk->skyLight = malloc(2048);
					for (size_t i = 0; i < 4096; i++) {
						unsigned char lb = data[0];
						if (i % 2 == 0) {
							lb >>= 4;
						} else {
							lb &= 0x0f;
						}
						if (i % 2 == 0) {
							chunk->skyLight[i / 2] = lb << 4;
						} else {
							chunk->skyLight[i / 2] |= lb & 0x0f;
						}
						if (i % 2 == 1) {
							data++;
							size--;
						}
					}
				} else chunk->skyLight = NULL;
			}
			if (pkt.data.play_server.chunkdata.continuous) {
				struct chunk* cc = getChunk(gs.world, pkt.data.play_server.chunkdata.x, pkt.data.play_server.chunkdata.z);
				if (cc != NULL) {
					free(cc); //remove chunk does not dereference the chunk
					removeChunk(gs.world, cc);
				}
				addChunk(gs.world, chunk);
			}
			free(pkt.data.play_server.chunkdata.data);
			for (int32_t i = 0; i < pkt.data.play_server.chunkdata.nbtc; i++) {
				freeNBT(pkt.data.play_server.chunkdata.nbts[i]);
			}
			if (pkt.data.play_server.chunkdata.nbts != NULL) free(pkt.data.play_server.chunkdata.nbts);
		} else if (pkt.id == PKT_PLAY_SERVER_EFFECT) {

		} else if (pkt.id == PKT_PLAY_SERVER_PARTICLE) {

		} else if (pkt.id == PKT_PLAY_SERVER_JOINGAME) {
			gs.difficulty = pkt.data.play_server.joingame.difficulty;
			gs.gamemode = pkt.data.play_server.joingame.gamemode;
			gs.maxPlayers = pkt.data.play_server.joingame.maxPlayers;
			gs.player = newEntity(pkt.data.play_server.joingame.eid, 0., 0., 0., ENT_OURPLAYER, 0., 0.);
			gs.reducedDebugInfo = pkt.data.play_server.joingame.reducedDebugInfo;
			gs.world = newWorld();
			spawnEntity(gs.world, gs.player);
			gs.world->levelType = pkt.data.play_server.joingame.levelType;
			gs.world->dimension = pkt.data.play_server.joingame.dimension;
		} else if (pkt.id == PKT_PLAY_SERVER_MAP) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYRELMOVE) {
			struct entity* ent = getEntity(gs.world, pkt.data.play_server.entityrelmove.entityID);
			if (ent != NULL) {
				ent->x += pkt.data.play_server.entityrelmove.dx;
				ent->y += pkt.data.play_server.entityrelmove.dy;
				ent->z += pkt.data.play_server.entityrelmove.dz;
				ent->onGround = pkt.data.play_server.entityrelmove.onGround;
			}
		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYLOOKRELMOVE) {
			struct entity* ent = getEntity(gs.world, pkt.data.play_server.entitylookrelmove.entityID);
			if (ent != NULL) {
				ent->x += pkt.data.play_server.entitylookrelmove.dx;
				ent->y += pkt.data.play_server.entitylookrelmove.dy;
				ent->z += pkt.data.play_server.entitylookrelmove.dz;
				ent->onGround = pkt.data.play_server.entitylookrelmove.onGround;
				ent->yaw = pkt.data.play_server.entitylookrelmove.yaw;
				ent->pitch = pkt.data.play_server.entitylookrelmove.pitch;
			}
		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYLOOK) {
			struct entity* ent = getEntity(gs.world, pkt.data.play_server.entitylook.entityID);
			if (ent != NULL) {
				ent->onGround = pkt.data.play_server.entitylook.onGround;
				ent->yaw = pkt.data.play_server.entitylook.yaw;
				ent->pitch = pkt.data.play_server.entitylook.pitch;
			}
		} else if (pkt.id == PKT_PLAY_SERVER_ENTITY) {
			// this packet seems pretty useless
		} else if (pkt.id == PKT_PLAY_SERVER_VEHICLEMOVE) {

		} else if (pkt.id == PKT_PLAY_SERVER_OPENSIGNEDITOR) {

		} else if (pkt.id == PKT_PLAY_SERVER_PLAYERABILITIES) {
			//todo
			if (!spawnedIn && 0) {
				rpkt.id = PKT_PLAY_CLIENT_PLUGINMESSAGE;
				rpkt.data.play_client.pluginmessage.channel = "MC|Brand";
				rpkt.data.play_client.pluginmessage.data = "vanilla/remake in C";
				rpkt.data.play_client.pluginmessage.data_size = 19;
				writePacket(conn, &rpkt);
				rpkt.id = PKT_PLAY_CLIENT_CLIENTSTATUS;
				rpkt.data.play_client.clientstatus.actionID = 0;
				writePacket(conn, &rpkt);
			}
		} else if (pkt.id == PKT_PLAY_SERVER_COMBATEVENT) {

		} else if (pkt.id == PKT_PLAY_SERVER_PLAYERLISTITEM) {

		} else if (pkt.id == PKT_PLAY_SERVER_PLAYERPOSLOOK) {
			gs.player->x = ((pkt.data.play_server.playerposlook.flags & 0x01) == 0x01 ? gs.player->x : 0.) + pkt.data.play_server.playerposlook.x;
			gs.player->y = ((pkt.data.play_server.playerposlook.flags & 0x02) == 0x02 ? gs.player->y : 0.) + pkt.data.play_server.playerposlook.y;
			gs.player->z = ((pkt.data.play_server.playerposlook.flags & 0x04) == 0x04 ? gs.player->z : 0.) + pkt.data.play_server.playerposlook.z;
			gs.player->lx = gs.player->x;
			gs.player->ly = gs.player->y;
			gs.player->lz = gs.player->z;
			gs.player->pitch = ((pkt.data.play_server.playerposlook.flags & 0x08) == 0x08 ? gs.player->pitch : 0.) + pkt.data.play_server.playerposlook.y;
			gs.player->yaw = ((pkt.data.play_server.playerposlook.flags & 0x10) == 0x10 ? gs.player->yaw : 0.) + pkt.data.play_server.playerposlook.z;
			gs.player->health = 20.;
			printf("spawned in at: %f, %f, %f\n", gs.player->x, gs.player->y, gs.player->z);
			rpkt.id = PKT_PLAY_CLIENT_TELEPORTCONFIRM;
			rpkt.data.play_client.teleportconfirm.teleportID = pkt.data.play_server.playerposlook.teleportID;
			writePacket(conn, &rpkt);
			running = 1;
			spawnedIn = 1;
		} else if (pkt.id == PKT_PLAY_SERVER_USEBED) {

		} else if (pkt.id == PKT_PLAY_SERVER_DESTROYENTITIES) {
			for (int32_t i = 0; i < pkt.data.play_server.destroyentities.count; i++) {
				int32_t entityID = pkt.data.play_server.destroyentities.entityIDs[i];
				struct entity* ent = getEntity(gs.world, entityID);
				if (ent != NULL) ent->markedKill = 1;
			}
			free(pkt.data.play_server.destroyentities.entityIDs);
		} else if (pkt.id == PKT_PLAY_SERVER_REMOVEENTITYEFFECT) {
			struct entity* ent = getEntity(gs.world, pkt.data.play_server.removeentityeffect.entityID);
			if (ent != NULL) {
				for (size_t i = 0; i < ent->effect_count; i++) {
					ent->effects[i].duration = 0;
				}
			}
		} else if (pkt.id == PKT_PLAY_SERVER_RESOURCEPACKSEND) {

		} else if (pkt.id == PKT_PLAY_SERVER_RESPAWN) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYHEADLOOK) {
			struct entity* ent = getEntity(gs.world, pkt.data.play_server.entityheadlook.entityID);
			if (ent != NULL) {
				ent->headpitch = pkt.data.play_server.entityheadlook.headYaw;
			}
		} else if (pkt.id == PKT_PLAY_SERVER_WORLDBORDER) {

		} else if (pkt.id == PKT_PLAY_SERVER_CAMERA) {

		} else if (pkt.id == PKT_PLAY_SERVER_HELDITEMCHANGE) {
			gs.heldItem = pkt.data.play_server.helditemchange.slot;
		} else if (pkt.id == PKT_PLAY_SERVER_DISPLAYSCOREBOARD) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYMETADATA) {
			struct entity* ent = getEntity(gs.world, pkt.data.play_server.entitymetadata.entityID);
			if (ent != NULL) {
				readMetadata(ent, pkt.data.play_server.entitymetadata.metadata, pkt.data.play_server.entitymetadata.metadata_size);
			}
			free(pkt.data.play_server.entitymetadata.metadata);
		} else if (pkt.id == PKT_PLAY_SERVER_ATTACHENTITY) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYVELOCITY) {
			struct entity* ent = getEntity(gs.world, pkt.data.play_server.entityvelocity.entityID);
			if (ent != NULL) {
				ent->motX += pkt.data.play_server.entityvelocity.velX;
				ent->motY += pkt.data.play_server.entityvelocity.velY;
				ent->motZ += pkt.data.play_server.entityvelocity.velZ;
			}
		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYEQUIPMENT) {

		} else if (pkt.id == PKT_PLAY_SERVER_SETEXPERIENCE) {

		} else if (pkt.id == PKT_PLAY_SERVER_UPDATEHEALTH) {
			gs.player->health = pkt.data.play_server.updatehealth.health;
		} else if (pkt.id == PKT_PLAY_SERVER_SCOREBOARDOBJECTIVE) {

		} else if (pkt.id == PKT_PLAY_SERVER_SETPASSENGERS) {

		} else if (pkt.id == PKT_PLAY_SERVER_TEAMS) {

		} else if (pkt.id == PKT_PLAY_SERVER_UPDATESCORE) {

		} else if (pkt.id == PKT_PLAY_SERVER_SPAWNPOSITION) {
			memcpy(&gs.world->spawnpos, &pkt.data.play_server.spawnposition.pos, sizeof(struct encpos));
		} else if (pkt.id == PKT_PLAY_SERVER_TIMEUPDATE) {
			gs.world->time = pkt.data.play_server.timeupdate.time;
			gs.world->age = pkt.data.play_server.timeupdate.worldAge;
		} else if (pkt.id == PKT_PLAY_SERVER_TITLE) {

		} else if (pkt.id == PKT_PLAY_SERVER_SOUNDEFFECT) {

		} else if (pkt.id == PKT_PLAY_SERVER_PLAYERLISTHEADERFOOTER) {

		} else if (pkt.id == PKT_PLAY_SERVER_COLLECTITEM) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYTELEPORT) {
			struct entity* ent = getEntity(gs.world, pkt.data.play_server.entityteleport.entityID);
			if (ent != NULL) {
				ent->x = pkt.data.play_server.entityteleport.x;
				ent->y = pkt.data.play_server.entityteleport.y;
				ent->z = pkt.data.play_server.entityteleport.z;
				ent->onGround = pkt.data.play_server.entityteleport.onGround;
			}
		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYPROPERTIES) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYEFFECT) {
			struct entity* ent = getEntity(gs.world, pkt.data.play_server.entityeffect.entityID);
			if (ent != NULL) {
				for (size_t i = 0; i < ent->effect_count; i++) {
					if (ent->effects[i].effectID == pkt.data.play_server.entityeffect.effectID) {
						ent->effects[i].amplifier = pkt.data.play_server.entityeffect.amplifier;
						ent->effects[i].duration = pkt.data.play_server.entityeffect.duration;
						ent->effects[i].particles = pkt.data.play_server.entityeffect.hideParticles;
						goto rcmp;
					}
				}
				if (ent->effects == NULL) {
					ent->effects = malloc(sizeof(struct potioneffect));
					ent->effect_count = 0;
				} else {
					ent->effects = realloc(ent->effects, sizeof(struct potioneffect) * (ent->effect_count + 1));
				}
				ent->effects[ent->effect_count].amplifier = pkt.data.play_server.entityeffect.amplifier;
				ent->effects[ent->effect_count].effectID = pkt.data.play_server.entityeffect.effectID;
				ent->effects[ent->effect_count].duration = pkt.data.play_server.entityeffect.duration;
				ent->effects[ent->effect_count].particles = pkt.data.play_server.entityeffect.hideParticles;
			}
		}
		rcmp: ;
	}
}
