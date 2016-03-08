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

int running = 0;

int moveForward = 0;
int moveStrafe = 0;
float pMotionX = 0.;
float pMotionY = 0.;
float pMotionZ = 0.;
int sprinting = 0;

void ingame_tick() {
	if (!running) return;
	struct packet pkt;
	pkt.id = PKT_PLAY_CLIENT_PLAYERPOSLOOK;
	pkt.data.play_client.playerposlook.x = gs.player->x;
	pkt.data.play_client.playerposlook.y = gs.player->y;
	pkt.data.play_client.playerposlook.z = gs.player->z;
	pkt.data.play_client.playerposlook.yaw = gs.player->yaw;
	pkt.data.play_client.playerposlook.pitch = gs.player->pitch;
	pkt.data.play_client.playerposlook.onGround = gs.player->onGround;
	writePacket(gs.conn, &pkt);
	return;
	float fw = moveForward * (moveForward > 0 && sprinting ? 1.5 : 1.);
	float fs = moveStrafe * (moveForward > 0 && sprinting ? 1.5 : 1.);
	float f4 = fs * fs + fw * fw;
	if (f4 > 0.0001) {
		f4 = sqrt(f4);
		if (f4 < 1.) f4 = 1.;
		float ff = 0.02 / f4;
		float f5 = sin(-gs.player->yaw * 0.017453292);
		float f6 = cos(-gs.player->yaw * 0.017453292);
		float nmx = fs * ff * f6 - fw * ff * f5;
		float nmz = fw * ff * f6 + fs * ff * f5;
		pMotionX -= nmx;
		pMotionZ += nmz;
	}
	pMotionY -= 0.02;
	gs.player->x += (pMotionX *= 0.82);
	gs.player->y += (pMotionY *= 0.90);
	if (gs.player->y < .4) {
		gs.player->y = .4;
	}
	if (gs.player->y <= .4 && pMotionY < 0.) pMotionY = 0.;
	gs.player->z += (pMotionZ *= 0.82);
	if (fabs(pMotionX) < 0.0005) pMotionX = 0.;
	if (fabs(pMotionY) < 0.0005) pMotionY = 0.;
	if (fabs(pMotionZ) < 0.0005) pMotionZ = 0.;
	for (size_t i = 0; i < gs.world->entity_count; i++) {
		if (gs.world->entities[i] != NULL) {
			gs.world->entities[i]->lx = gs.world->entities[i]->x;
			gs.world->entities[i]->ly = gs.world->entities[i]->y;
			gs.world->entities[i]->lz = gs.world->entities[i]->z;
			gs.world->entities[i]->lyaw = gs.world->entities[i]->yaw;
			gs.world->entities[i]->lpitch = gs.world->entities[i]->pitch;
		}
	}
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

		} else if (pkt.id == PKT_PLAY_SERVER_BOSSBAR) {

		} else if (pkt.id == PKT_PLAY_SERVER_SERVERDIFFICULTY) {
			gs.difficulty = pkt.data.play_server.serverdifficulty.difficulty;
		} else if (pkt.id == PKT_PLAY_SERVER_TABCOMPLETE) {

		} else if (pkt.id == PKT_PLAY_SERVER_CHATMESSAGE) {

		} else if (pkt.id == PKT_PLAY_SERVER_MULTIBLOCKCHANGE) {

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

		} else if (pkt.id == PKT_PLAY_SERVER_UNLOADCHUNK) {

		} else if (pkt.id == PKT_PLAY_SERVER_CHANGEGAMESTATE) {

		} else if (pkt.id == PKT_PLAY_SERVER_KEEPALIVE) {
			rpkt.id = PKT_PLAY_CLIENT_KEEPALIVE;
			rpkt.data.play_client.keepalive.key = pkt.data.play_server.keepalive.key;
			writePacket(conn, &rpkt);
		} else if (pkt.id == PKT_PLAY_SERVER_CHUNKDATA) {

		} else if (pkt.id == PKT_PLAY_SERVER_EFFECT) {

		} else if (pkt.id == PKT_PLAY_SERVER_PARTICLE) {

		} else if (pkt.id == PKT_PLAY_SERVER_JOINGAME) {
			gs.difficulty = pkt.data.play_server.joingame.difficulty;
			gs.gamemode = pkt.data.play_server.joingame.gamemode;
			gs.maxPlayers = pkt.data.play_server.joingame.maxPlayers;
			gs.player = newEntity(pkt.data.play_server.joingame.eid, 0., 0., 0., ENTITY_OURPLAYER, 0., 0.);
			gs.reducedDebugInfo = pkt.data.play_server.joingame.reducedDebugInfo;
			gs.world = newWorld();
			gs.world->levelType = pkt.data.play_server.joingame.levelType;
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
			gs.player->pitch = ((pkt.data.play_server.playerposlook.flags & 0x08) == 0x08 ? gs.player->pitch : 0.) + pkt.data.play_server.playerposlook.y;
			gs.player->yaw = ((pkt.data.play_server.playerposlook.flags & 0x10) == 0x10 ? gs.player->yaw : 0.) + pkt.data.play_server.playerposlook.z;
			rpkt.id = PKT_PLAY_CLIENT_TELEPORTCONFIRM;
			rpkt.data.play_client.teleportconfirm.teleportID = pkt.data.play_server.playerposlook.teleportID;
			writePacket(conn, &rpkt);
			running = 1;
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
	}
}
