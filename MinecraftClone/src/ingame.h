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
		int moveForward;
		int moveBackward;
		int moveLeft;
		int moveRight;
		int sprinting;
		int wsprinting;
		int jumping;
		int crouching;
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
};

void ingame_keyboardCallback(int key, int scancode, int action, int mods);

void ingame_mouseMotionCallback(double x, double y);

struct gamestate gs;

void loadIngame();

void runNetwork(struct conn* conn);

void ingame_tick();

void drawIngame(float partialTick);

#endif /* INGAME_H_ */
