/*
 * entity.c
 *
 *  Created on: Feb 22, 2016
 *      Author: root
 */

#include "entity.h"
#include <stdint.h>
#include <stdlib.h>

struct entity* newEntity(uint32_t id, float x, float y, float z, uint8_t type, float yaw, float pitch) {
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
	e->onGround = 1;
	return e;
}

void freeEntity(struct entity* entity) {
	free(entity);
}
