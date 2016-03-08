/*
 * render.c
 *
 *  Created on: Feb 23, 2016
 *      Author: root
 */

#include "render.h"
#ifdef __MINGW32__
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#include <GL/gl.h>
#include <GL/glext.h>
#include "xstring.h"
#include <math.h>
#include "world.h"

void virtVertex3f(union uvertex* vert, float x, float y, float z) {
	vert->vert.x = x;
	vert->vert.y = y;
	vert->vert.z = z;
}

void virtTexCoord2f(struct vertex_tex* vert, float x, float y) {
	vert->texX = x;
	vert->texY = y;
}

void createVAO(struct vertex* verticies, size_t count, struct vao* vao, int textures) {
	glGenVertexArrays(1, &vao->vao);
	glBindVertexArray(vao->vao);
	glGenBuffers(1, &vao->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vao->vbo);
	glBufferData(GL_ARRAY_BUFFER, count * (textures ? sizeof(struct vertex_tex) : sizeof(struct vertex)), verticies, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, textures ? sizeof(struct vertex_tex) : sizeof(struct vertex), 0);
	if (textures) glTexCoordPointer(2, GL_FLOAT, sizeof(struct vertex_tex), (void*) (sizeof(struct vertex)));
	glEnableClientState (GL_VERTEX_ARRAY);
	if (textures) glEnableClientState (GL_TEXTURE_COORD_ARRAY);
	glBindVertexArray(0);
	vao->tex = textures;
	vao->vertex_count = count;
}

void createTexCube(float size, struct vao* vao) {
	struct vertex_tex vrt[24];
	virtTexCoord2f(&vrt[0], 0.0, 0.0);
	virtVertex3f(&vrt[0], -size, -size, size);
	virtTexCoord2f(&vrt[1], 1.0, 0.0);
	virtVertex3f(&vrt[1], size, -size, size);
	virtTexCoord2f(&vrt[2], 1.0, 1.0);
	virtVertex3f(&vrt[2], size, size, size);
	virtTexCoord2f(&vrt[3], 0.0, 1.0);
	virtVertex3f(&vrt[3], -size, size, size);

	virtTexCoord2f(&vrt[4], 0.0, 0.0);
	virtVertex3f(&vrt[4], -size, -size, -size);
	virtTexCoord2f(&vrt[5], 1.0, 0.0);
	virtVertex3f(&vrt[5], size, -size, -size);
	virtTexCoord2f(&vrt[6], 1.0, 1.0);
	virtVertex3f(&vrt[6], size, size, -size);
	virtTexCoord2f(&vrt[7], 0.0, 1.0);
	virtVertex3f(&vrt[7], -size, size, -size);

	//

	virtTexCoord2f(&vrt[8], 0.0, 0.0);
	virtVertex3f(&vrt[8], -size, size, -size);
	virtTexCoord2f(&vrt[9], 1.0, 0.0);
	virtVertex3f(&vrt[9], size, size, -size);
	virtTexCoord2f(&vrt[10], 1.0, 1.0);
	virtVertex3f(&vrt[10], size, size, size);
	virtTexCoord2f(&vrt[11], 0.0, 1.0);
	virtVertex3f(&vrt[11], -size, size, size);

	virtTexCoord2f(&vrt[12], 0.0, 0.0);
	virtVertex3f(&vrt[12], -size, -size, -size);
	virtTexCoord2f(&vrt[13], 1.0, 0.0);
	virtVertex3f(&vrt[13], size, -size, -size);
	virtTexCoord2f(&vrt[14], 1.0, 1.0);
	virtVertex3f(&vrt[14], size, -size, size);
	virtTexCoord2f(&vrt[15], 0.0, 1.0);
	virtVertex3f(&vrt[15], -size, -size, size);

	//

	virtTexCoord2f(&vrt[16], 0.0, 0.0);
	virtVertex3f(&vrt[16], size, -size, -size);
	virtTexCoord2f(&vrt[17], 1.0, 0.0);
	virtVertex3f(&vrt[17], size, size, -size);
	virtTexCoord2f(&vrt[18], 1.0, 1.0);
	virtVertex3f(&vrt[18], size, size, size);
	virtTexCoord2f(&vrt[19], 0.0, 1.0);
	virtVertex3f(&vrt[19], size, -size, size);

	virtTexCoord2f(&vrt[20], 0.0, 0.0);
	virtVertex3f(&vrt[20], -size, -size, -size);
	virtTexCoord2f(&vrt[21], 1.0, 0.0);
	virtVertex3f(&vrt[21], -size, size, -size);
	virtTexCoord2f(&vrt[22], 1.0, 1.0);
	virtVertex3f(&vrt[22], -size, size, size);
	virtTexCoord2f(&vrt[23], 0.0, 1.0);
	virtVertex3f(&vrt[23], -size, -size, size);
	createVAO(vrt, 24, vao, 1);
}

void drawSkeleton(struct vao* vao) {
	if (vao->vertex_count % 2 != 0) return;
	glBindVertexArray(vao->vao);
	size_t lc = vao->vertex_count / 2;
	GLsizei count[lc];
	GLint first[lc];
	for (size_t i = 0; i < lc; i++) {
		count[i] = 2;
		first[i] = i * 2;
	}
	glMultiDrawArrays(GL_LINES, first, count, lc);
	glBindVertexArray(0);
}

void drawCube() {
	glBindVertexArray(mod_cube.vao);
	GLsizei count[6];
	count[0] = 4;
	count[1] = 4;
	count[2] = 4;
	count[3] = 4;
	count[4] = 4;
	count[5] = 4;
	GLint first[6];
	first[0] = 0;
	first[1] = 4;
	first[2] = 8;
	first[3] = 12;
	first[4] = 16;
	first[5] = 20;
	glMultiDrawArrays(GL_QUADS, first, count, 6);
	glBindVertexArray(0);
}

void drawChunk(struct chunk* chunk) {
	glEnable (GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(0., 0.125, 0.);
	for (uint16_t x = 0; x < 16; x++) {
		glPushMatrix();
		for (uint16_t z = 0; z < 16; z++) {
			glPushMatrix();
			for (uint16_t y = 0; y < 256; y++) {
				block blk = chunk->blocks[(x << 12) | (z << 8) | y];
				if (blk == BLK_WOOD) {
					glBindTexture(GL_TEXTURE_2D, TX_WOOD);
					drawCube();
				}
				glTranslatef(0., 0.25, 0.);
			}
			glPopMatrix();
			glTranslatef(0., 0., 0.25);
		}
		glPopMatrix();
		glTranslatef(0.25, 0., 0.);
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawWorld(struct world* world) {
	for (size_t i = 0; i < world->chunk_count; i++) {
		if (world->chunks[i] != NULL) {
			glPushMatrix();
			glTranslatef((float) (world->chunks[i]->x << 4) * 0.25, 0., (float) (world->chunks[i]->z << 4) * 0.25);
			drawChunk(world->chunks[i]);
			glPopMatrix();
		}
	}
}

void drawTriangles(struct vao* vao) {
	if (vao->vertex_count % 3 != 0) return;
	glBindVertexArray(vao->vao);
	size_t lc = vao->vertex_count / 3;
	GLsizei count[lc];
	GLint first[lc];
	for (size_t i = 0; i < lc; i++) {
		count[i] = 3;
		first[i] = i * 3;
	}
	glMultiDrawArrays(GL_TRIANGLES, first, count, lc);
	glBindVertexArray(0);
}

void drawQuads(struct vao* vao) {
	if (vao->vertex_count % 4 != 0) return;
	glBindVertexArray(vao->vao);
	size_t lc = vao->vertex_count / 4;
	GLsizei count[lc];
	GLint first[lc];
	for (size_t i = 0; i < lc; i++) {
		count[i] = 4;
		first[i] = i * 4;
	}
	glMultiDrawArrays(GL_QUADS, first, count, lc);
	glBindVertexArray(0);
}

void drawChar(char c, int italic) {
	float v3 = c % 16 * 8;
	float v4 = c / 16 * 8;
	float v5 = italic ? 1. : 0.;
	float v6 = fontWidth[c] - .01;
	glBindTexture(GL_TEXTURE_2D, TX_ASCII);
	glBegin (GL_TRIANGLE_STRIP);
	glTexCoord2f(v3 / 128., (v4 + 0.1) / 128.);
	glVertex3f(v5, 0., 0.);
	glTexCoord2f(v3 / 128., (v4 + 7.99 - 0.2) / 128.);
	glVertex3f(-v5, 7.99, 0.);
	glTexCoord2f((v3 + v6 - 1.) / 128., (v4 + 0.1) / 128.);
	glVertex3f(v6 - 1. + v5, 0., 0.);
	glTexCoord2f((v3 + v6 - 1.) / 128., (v4 + 7.99 - 0.2) / 128.);
	glVertex3f(v6 - 1. - v5, 7.99, 0.0);
	glEnd();
}

void drawString(char* str, int x, int y, uint32_t color) {
	size_t sl = strlen(str);
	glDisable (GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(x, y, 0.);
	glPushMatrix();
	glTranslatef(1., 1., 0.);
	uint32_t ncolor = (color & 16579836) >> 2 | (color & -16777216);
	glColor4f(((ncolor >> 16) & 0xff) / 255., ((ncolor >> 8) & 0xff) / 255., ((ncolor) & 0xff) / 255., 1.);
	for (size_t i = 0; i < sl; i++) {
		drawChar(str[i], 0);
		glTranslatef(fontWidth[str[i]], 0., 0.);
	}
	glPopMatrix();
	glColor4f(((color >> 16) & 0xff) / 255., ((color >> 8) & 0xff) / 255., ((color) & 0xff) / 255., 1.);
	for (size_t i = 0; i < sl; i++) {
		drawChar(str[i], 0);
		glTranslatef(fontWidth[str[i]], 0., 0.);
	}
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}

size_t stringWidth(char* str) {
	size_t sx = 0;
	size_t sl = strlen(str);
	for (size_t i = 0; i < sl; i++) {
		sx += fontWidth[str[i]];
	}
	return sx;
}

void trimStringToWidth(char* str, size_t width) {
	size_t sx = 0;
	size_t sl = strlen(str);
	for (size_t i = 0; i < sl; i++) {
		sx += fontWidth[str[i]];
		if (sx >= width) {
			str[i] = 0;
			return;
		}
	}
}

void drawTexturedModalRect(int x, int y, int z, int textureX, int textureY, int width, int height) {
	glBegin (GL_QUADS);
	glTexCoord2f(textureX * .00390625, (textureY + height) * .00390625);
	glVertex3f(x, y + height, z);
	glTexCoord2f((textureX + width) * .00390625, (textureY + height) * .00390625);
	glVertex3f(x + width, y + height, z);
	glTexCoord2f((textureX + width) * .00390625, textureY * .00390625);
	glVertex3f(x + width, y, z);
	glTexCoord2f(textureX * .00390625, textureY * .00390625);
	glVertex3f(x, y, z);
	glEnd();
}

void drawRect(int x, int y, int z, int width, int height, uint32_t color) {
	glDisable (GL_TEXTURE_2D);
	glColor4f((float) (color >> 16 & 0xff) / 255., (float) (color >> 8 & 0xff) / 255., (float) (color & 0xff) / 255., (float) (color >> 24 & 0xff) / 255.);
	glBegin (GL_QUADS);
	glVertex3f(x, y + height, z);
	glVertex3f(x + width, y + height, z);
	glVertex3f(x + width, y, z);
	glVertex3f(x, y, z);
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

