/*
 * ingame.h
 *
 *  Created on: Mar 6, 2016
 *      Author: root
 */

#ifndef INGAME_H_
#define INGAME_H_

int spawnedIn;

struct gamestate {
		struct world* world;
		struct entity* player;
		int difficulty;
		int gamemode;
		int maxPlayers;
		int reducedDebugInfo;
		struct conn* conn;
};

struct gamestate gs;

void loadIngame();

void runNetwork(struct conn* conn);

void ingame_tick();

void drawIngame(float partialTick);

#endif /* INGAME_H_ */
