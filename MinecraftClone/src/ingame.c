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

int running = 0;

void loadIngame() {
	gs.moveSpeed = .1;
}

void ingame_keyboardCallback(int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_W) {
		gs.moveForward = action == GLFW_PRESS || action == GLFW_REPEAT;
	}
	if (key == GLFW_KEY_S) {
		gs.moveBackward = action == GLFW_PRESS || action == GLFW_REPEAT;
	}
	if (key == GLFW_KEY_A) {
		gs.moveLeft = action == GLFW_PRESS || action == GLFW_REPEAT;
	}
	if (key == GLFW_KEY_D) {
		gs.moveRight = action == GLFW_PRESS || action == GLFW_REPEAT;
	}
	if (key == GLFW_KEY_SPACE) {
		gs.jumping = action == GLFW_PRESS || action == GLFW_REPEAT;
	}
	if (key == GLFW_KEY_LEFT_CONTROL) {
		gs.sprinting = action == GLFW_PRESS || action == GLFW_REPEAT;
	}
	if (key == GLFW_KEY_LEFT_SHIFT) {
		gs.crouching = action == GLFW_PRESS || action == GLFW_REPEAT;
	}
}

int moc = 0;
double lmx = 0.;
double lmy = 0.;

void ingame_mouseMotionCallback(double x, double y) {
	if (gs.player != NULL && spawnedIn && hasMouse) {
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

void ingame_tick() {
	if (!running) return;
	for (size_t i = 0; i < gs.world->entity_count; i++) {
		struct entity* ent = gs.world->entities[i];
		if (ent != NULL) {
			ent->lx = gs.world->entities[i]->x;
			ent->ly = gs.world->entities[i]->y;
			ent->lz = gs.world->entities[i]->z;
			ent->lyaw = gs.world->entities[i]->yaw;
			ent->lpitch = gs.world->entities[i]->pitch;
			if (fabs(ent->motX) < 0.005) ent->motX = 0.;
			if (fabs(ent->motY) < 0.005) ent->motY = 0.;
			if (fabs(ent->motZ) < 0.005) ent->motZ = 0.;
		}
	}
	if (gs.jumping) {
		//if inwater
		//motY += 0.03999999910593033
		//else
		if (gs.player->onGround && gs.jumpTicks <= 0) {
			gs.player->motY = 0.42;
			//TODO: speed potion
			if (gs.sprinting) {
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
	if (gs.flying && gs.riding == NULL) {
		//TODO: flight
	} else {
		//TODO if in water and not flying

		//TODO else if in lava and not flying

		//ELSE
		if (gs.usingItem) {
			moveForward *= .2;
			moveStrafe *= .2;
		}
		double v3 = .91;
		if (gs.player->onGround) {
			//TODO get slipperniss of block below, multiply by .91 set to v3
		}
		float v4 = .16277136 / (v3 * v3 * v3);
		float v5 = .02;
		if (gs.player->onGround) {
			v5 = gs.moveSpeed * (gs.sprinting ? 1.3 : 1.) * v4;
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
			//TODO get slipperniss of block below, multiply by .91 set to v3
		}
		//
		//TODO: if in web
		if (gs.player->onGround && gs.crouching) {		//TODO set crouching
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
					if (b > 0 && doesBlockCollide(b)) {
						struct boundingbox* bb = getBlockCollision(b);
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
					if (b > 0 && doesBlockCollide(b)) {
						struct boundingbox* bb = getBlockCollision(b);
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
					if (b > 0 && doesBlockCollide(b)) {
						struct boundingbox* bb = getBlockCollision(b);
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
			if (lb != BLK_SLIMEBLOCK || gs.crouching) {
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
	gluPerspective((gs.sprinting && gs.moveForward && !gs.moveBackward) ? 90 : 70., (double) width / (double) height, 0.05, 16. * 25.);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	float ppitch = gs.player->pitch * (1. - partialTick) + gs.player->lpitch * partialTick;
	float pyaw = gs.player->yaw * (1. - partialTick) + gs.player->lyaw * partialTick;
	double px = gs.player->x * (1. - partialTick) + gs.player->lx * partialTick;
	double py = gs.player->y * (1. - partialTick) + gs.player->ly * partialTick;
	double pz = gs.player->z * (1. - partialTick) + gs.player->lz * partialTick;
	float v3 = cos(-gs.player->lyaw * 0.017453292 - PI);
	float v4 = sin(-pyaw * 0.017453292 - PI);
	float v5 = -cos(-ppitch * 0.017453292);
	float ly = sin(-ppitch * 0.017453292) + py;
	float lx = px + v4 * v5;
	float lz = pz + v3 * v5;
	gluLookAt(px, py + 1.62, pz, lx, ly + 1.62, lz, 0., 1., 0.);
//printf("lookat: %f, %f\n", gs.player->pitch, gs.player->yaw);
//glBindTexture(GL_TEXTURE_2D, TX_DEFAULT);
//if (!tbx) {
//	struct vertex_tex *vt = NULL;
//	size_t vts = 0;
//	drawBlock(&vt, &vts, 1, 0xFF, 0., 0., 0.);
//	createVAO(vt, vts, &tb, 1, 0);
//}
//tbx++;
//glPushMatrix();
//glTranslatef(px + 2., py + 1., pz + 1.);
//glRotatef(tbx, 0., 1., 0.);
//drawQuads(&tb);
//glPopMatrix();
	drawWorld(gs.world);
}

void runNetwork(struct conn* conn) {
	spawnedIn = 0;
	gs.conn = conn;
	struct packet pkt;
	struct packet rpkt;
	while (1) {
		if (readPacket(conn, &pkt)) {
			printf("closed\n");
			return;
		}
		//printf("recv: %i\n", pkt.id);
		if (pkt.id == PKT_PLAY_SERVER_SPAWNOBJECT) {

		} else if (pkt.id == PKT_PLAY_SERVER_SPAWNEXPERIENCEORB) {

		} else if (pkt.id == PKT_PLAY_SERVER_SPAWNGLOBALENTITY) {

		} else if (pkt.id == PKT_PLAY_SERVER_SPAWNMOB) {

		} else if (pkt.id == PKT_PLAY_SERVER_SPAWNPAINTING) {

		} else if (pkt.id == PKT_PLAY_SERVER_SPAWNPLAYER) {

		} else if (pkt.id == PKT_PLAY_SERVER_ANIMATION) {

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

		} else if (pkt.id == PKT_PLAY_SERVER_CLOSEWINDOW) {

		} else if (pkt.id == PKT_PLAY_SERVER_OPENWINDOW) {

		} else if (pkt.id == PKT_PLAY_SERVER_WINDOWITEMS) {

		} else if (pkt.id == PKT_PLAY_SERVER_WINDOWPROPERTY) {

		} else if (pkt.id == PKT_PLAY_SERVER_SETSLOT) {

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
				}
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
		} else if (pkt.id == PKT_PLAY_SERVER_EFFECT) {

		} else if (pkt.id == PKT_PLAY_SERVER_PARTICLE) {

		} else if (pkt.id == PKT_PLAY_SERVER_JOINGAME) {
			gs.difficulty = pkt.data.play_server.joingame.difficulty;
			gs.gamemode = pkt.data.play_server.joingame.gamemode;
			gs.maxPlayers = pkt.data.play_server.joingame.maxPlayers;
			gs.player = newEntity(pkt.data.play_server.joingame.eid, 0., 0., 0., ENTITY_OURPLAYER, 0., 0.);
			gs.reducedDebugInfo = pkt.data.play_server.joingame.reducedDebugInfo;
			gs.world = newWorld();
			spawnEntity(gs.world, gs.player);
			gs.world->levelType = pkt.data.play_server.joingame.levelType;
			gs.world->dimension = pkt.data.play_server.joingame.dimension;
		} else if (pkt.id == PKT_PLAY_SERVER_MAP) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYRELMOVE) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYLOOKRELMOVE) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYLOOK) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITY) {

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

		} else if (pkt.id == PKT_PLAY_SERVER_REMOVEENTITYEFFECT) {

		} else if (pkt.id == PKT_PLAY_SERVER_RESOURCEPACKSEND) {

		} else if (pkt.id == PKT_PLAY_SERVER_RESPAWN) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYHEADLOOK) {

		} else if (pkt.id == PKT_PLAY_SERVER_WORLDBORDER) {

		} else if (pkt.id == PKT_PLAY_SERVER_CAMERA) {

		} else if (pkt.id == PKT_PLAY_SERVER_HELDITEMCHANGE) {

		} else if (pkt.id == PKT_PLAY_SERVER_DISPLAYSCOREBOARD) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYMETADATA) {

		} else if (pkt.id == PKT_PLAY_SERVER_ATTACHENTITY) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYVELOCITY) {

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

		} else if (pkt.id == PKT_PLAY_SERVER_TITLE) {

		} else if (pkt.id == PKT_PLAY_SERVER_UPDATESIGN) {

		} else if (pkt.id == PKT_PLAY_SERVER_SOUNDEFFECT) {

		} else if (pkt.id == PKT_PLAY_SERVER_PLAYERLISTHEADERFOOTER) {

		} else if (pkt.id == PKT_PLAY_SERVER_COLLECTITEM) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYTELEPORT) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYPROPERTIES) {

		} else if (pkt.id == PKT_PLAY_SERVER_ENTITYEFFECT) {

		}
		rcmp: ;
	}
}
