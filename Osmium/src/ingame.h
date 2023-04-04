/*
 * ingame.h
 *
 *  Created on: Mar 6, 2016
 *      Author: root
 */

#ifndef INGAME_H_
#define INGAME_H_

#include <stdint.h>

extern int spawnedIn;

struct gamestate {
		struct world* world;
		struct entity* player;
		int difficulty;
		int gamemode;
		int maxPlayers;
		int reducedDebugInfo;
		int moveForward;
		int moveBackward;
		int moveLeft;
		int moveRight;
		int wsprinting;
		int jumping;
		int wcrouching;
		int jumpTicks;
		int usingItem;
		int flying;
		float moveSpeed;
		int isCollidedHorizontally;
		int isCollidedVertically;
		struct entity* riding;
		struct conn* conn;
		int inMenu;
		struct inventory* playerinv;
		struct inventory* openinv;
		struct slot* inCursor;
		uint64_t invAct;
		int shiftDown;
		int heldItem;
};

double distEntitySq(struct entity* ent1, struct entity* ent2);

void renderLivingLabel(double x, double y, double z, int hide, char* str, float partialTick);

void ingame_scrollCallback(double x, double y);

void ingame_keyboardCallback(int key, int scancode, int action, int mods);

void ingame_mouseMotionCallback(double x, double y);

extern struct gamestate gs;

void loadIngame();

void runNetwork(struct conn* conn);

void ingame_tick();

void drawIngame(float partialTick);

#endif /* INGAME_H_ */
