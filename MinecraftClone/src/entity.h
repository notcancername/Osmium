/*
 * entity.h
 *
 *  Created on: Feb 22, 2016
 *      Author: root
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <stdint.h>

#define ENTITY_OURPLAYER 1
#define ENTITY_MPPLAYER 2

struct entity {
		uint32_t id;
		double x;
		double y;
		double z;
		double lx;
		double ly;
		double lz;
		uint8_t type;
		float yaw;
		float lyaw;
		float pitch;
		float lpitch;
		int onGround;
};

struct entity* newEntity(uint32_t id, float x, float y, float z, uint8_t type, float yaw, float pitch);

void freeEntity(struct entity* entity);

#endif /* ENTITY_H_ */
