/*
 * render.c
 *
 *  Created on: Feb 23, 2016
 *      Author: root
 */

#include "render.h"
#include "inventory.h"
#ifdef __MINGW32__
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#include <GL/gl.h>
#include <GL/glext.h>
#include "xstring.h"
#include <math.h>
#include "world.h"
#include <time.h>
#include "block.h"
#include "ingame.h"
#include "entity.h"
#include "globals.h"

void virtVertex3f(union uvertex* vert, float x, float y, float z) {
	vert->vert.x = x;
	vert->vert.y = y;
	vert->vert.z = z;
}

void virtTexCoord2f(struct vertex_tex* vert, float x, float y) {
	vert->texX = x;
	vert->texY = y;
}

void createVAO(struct vertex* verticies, size_t count, struct vao* vao, int textures, int overwrite) {
	if (!overwrite) glGenVertexArrays(1, &vao->vao);
	glBindVertexArray(vao->vao);
	if (!overwrite) glGenBuffers(1, &vao->vbo);
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

void deleteVAO(struct vao* vao) {
	glDeleteBuffers(1, &vao->vbo);
	glDeleteVertexArrays(1, &vao->vao);
}

void createSubCube(float size, struct vertex_tex* vrt, float x, float y, float z, unsigned char faceMask, float tx1, float ty1, float tx2, float ty2) {
	float tx1t[6] = { tx1, tx1, tx1, tx1, tx1, tx1 };
	float ty1t[6] = { ty1, ty1, ty1, ty1, ty1, ty1 };
	float tx2t[6] = { tx2, tx2, tx2, tx2, tx2, tx2 };
	float ty2t[6] = { ty2, ty2, ty2, ty2, ty2, ty2 };
	createMultSub(size, size, size, vrt, x, y, z, faceMask, tx1t, ty1t, tx2t, ty2t);
}

void createMultSub(float xwid, float ywid, float zwid, struct vertex_tex* vrt, float x, float y, float z, unsigned char faceMask, float* tx1, float* ty1, float* tx2, float* ty2) {
	int vx = 0;
	if (faceMask & 0x01) {
		virtTexCoord2f(&vrt[vx], tx2[2], ty2[2]);
		virtVertex3f(&vrt[vx++], -xwid + x, -ywid + y, zwid + z);
		virtTexCoord2f(&vrt[vx], tx1[2], ty2[2]);
		virtVertex3f(&vrt[vx++], xwid + x, -ywid + y, zwid + z);
		virtTexCoord2f(&vrt[vx], tx2[2], ty1[2]);
		virtVertex3f(&vrt[vx++], -xwid + x, ywid + y, zwid + z);
		virtTexCoord2f(&vrt[vx], tx1[2], ty1[2]);
		virtVertex3f(&vrt[vx++], xwid + x, ywid + y, zwid + z);
	}
	if (faceMask & 0x02) {
		virtTexCoord2f(&vrt[vx], tx2[3], ty2[3]);
		virtVertex3f(&vrt[vx++], -xwid + x, -ywid + y, -zwid + z);
		virtTexCoord2f(&vrt[vx], tx2[3], ty1[3]);
		virtVertex3f(&vrt[vx++], -xwid + x, ywid + y, -zwid + z);
		virtTexCoord2f(&vrt[vx], tx1[3], ty2[3]);
		virtVertex3f(&vrt[vx++], xwid + x, -ywid + y, -zwid + z);
		virtTexCoord2f(&vrt[vx], tx1[3], ty1[3]);
		virtVertex3f(&vrt[vx++], xwid + x, ywid + y, -zwid + z);
	}
	//
	if (faceMask & 0x04) {
		virtTexCoord2f(&vrt[vx], tx1[0], ty1[0]);
		virtVertex3f(&vrt[vx++], -xwid + x, ywid + y, -zwid + z);
		virtTexCoord2f(&vrt[vx], tx1[0], ty2[0]);
		virtVertex3f(&vrt[vx++], -xwid + x, ywid + y, zwid + z);
		virtTexCoord2f(&vrt[vx], tx2[0], ty1[0]);
		virtVertex3f(&vrt[vx++], xwid + x, ywid + y, -zwid + z);
		virtTexCoord2f(&vrt[vx], tx2[0], ty2[0]);
		virtVertex3f(&vrt[vx++], xwid + x, ywid + y, zwid + z);
	}
	if (faceMask & 0x08) {
		virtTexCoord2f(&vrt[vx], tx1[1], ty1[1]);
		virtVertex3f(&vrt[vx++], -xwid + x, -ywid + y, -zwid + z);
		virtTexCoord2f(&vrt[vx], tx2[1], ty1[1]);
		virtVertex3f(&vrt[vx++], xwid + x, -ywid + y, -zwid + z);
		virtTexCoord2f(&vrt[vx], tx1[1], ty2[1]);
		virtVertex3f(&vrt[vx++], -xwid + x, -ywid + y, zwid + z);
		virtTexCoord2f(&vrt[vx], tx2[1], ty2[1]);
		virtVertex3f(&vrt[vx++], xwid + x, -ywid + y, zwid + z);
	}
	//
	if (faceMask & 0x10) {
		virtTexCoord2f(&vrt[vx], tx2[4], ty2[4]);
		virtVertex3f(&vrt[vx++], xwid + x, -ywid + y, -zwid + z);
		virtTexCoord2f(&vrt[vx], tx2[4], ty1[4]);
		virtVertex3f(&vrt[vx++], xwid + x, ywid + y, -zwid + z);
		virtTexCoord2f(&vrt[vx], tx1[4], ty2[4]);
		virtVertex3f(&vrt[vx++], xwid + x, -ywid + y, zwid + z);
		virtTexCoord2f(&vrt[vx], tx1[4], ty1[4]);
		virtVertex3f(&vrt[vx++], xwid + x, ywid + y, zwid + z);
	}
	if (faceMask & 0x20) {
		virtTexCoord2f(&vrt[vx], tx2[5], ty2[5]);
		virtVertex3f(&vrt[vx++], -xwid + x, -ywid + y, -zwid + z);
		virtTexCoord2f(&vrt[vx], tx1[5], ty2[5]);
		virtVertex3f(&vrt[vx++], -xwid + x, -ywid + y, zwid + z);
		virtTexCoord2f(&vrt[vx], tx2[5], ty1[5]);
		virtVertex3f(&vrt[vx++], -xwid + x, ywid + y, -zwid + z);
		virtTexCoord2f(&vrt[vx], tx1[5], ty1[5]);
		virtVertex3f(&vrt[vx++], -xwid + x, ywid + y, zwid + z);
	}
}

void createBBVao(struct boundingbox* bb) {
	struct vertex_tex vrt[6 * 4];
	float tg[6];
	for (int i = 0; i < 6; i++)
		tg[i] = 0.;
	createMultSub((float) (bb->maxX - bb->minX) / 2., (float) (bb->maxY - bb->minY) / 2., (float) (bb->maxZ - bb->minZ) / 2., vrt, (float) (bb->maxX + bb->minX) / 2., (float) (bb->maxY + bb->minY) / 2., (float) (bb->maxZ + bb->minZ) / 2., 0xFF, tg, tg, tg, tg);
	bb->ovao = malloc(sizeof(struct vao));
	createVAO(vrt, 6 * 4, bb->ovao, 1, 0);
}

void createMultSubCube(float size, struct vertex_tex* vrt, float x, float y, float z, unsigned char faceMask, float* tx1, float* ty1, float* tx2, float* ty2) {
	createMultSub(size, size, size, vrt, x, y, z, faceMask, tx1, ty1, tx2, ty2);
}

void createTexCube(float size, struct vao* vao) {
	struct vertex_tex vrt[24];
	createSubCube(size, vrt, 0xFF, 0., 0., 0., 0., 0., 1., 1.);
	createVAO(vrt, 24, vao, 1, 0);
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

int acc = 0;
int tvc = 0;
int updateChunk(struct chunk* chunk) {
	struct chunk* chzp = getChunk(gs.world, chunk->x, chunk->z + 1);
	struct chunk* chzn = getChunk(gs.world, chunk->x, chunk->z - 1);
	struct chunk* chxp = getChunk(gs.world, chunk->x + 1, chunk->z);
	struct chunk* chxn = getChunk(gs.world, chunk->x - 1, chunk->z);
	size_t tvcx = 0;
	for (int i = 0; i < 16; i++) {
		if (chunk->needsUpdate[i]) {
			//struct timespec ts;
			//clock_gettime(CLOCK_MONOTONIC, &ts);
			//double ms2 = (double) ts.tv_sec * 1000. + (double) ts.tv_nsec / 1000000.;
			chunk->needsUpdate[i] = 0;
			//printf("Updating section: %i, %i, %i\n", chunk->x, i, chunk->z);
			int y = i * 16;
			struct vertex_tex* vts = malloc(2048 * 4 * 6 * sizeof(struct vertex_tex));
			size_t vtsx = 2048 * 4 * 6 * sizeof(struct vertex_tex);
			size_t cvts = 0;
			//struct vertex_tex* tvts = malloc(2048 * 4 * 6 * sizeof(struct vertex_tex));
			//size_t tvtsx = 2048 * 4 * 6 * sizeof(struct vertex_tex);
			//size_t tcvts = 0;
			for (uint16_t x = 0; x < 16; x++) {
				for (uint16_t z = 0; z < 16; z++) {
					for (uint16_t sy = 0; sy < 16; sy++) {
						block blk = chunk->blocks[x][z][y + sy];
						if (blk == BLK_AIR) {

						} else {
							if (isBlockOpaque(blk)) {
								unsigned char fm = 0x3F;
								if (sy + y > 0 && isBlockOpaque(chunk->blocks[x][z][y + sy - 1])) {
									fm ^= 0x08;
								}
								if (sy + y < 255 && isBlockOpaque(chunk->blocks[x][z][y + sy + 1])) {
									fm ^= 0x04;
								}
								if (x > 0) {
									if (isBlockOpaque(chunk->blocks[x - 1][z][y + sy])) fm ^= 0x20;
								} else if (x == 0 && chxn != NULL && isBlockOpaque(chxn->blocks[15][z][y + sy])) fm ^= 0x20;
								if (x < 15) {
									if (isBlockOpaque(chunk->blocks[x + 1][z][y + sy])) fm ^= 0x10;
								} else if (x == 15 && chxp != NULL && isBlockOpaque(chxp->blocks[0][z][y + sy])) fm ^= 0x10;
								if (z > 0) {
									if (isBlockOpaque(chunk->blocks[x][z - 1][y + sy])) fm ^= 0x02;
								} else if (z == 0 && chzn != NULL && isBlockOpaque(chzn->blocks[x][15][y + sy])) fm ^= 0x02;
								if (z < 15) {
									if (isBlockOpaque(chunk->blocks[x][z + 1][y + sy])) fm ^= 0x01;
								} else if (z == 15 && chzp != NULL && isBlockOpaque(chzp->blocks[x][0][y + sy])) fm ^= 0x01;
								if (fm > 0) drawBlock(&vts, &vtsx, &cvts, blk, fm, (float) x, (float) sy, (float) z, chunk->x << 4 | x, y + sy, chunk->z << 4 | z);
							} else {
								drawBlock(&vts, &vtsx, &cvts, blk, 0xFF, (float) x, (float) sy, (float) z, chunk->x << 4 | x, y + sy, chunk->z << 4 | z);
							}
						}
					}
				}
			}
			//clock_gettime(CLOCK_MONOTONIC, &ts);
			//ms2 = ((double) ts.tv_sec * 1000. + (double) ts.tv_nsec / 1000000.) - ms2;
			//printf("chunk took: %f opaq = %i/4096\n", ms2, opaw);
			if (vtsx > 0) {
				//printf("pic (opaque) = %i\n", cvts);
				createVAO(vts, cvts, &chunk->vaos[i], 1, chunk->vaos[i].vao == -1 ? 0 : 1);
				free(vts);
				if (chunk->calls[i] == -1) {
					chunk->calls[i] = glGenLists(1);
				}
				glNewList(chunk->calls[i], GL_COMPILE);
				drawTriangleStrips4(&chunk->vaos[i]);
				glEndList();
			} else {
				if (chunk->vaos[i].vao >= 0) {
					deleteVAO(&chunk->vaos[i]);
					glDeleteLists(chunk->calls[i], 1);
					chunk->vaos[i].vao = -1;
					chunk->vaos[i].vbo = -1;
				}
			}
			//if (tvtsx > 0) {
			//printf("pic (trans) = %i\n", tcvts);
			//	createVAO(tvts, tcvts, &chunk->tvaos[i], 1, chunk->tvaos[i].vao == -1 ? 0 : 1);
			//	free(tvts);
			//} else {
			//	if (chunk->tvaos[i].vao >= 0) {
			//		deleteVAO(&chunk->tvaos[i]);
			//		chunk->tvaos[i].vao = -1;
			//		chunk->tvaos[i].vbo = -1;
			//	}
			//}
			acc++;
			tvc += cvts;			// + tcvts;
			//printf("%i chunks, %i verticies, %f verticies/chunk\n", acc, tvc, ((float) tvc / (float) acc));
		}
		if (chunk->vaos[i].vao >= 0) tvcx += chunk->vaos[i].vertex_count;
	}
	chunk->empty = (tvcx == 0);
	return 0;
}

#define FR_TOP 0
#define FR_BOTTOM 1
#define FR_LEFT 2
#define FR_RIGHT 3
#define FR_NEAR 4
#define FR_FAR 5

void drawChunk(struct chunk* chunk, struct plane* planes) {
	int t = 0;
	float ltc = 0.;
	for (int i = 0; i < 16; i++) {
		if (chunk->vaos[i].vertex_count > 0) {
			for (int x = 0; x < 6; x++) {
				struct plane* pl = &planes[x];
				double cpx = chunk->x << 4;
				if (pl->nx >= 0.) cpx += 16.;
				double cpy = i << 4;
				if (pl->ny >= 0.) cpy += 16.;
				double cpz = chunk->z << 4;
				if (pl->nz >= 0.) cpz += 16.;
				double cnx = (chunk->x + 1) << 4;
				if (pl->nx >= 0.) cnx -= 16.;
				double cny = (i + 1) << 4;
				if (pl->ny >= 0.) cny -= 16.;
				double cnz = (chunk->z + 1) << 4;
				if (pl->nz >= 0.) cnz -= 16.;
				double sdist = pl->nx * (cpx - pl->px) + pl->ny * (cpy - pl->py) + pl->nz * (cpz - pl->pz);
				double sdist2 = pl->nx * (cnx - pl->px) + pl->ny * (cny - pl->py) + pl->nz * (cnz - pl->pz);
				if (sdist < 0 && sdist2 < 0) {
					ltc++;
					goto pcnt;
				}
			}
			if (!t) {
				glPushMatrix();
				glTranslatef((float) (chunk->x << 4), 0., (float) (chunk->z << 4));
				t = 1;
			}
			if (ltc > 0) {
				glTranslatef(0., 16. * ltc, 0.);
				ltc = 0.;
			}
			if (chunk->vaos[i].vao >= 0) {
				glCallList(chunk->calls[i]);
			}
			ltc++;
			pcnt: ;
		} else {
			ltc++;
		}
	}
	if (t) glPopMatrix();
}

void crossp(double* v1, double* v2, double* res) {
	res[0] = v1[1] * v2[2] - v1[2] * v2[1];
	res[1] = v1[2] * v2[0] - v1[0] * v2[2];
	res[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

void drawWorld(struct world* world) {
	struct plane frust[6];
	double ncx = eyeX + lookX * 0.05;
	double ncy = eyeY + lookY * 0.05;
	double ncz = eyeZ + lookZ * 0.05;
	double fcx = eyeX + lookX * viewDistance;
	double fcy = eyeY + lookY * viewDistance;
	double fcz = eyeZ + lookZ * viewDistance;
	frust[FR_NEAR].nx = lookX;
	frust[FR_NEAR].ny = lookY;
	frust[FR_NEAR].nz = lookZ;
	frust[FR_NEAR].px = ncx;
	frust[FR_NEAR].py = ncy;
	frust[FR_NEAR].pz = ncz;
	frust[FR_FAR].nx = -lookX;
	frust[FR_FAR].ny = -lookY;
	frust[FR_FAR].nz = -lookZ;
	frust[FR_FAR].px = fcx;
	frust[FR_FAR].py = fcy;
	frust[FR_FAR].pz = fcz;
	double xp[3];
	double zp[3];
	zp[0] = -lookX;
	zp[1] = -lookY;
	zp[2] = -lookZ;
	double upv[3];
	upv[0] = 0.;
	upv[1] = 1.;
	upv[2] = 0.;
	crossp(upv, zp, xp);
	double aul = sqrt(xp[0] * xp[0] + xp[1] * xp[1] + xp[2] * xp[2]);
	xp[0] /= aul;
	xp[1] /= aul;
	xp[2] /= aul;
	double yp[3];
	crossp(zp, xp, yp);
	double aux[3];
	aux[0] = ncx + (yp[0] * hnear) - eyeX;
	aux[1] = ncy + (yp[1] * hnear) - eyeY;
	aux[2] = ncz + (yp[2] * hnear) - eyeZ;
	aul = sqrt(aux[0] * aux[0] + aux[1] * aux[1] + aux[2] * aux[2]);
	aux[0] /= aul;
	aux[1] /= aul;
	aux[2] /= aul;
	double norm[3];
	crossp(aux, xp, norm);
	aul = sqrt(norm[0] * norm[0] + norm[1] * norm[1] + norm[2] * norm[2]);
	norm[0] /= aul;
	norm[1] /= aul;
	norm[2] /= aul;
	frust[FR_TOP].nx = norm[0];
	frust[FR_TOP].ny = norm[1];
	frust[FR_TOP].nz = norm[2];
	frust[FR_TOP].px = ncx + (yp[0] * hnear);
	frust[FR_TOP].py = ncy + (yp[1] * hnear);
	frust[FR_TOP].pz = ncz + (yp[2] * hnear);
	//
	aux[0] = ncx - (yp[0] * hnear) - eyeX;
	aux[1] = ncy - (yp[1] * hnear) - eyeY;
	aux[2] = ncz - (yp[2] * hnear) - eyeZ;
	aul = sqrt(aux[0] * aux[0] + aux[1] * aux[1] + aux[2] * aux[2]);
	aux[0] /= aul;
	aux[1] /= aul;
	aux[2] /= aul;
	crossp(xp, aux, norm);
	aul = sqrt(norm[0] * norm[0] + norm[1] * norm[1] + norm[2] * norm[2]);
	norm[0] /= aul;
	norm[1] /= aul;
	norm[2] /= aul;
	frust[FR_BOTTOM].nx = norm[0];
	frust[FR_BOTTOM].ny = norm[1];
	frust[FR_BOTTOM].nz = norm[2];
	frust[FR_BOTTOM].px = ncx - (yp[0] * hnear);
	frust[FR_BOTTOM].py = ncy - (yp[1] * hnear);
	frust[FR_BOTTOM].pz = ncz - (yp[2] * hnear);
//
	aux[0] = ncx - (xp[0] * wnear) - eyeX;
	aux[1] = ncy - (xp[1] * wnear) - eyeY;
	aux[2] = ncz - (xp[2] * wnear) - eyeZ;
	aul = sqrt(aux[0] * aux[0] + aux[1] * aux[1] + aux[2] * aux[2]);
	aux[0] /= aul;
	aux[1] /= aul;
	aux[2] /= aul;
	crossp(aux, yp, norm);
	aul = sqrt(norm[0] * norm[0] + norm[1] * norm[1] + norm[2] * norm[2]);
	norm[0] /= aul;
	norm[1] /= aul;
	norm[2] /= aul;
	frust[FR_LEFT].nx = norm[0];
	frust[FR_LEFT].ny = norm[1];
	frust[FR_LEFT].nz = norm[2];
	frust[FR_LEFT].px = ncx - (xp[0] * wnear);
	frust[FR_LEFT].py = ncy - (xp[1] * wnear);
	frust[FR_LEFT].pz = ncz - (xp[2] * wnear);
	//
	aux[0] = ncx + (xp[0] * wnear) - eyeX;
	aux[1] = ncy + (xp[1] * wnear) - eyeY;
	aux[2] = ncz + (xp[2] * wnear) - eyeZ;
	aul = sqrt(aux[0] * aux[0] + aux[1] * aux[1] + aux[2] * aux[2]);
	aux[0] /= aul;
	aux[1] /= aul;
	aux[2] /= aul;
	crossp(yp, aux, norm);
	aul = sqrt(norm[0] * norm[0] + norm[1] * norm[1] + norm[2] * norm[2]);
	norm[0] /= aul;
	norm[1] /= aul;
	norm[2] /= aul;
	frust[FR_RIGHT].nx = norm[0];
	frust[FR_RIGHT].ny = norm[1];
	frust[FR_RIGHT].nz = norm[2];
	frust[FR_RIGHT].px = ncx + (xp[0] * wnear);
	frust[FR_RIGHT].py = ncy + (xp[1] * wnear);
	frust[FR_RIGHT].pz = ncz + (xp[2] * wnear);
	glBindTexture(GL_TEXTURE_2D, TX_DEFAULT);
	for (size_t i = 0; i < world->chunk_count; i++) {
		if (world->chunks[i] != NULL) {
			updateChunk(world->chunks[i]);
			if (!world->chunks[i]->empty) {
				drawChunk(world->chunks[i], frust);
			}
		}
	}
	//for (size_t i = 0; i < world->chunk_count; i++) {
	//	if (world->chunks[i] != NULL) {
	//		glPushMatrix();
	//		glTranslatef((float) (world->chunks[i]->x << 4), 0., (float) (world->chunks[i]->z << 4));
	//		drawChunk(world->chunks[i], 1, frust);
	//		glPopMatrix();
	//	}
	//}
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
}

void drawTriangleStrips4(struct vao* vao) {
	if (vao->vertex_count % 4 != 0) return;
	glBindVertexArray(vao->vao);
	size_t lc = vao->vertex_count / 4;
	GLsizei count[lc];
	GLint first[lc];
	for (size_t i = 0; i < lc; i++) {
		count[i] = 4;
		first[i] = i * 4;
	}
	glMultiDrawArrays(GL_TRIANGLE_STRIP, first, count, lc);
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
	glColor4f(1., 1., 1., 1.);
}

