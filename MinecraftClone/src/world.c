/*
 * world.c
 *
 *  Created on: Feb 22, 2016
 *      Author: root
 */
#include "world.h"
#include "entity.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct chunk* getChunk(struct world* world, int16_t x, int16_t z) {
	for (size_t i = 0; i < world->chunk_count; i++) {
		if (world->chunks[i] != NULL && world->chunks[i]->x == x && world->chunks[i]->z == z) {
			return world->chunks[i];
		}
	}
	return NULL;
}

void removeChunk(struct world* world, struct chunk* chunk) {
	for (size_t i = 0; i < world->chunk_count; i++) {
		if (world->chunks[i] == chunk) {
			world->chunks[i] = NULL;
			return;
		}
	}
}

int getBiome(struct world* world, int32_t x, int32_t z) {
	struct chunk* chunk = getChunk(world, x >> 4, z >> 4);
	if (chunk == NULL) return 0;
	return chunk->biomes[z & 0x0f][x & 0x0f];
}

void addChunk(struct world* world, struct chunk* chunk) {
	if (world->chunks == NULL) {
		world->chunks = malloc(sizeof(struct chunk*));
		world->chunk_count = 0;
	} else {
		for (size_t i = 0; i < world->chunk_count; i++) {
			if (world->chunks[i] == NULL) {
				world->chunks[i] = chunk;
				return;
			}
		}
		world->chunks = realloc(world->chunks, sizeof(struct chunk*) * (world->chunk_count + 1));
	}
	world->chunks[world->chunk_count++] = chunk;
}

block getBlockChunk(struct chunk* chunk, uint8_t x, uint8_t y, uint8_t z) {
	if (x > 15 || z > 15 || y > 255 || x < 0 || z < 0 || y < 0) return 0;
	return chunk->blocks[x][z][y];
}

block getBlockWorld(struct world* world, int32_t x, uint8_t y, int32_t z) {
	struct chunk* chunk = getChunk(world, x >> 4, z >> 4);
	if (chunk == NULL) return 0;
	return getBlockChunk(chunk, x & 0x0f, y, z & 0x0f);
}

struct chunk* newChunk(int16_t x, int16_t z) {
	struct chunk* chunk = malloc(sizeof(struct chunk));
	memset(chunk, 0, sizeof(struct chunk));
	chunk->x = x;
	chunk->z = z;
	chunk->vaos = malloc(sizeof(struct vao) * 16);
	chunk->tvaos = malloc(sizeof(struct vao) * 16);
	for (int i = 0; i < 16; i++) {
		chunk->vaos[i].vao = -1;
		chunk->vaos[i].vbo = -1;
		chunk->tvaos[i].vao = -1;
		chunk->tvaos[i].vbo = -1;
		chunk->needsUpdate[i] = 1;
	}
	return chunk;
}

void freeChunk(struct chunk* chunk) {
	free(chunk->vaos);
	if (chunk->skyLight != NULL) free(chunk->skyLight);
	free(chunk);
}

void setBlockChunk(struct chunk* chunk, block blk, uint8_t x, uint8_t y, uint8_t z) {
	if (x > 15 || z > 15 || y > 255 || x < 0 || z < 0 || y < 0) return;
	chunk->blocks[x][z][y] = blk;
	chunk->needsUpdate[y >> 4] = 1;
}

void setBlockWorld(struct world* world, block blk, int32_t x, int32_t y, int32_t z) {
	struct chunk* chunk = getChunk(world, x >> 4, z >> 4);
	if (chunk == NULL) {
		chunk = newChunk(x >> 4, z >> 4);
		addChunk(world, chunk);
	}
	setBlockChunk(chunk, blk, x & 0x0f, y, z & 0x0f);
}

struct world* newWorld() {
	struct world* world = malloc(sizeof(struct world));
	memset(world, 0, sizeof(struct world));
	return world;
}

void freeWorld(struct world* world) {
	for (size_t i = 0; i < world->entity_count; i++) {
		if (world->entities[i] != NULL) freeEntity(world->entities[i]);
	}
	free(world);
}

void spawnEntity(struct world* world, struct entity* entity) {
	for (size_t i = 0; i < world->entity_count; i++) {
		if (world->entities[i] == NULL) {
			world->entities[i] = entity;
			return;
		}
	}
	if (world->entities == NULL) {
		world->entities = malloc(sizeof(struct entity*));
		world->entity_count = 0;
	} else {
		world->entities = realloc(world->entities, sizeof(struct entity*) * (world->entity_count + 1));
	}
	world->entities[world->entity_count++] = entity;
}

struct entity* despawnEntity(struct world* world, uint32_t id) {
	for (size_t i = 0; i < world->entity_count; i++) {
		if (world->entities[i] != NULL && world->entities[i]->id == id) {
			struct entity* ent = world->entities[i];
			world->entities[i] = NULL;
			return ent;
		}
	}
	return NULL;
}

struct entity* getEntity(struct world* world, uint32_t id) {
	for (size_t i = 0; i < world->entity_count; i++) {
		if (world->entities[i] != NULL && world->entities[i]->id == id) {
			return world->entities[i];
		}
	}
	return NULL;
}
