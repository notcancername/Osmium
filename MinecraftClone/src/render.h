/*
 * render.h
 *
 *  Created on: Feb 23, 2016
 *      Author: root
 */

#ifndef RENDER_H_
#define RENDER_H_

#include <stdlib.h>
#include "models.h"
#include "world.h"

unsigned char fontColors[32][3];
unsigned char fontWidth[256];

struct vertex {
		float x;
		float y;
		float z;
};

struct vertex_tex {
		float x;
		float y;
		float z;
		float texX;
		float texY;
};

union uvertex {
		struct vertex vert;
		struct vertex_tex tex;
};

struct vao {
		int vao;
		int vbo;
		int tex;
		size_t vertex_count;
};

#define TX_NONE 0
#define TX_DEFAULT 1
#define TX_WIDGETS 4
#define TX_OPTIONSBG 5
#define TX_PAN0 6
#define TX_PAN1 7
#define TX_PAN2 8
#define TX_PAN3 9
#define TX_PAN4 10
#define TX_PAN5 11
#define TX_ASCII 12
#define TX_TITLE 13
#define TX_MMTT 14

void virtVertex3f(union uvertex* vert, float x, float y, float z);

void virtTexCoord2f(struct vertex_tex* vert, float x, float y);

void createVAO(struct vertex* verticies, size_t count, struct vao* vao, int textures, int overwrite);

void deleteVAO(struct vao* vao);

void createSubCube(float size, struct vertex_tex* vrt, float x, float y, float z, unsigned char faceMask, float tx1, float ty1, float tx2, float ty2);

void createMultSub(float xwid, float ywid, float zwid, struct vertex_tex* vrt, float x, float y, float z, unsigned char faceMask, float* tx1, float* ty1, float* tx2, float* ty2);

void createBBVao(struct boundingbox* bb);

void createMultSubCube(float size, struct vertex_tex* vrt, float x, float y, float z, unsigned char faceMask, float* tx1, float* ty1, float* tx2, float* ty2);

void createTexCube(float size, struct vao* vao);

void drawSkeleton(struct vao* vao);

void drawTriangles(struct vao* vao);

void drawQuads(struct vao* vao);

struct plane {
		double nx;
		double ny;
		double nz;
		double px;
		double py;
		double pz;
};

void drawChunk(struct chunk* chunk, int t, struct plane* planes);

void drawWorld(struct world* world);

void drawChar(char c, int italic);

void drawString(char* str, int x, int y, uint32_t color);

size_t stringWidth(char* str);

void trimStringToWidth(char* str, size_t width);

void drawTexturedModalRect(int x, int y, int z, int textureX, int textureY, int width, int height);

void drawRect(int x, int y, int z, int width, int height, uint32_t color);

#endif /* RENDER_H_ */
