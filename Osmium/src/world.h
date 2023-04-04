/*
 * world.h
 *
 *  Created on: Feb 22, 2016
 *      Author: root
 */

#ifndef WORLD_H_
#define WORLD_H_

#include "entity.h"
#include "render.h"
#include <stdlib.h>
#include "network.h"

struct boundingbox {
		double minX;
		double maxX;
		double minY;
		double maxY;
		double minZ;
		double maxZ;
		struct vao* ovao;
};

typedef uint16_t block;

struct chunk {
		int16_t x;
		int16_t z;
		struct vao *vaos;
		block blocks[16][16][256]; // x, z, y
		unsigned char biomes[16][16]; // x, z
		unsigned char blockLight[16][16][128]; // x, z, y(4-bit)
		unsigned char* skyLight; // if non-NULL, points to a 2048-byte nibble-array.
		int needsUpdate[16];
		int empty;
		int kill;
        unsigned int tbufs[8];
};

struct world {
		struct entity** entities;
		size_t entity_count;
		struct chunk** chunks;
		size_t chunk_count;
		char* levelType;
		struct encpos spawnpos;
		int32_t dimension;
		uint64_t time;
		uint64_t age;
};

float interpolateAngle(float ang1, float ang2, float gradiant);

struct chunk* getChunk(struct world* world, int16_t x, int16_t z);

void removeChunk(struct world* world, struct chunk* chunk);

int getBiome(struct world* world, int32_t x, int32_t z);

void addChunk(struct world* world, struct chunk* chunk);

block getBlockChunk(struct chunk* chunk, uint8_t x, uint8_t y, uint8_t z);

block getBlockWorld(struct world* world, int32_t x, uint8_t y, int32_t z);

struct chunk* newChunk(int16_t x, int16_t z);

void freeChunk(struct chunk* chunk);

void setBlockChunk(struct chunk* chunk, block blk, uint8_t x, uint8_t y, uint8_t z);

void setBlockWorld(struct world* world, block blk, int32_t x, int32_t y, int32_t z);

struct world* newWorld();

void freeWorld(struct world* world);

void spawnEntity(struct world* world, struct entity* entity);

struct entity* despawnEntity(struct world* world, int32_t id);

struct entity* getEntity(struct world* world, int32_t id);

#endif /* WORLD_H_ */
