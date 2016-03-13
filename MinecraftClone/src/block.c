/*
 * block.c
 *
 *  Created on: Mar 12, 2016
 *      Author: root
 */

#include "world.h"
#include "render.h"
#include <GL/gl.h>
#include "block.h"
#include "globals.h"

void drawBlock(struct vertex_tex** vex, size_t* vexs, block block, unsigned char faceMask, float x, float y, float z) {
	//TODO: if not solid blah
	unsigned char fc = 0;
	if (faceMask & 0x01) fc++;
	if (faceMask & 0x02) fc++;
	if (faceMask & 0x04) fc++;
	if (faceMask & 0x08) fc++;
	if (faceMask & 0x10) fc++;
	if (faceMask & 0x20) fc++;
	if (*vex == NULL) {
		*vex = malloc(fc * 4 * sizeof(struct vertex_tex));
		*vexs = 0;
	} else {
		*vex = realloc(*vex, ((fc * 4) + *vexs) * sizeof(struct vertex_tex));
	}
	float tw = 1. / (float) def_wrap;
	float th = 1. / ((float) def_height / ((float) def_width / (float) def_wrap));
	float tx = 2.;
	float ty = 1.;
	if (block == BLK_STONE) {
		tx = 31;
		ty = 13;
	} else if (block == BLK_GRANITE) {
		tx = 14;
		ty = 14;
	} else if (block == BLK_POLISHEDGRANITE) {
		tx = 9;
		ty = 7;
	} else if (block >> 4 == BLK_STONE >> 4) {
		tx = 31;
		ty = 13;
	}
	createSubCube(0.5, &((*vex)[*vexs]), x + 0.5, y + 0.5, z + 0.5, faceMask, tw * tx, th * ty, tw * (tx + 1), th * (ty + 1));
	*vexs += fc * 4;
}

int isBlockOpaque(block block) {
	return block != BLK_AIR;
}

int doesBlockCollide(block block) {
	return block != BLK_AIR;
}

