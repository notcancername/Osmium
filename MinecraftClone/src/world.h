/*
 * world.h
 *
 *  Created on: Feb 22, 2016
 *      Author: root
 */

#ifndef WORLD_H_
#define WORLD_H_

#include "entity.h"
#include <stdlib.h>
#include "network.h"

typedef uint16_t block;

#define BLK_WOOD 1

struct chunk {
		int16_t x;
		int16_t z;
		block blocks[16][16][256]; // x, z, y?
		unsigned char biomes[16][16]; // x, z?
};

struct world {
		struct entity** entities;
		size_t entity_count;
		struct chunk** chunks;
		size_t chunk_count;
		char* levelType;
		struct encpos spawnpos;
};

struct chunk* getChunk(struct world* world, int16_t x, int16_t z);

void removeChunk(struct world* world, struct chunk* chunk);

void addChunk(struct world* world, struct chunk* chunk);

block getBlockChunk(struct chunk* chunk, uint8_t x, uint8_t y, uint8_t z);

block getBlockWorld(struct world* world, int32_t x, uint8_t y, int32_t z);

struct chunk* newChunk(int16_t x, int16_t z);

void setBlockChunk(struct chunk* chunk, block blk, uint8_t x, uint8_t y, uint8_t z);

void setBlockWorld(struct world* world, block blk, int32_t x, int32_t y, int32_t z);

struct world* newWorld();

void freeWorld(struct world* world);

void spawnEntity(struct world* world, struct entity* entity);

struct entity* despawnEntity(struct world* world, uint32_t id);

struct entity* getEntity(struct world* world, uint32_t id);

#endif /* WORLD_H_ */
