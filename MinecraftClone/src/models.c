/*
 * models.c
 *
 *  Created on: Feb 26, 2016
 *      Author: root
 */
#include "models.h"
#include <png.h>
#include <GL/gl.h>
#include "xstring.h"
#include <errno.h>
#include <dirent.h>
#include <math.h>
#include "globals.h"

void loadBaseModels() {
	loadTexturePNG(INSTALLDIR "assets/minecraft/textures/entity/steve.png", TX_STEVE, 1);
	newModel(&mod_biped, TX_STEVE, 64, 64); // even if scaled up due to texture pack, this should still scale UV coords to 64x64
	struct modr* biped_head = malloc(sizeof(struct modr));
	newModr(biped_head, 0, 0, 64, 64, 0., 0., 0.);
	struct vertex_tex cube[24];
	createModelCube(biped_head, cube, -4., -8., -4., 8, 8, 8, 0., 0);
	biped_head->vao = malloc(sizeof(struct vao));
	createVAO(cube, 24, biped_head->vao, 1, 0);
	addModelChild(&mod_biped, biped_head);
	struct modr* biped_headwear = malloc(sizeof(struct modr));
	newModr(biped_headwear, 32, 0, 64, 64, 0., 0., 0.);
	createModelCube(biped_headwear, cube, -4., -8., -4., 8, 8, 8, .5, 0);
	biped_headwear->vao = malloc(sizeof(struct vao));
	createVAO(cube, 24, biped_headwear->vao, 1, 0);
	addModelChild(&mod_biped, biped_headwear);
	struct modr* biped_body = malloc(sizeof(struct modr));
	newModr(biped_body, 16, 16, 64, 64, 0., 0., 0.);
	createModelCube(biped_body, cube, -4., 0., -2., 8, 12, 4, 0., 0);
	biped_body->vao = malloc(sizeof(struct vao));
	createVAO(cube, 24, biped_body->vao, 1, 0);
	addModelChild(&mod_biped, biped_body);
	struct modr* biped_rightarm = malloc(sizeof(struct modr));
	newModr(biped_rightarm, 40, 16, 64, 64, -5., 2., 0.);
	createModelCube(biped_rightarm, cube, -3., -2., -2., 4, 12, 4, 0., 0);
	biped_rightarm->vao = malloc(sizeof(struct vao));
	createVAO(cube, 24, biped_rightarm->vao, 1, 0);
	addModelChild(&mod_biped, biped_rightarm);
	struct modr* biped_leftarm = malloc(sizeof(struct modr));
	newModr(biped_leftarm, 40, 16, 64, 64, 5., 2., 0.);
	createModelCube(biped_leftarm, cube, -1., -2., -2., 4, 12, 4, 0., 1);
	biped_leftarm->vao = malloc(sizeof(struct vao));
	createVAO(cube, 24, biped_leftarm->vao, 1, 0);
	addModelChild(&mod_biped, biped_leftarm);
	struct modr* biped_rightleg = malloc(sizeof(struct modr));
	newModr(biped_rightleg, 0, 16, 64, 64, -1.9, 12., 0.);
	createModelCube(biped_rightleg, cube, -2., 0., -2., 4, 12, 4, 0., 0);
	biped_rightleg->vao = malloc(sizeof(struct vao));
	createVAO(cube, 24, biped_rightleg->vao, 1, 0);
	addModelChild(&mod_biped, biped_rightleg);
	struct modr* biped_leftleg = malloc(sizeof(struct modr));
	newModr(biped_leftleg, 0, 16, 64, 64, 1.9, 12., 0.);
	createModelCube(biped_leftleg, cube, -2., 0., -2., 4, 12, 4, 0., 1);
	biped_leftleg->vao = malloc(sizeof(struct vao));
	createVAO(cube, 24, biped_leftleg->vao, 1, 0);
	addModelChild(&mod_biped, biped_leftleg);
}

void newModel(struct model* model, int tx, int width, int height) {
	model->tex = tx;
	model->txh = height;
	model->txw = width;
	model->children = NULL;
	model->child_count = 0;
}

void newModr(struct modr* modr, int txx, int txy, int txw, int txh, float rpX, float rpY, float rpZ) {
	modr->child_count = 0;
	modr->children = NULL;
	modr->txx = txx;
	modr->txy = txy;
	modr->txh = txh;
	modr->txw = txw;
	modr->vao = NULL;
	modr->rotX = 0.;
	modr->rotY = 0.;
	modr->rotZ = 0.;
	modr->defRotX = 0.;
	modr->defRotY = 0.;
	modr->defRotZ = 0.;
	modr->defrpX = rpX;
	modr->defrpY = rpY;
	modr->defrpZ = rpZ;
	modr->rpX = rpX;
	modr->rpY = rpY;
	modr->rpZ = rpZ;
}

void setModrAngles(struct modr* modr, float rotX, float rotY, float rotZ) {
	modr->rotX = rotX;
	modr->rotY = rotY;
	modr->rotZ = rotZ;
}

void setModrDefAngles(struct modr* modr, float rotX, float rotY, float rotZ) {
	modr->defRotX = rotX;
	modr->defRotY = rotY;
	modr->defRotZ = rotZ;
}

void setModrAnglePoint(struct modr* modr, float rpX, float rpY, float rpZ) {
	modr->rpX = rpX;
	modr->rpY = rpY;
	modr->rpZ = rpZ;
}

void setModrDefAnglePoint(struct modr* modr, float rpX, float rpY, float rpZ) {
	modr->defrpX = rpX;
	modr->defrpY = rpY;
	modr->defrpZ = rpZ;
}

void resetModr(struct modr* modr) {
	modr->rpX = modr->defrpX;
	modr->rpY = modr->defrpY;
	modr->rpZ = modr->defrpZ;
	modr->rotX = modr->defRotX;
	modr->rotY = modr->defRotY;
	modr->rotZ = modr->defRotZ;
	for (size_t i = 0; i < modr->child_count; i++) {
		resetModr(modr->children[i]);
	}
}

void resetModel(struct model* model) {
	for (size_t i = 0; i < model->child_count; i++) {
		resetModr(model->children[i]);
	}
}

void addModrChild(struct modr* modr, struct modr* child) {
	if (modr->children == NULL) {
		modr->children = malloc(sizeof(struct modr*));
		modr->child_count = 0;
	} else {
		modr->children = realloc(modr->children, sizeof(struct modr*) * (1 + modr->child_count));
	}
	modr->children[modr->child_count++] = child;
}

void addModelChild(struct model* model, struct modr* child) {
	if (model->children == NULL) {
		model->children = malloc(sizeof(struct modr*));
		model->child_count = 0;
	} else {
		model->children = realloc(model->children, sizeof(struct modr*) * (1 + model->child_count));
	}
	model->children[model->child_count++] = child;
}

void xferVerticiesQuad(struct vertex_tex* to, struct vertex_tex** from, int x1, int y1, int x2, int y2, float txw, float txh, int mirror) {
	struct vertex_tex* mir[4];
	struct vertex_tex** rt = mir;
	if (mirror) {
		mir[0] = &to[3];
		mir[1] = &to[2];
		mir[2] = &to[1];
		mir[3] = &to[0];
	} else {
		mir[0] = &to[0];
		mir[1] = &to[1];
		mir[2] = &to[2];
		mir[3] = &to[3];
	}
	for (int i = 0; i < 4; i++) {
		(rt)[i]->x = from[i]->x * .0625;
		(rt)[i]->y = from[i]->y * .0625;
		(rt)[i]->z = from[i]->z * .0625;
	}
	(rt)[0]->texX = (float) x2 / txw;
	(rt)[0]->texY = (float) y1 / txh;
	(rt)[1]->texX = (float) x1 / txw;
	(rt)[1]->texY = (float) y1 / txh;
	(rt)[2]->texX = (float) x1 / txw;
	(rt)[2]->texY = (float) y2 / txh;
	(rt)[3]->texX = (float) x2 / txw;
	(rt)[3]->texY = (float) y2 / txh;
}

void createModelCube(struct modr* modr, struct vertex_tex* vexs, float x, float y, float z, int width, int height, int depth, float scale, int mirror) {
	float x2 = x + (float) width;
	float y2 = y + (float) height;
	float z2 = z + (float) depth;
	x -= scale;
	y -= scale;
	z -= scale;
	x2 += scale;
	y2 += scale;
	z2 += scale;
	if (mirror) {
		float t = x2;
		x2 = x;
		x = t;
	}
	struct vertex_tex tt[8];
	virtVertex3f(&tt[0], x, y, z);
	virtTexCoord2f(&tt[0], 0., 0.);
	virtVertex3f(&tt[1], x2, y, z);
	virtTexCoord2f(&tt[1], 0., 8.);
	virtVertex3f(&tt[2], x2, y2, z);
	virtTexCoord2f(&tt[2], 8., 8.);
	virtVertex3f(&tt[3], x, y2, z);
	virtTexCoord2f(&tt[3], 8., 0.);
	virtVertex3f(&tt[4], x, y, z2);
	virtTexCoord2f(&tt[4], 0., 0.);
	virtVertex3f(&tt[5], x2, y, z2);
	virtTexCoord2f(&tt[5], 0., 8.);
	virtVertex3f(&tt[6], x2, y2, z2);
	virtTexCoord2f(&tt[6], 8., 8.);
	virtVertex3f(&tt[7], x, y2, z2);
	virtTexCoord2f(&tt[7], 8., 0.);
	//
	struct vertex_tex* tv[4];
	tv[0] = &tt[5];
	tv[1] = &tt[1];
	tv[2] = &tt[2];
	tv[3] = &tt[6];
	xferVerticiesQuad(&(vexs[0]), tv, modr->txx + depth + width, modr->txy + depth, modr->txx + depth + width + depth, modr->txy + depth + height, modr->txw, modr->txh, mirror);
	tv[0] = &tt[0];
	tv[1] = &tt[4];
	tv[2] = &tt[7];
	tv[3] = &tt[3];
	xferVerticiesQuad(&(vexs[4]), tv, modr->txx, modr->txy + depth, modr->txx + depth, modr->txy + depth + height, modr->txw, modr->txh, mirror);
	tv[0] = &tt[5];
	tv[1] = &tt[4];
	tv[2] = &tt[0];
	tv[3] = &tt[1];
	xferVerticiesQuad(&(vexs[8]), tv, modr->txx + depth, modr->txy, modr->txx + depth + width, modr->txy + depth, modr->txw, modr->txh, mirror);
	tv[0] = &tt[2];
	tv[1] = &tt[3];
	tv[2] = &tt[7];
	tv[3] = &tt[6];
	xferVerticiesQuad(&(vexs[12]), tv, modr->txx + depth + width, modr->txy + depth, modr->txx + depth + width + width, modr->txy, modr->txw, modr->txh, mirror);
	tv[0] = &tt[1];
	tv[1] = &tt[0];
	tv[2] = &tt[3];
	tv[3] = &tt[2];
	xferVerticiesQuad(&(vexs[16]), tv, modr->txx + depth, modr->txy + depth, modr->txx + depth + width, modr->txy + depth + height, modr->txw, modr->txh, mirror);
	tv[0] = &tt[4];
	tv[1] = &tt[5];
	tv[2] = &tt[6];
	tv[3] = &tt[7];
	xferVerticiesQuad(&(vexs[20]), tv, modr->txx + depth + width, modr->txy + depth, modr->txx + depth + width + depth + width, modr->txy + depth + height, modr->txw, modr->txh, mirror);
}

void drawModr(struct modr* modr) {
	glPushMatrix();
	if (modr->rpX != 0. || modr->rpY != 0. || modr->rpZ != 0.) glTranslatef(modr->rpX * .0625, modr->rpY * .0625, modr->rpZ * .0625);
	if (modr->rotZ != 0.) glRotatef(modr->rotZ * (180. / PI), 0., 0., 1.);
	if (modr->rotY != 0.) glRotatef(modr->rotY * (180. / PI), 0., 1., 0.);
	if (modr->rotX != 0.) glRotatef(modr->rotX * (180. / PI), 1., 0., 0.);
	drawQuads(modr->vao);
	for (int i = 0; i < modr->child_count; i++) {
		drawModr(modr->children[i]);
	}
	glPopMatrix();
}

void drawModel(struct model* model) {
	glBindTexture(GL_TEXTURE_2D, model->tex);
	glPushMatrix();
	glScalef(-1., -1., 1.);
	glTranslatef(0., -1.5078125, 0.);
	for (int i = 0; i < model->child_count; i++) {
		drawModr(model->children[i]);
	}
	glPopMatrix();
}

int loadTexturePNG(char* path, int id, int s) {
	FILE* fd = fopen(path, "rb");
	if (!fd) return -1;
	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png) {
		fclose(fd);
		return -1;
	}
	png_infop info = png_create_info_struct(png);
	if (!info) {
		fclose(fd);
		return -1;
	}
	png_init_io(png, fd);
	png_read_info(png, info);
	int width = png_get_image_width(png, info);
	int height = png_get_image_height(png, info);
	png_byte color_type = png_get_color_type(png, info);
	png_byte bit_depth = png_get_bit_depth(png, info);
	if (bit_depth == 16) png_set_strip_16(png);
	if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png);
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png);
	if (png_get_valid(png, info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png);
	if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE) png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(png);
	png_read_update_info(png, info);
	void* pngd = malloc(height * png_get_rowbytes(png, info));
	png_bytep* row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
	for (int y = 0; y < height; y++) {
		row_pointers[y] = (png_byte*) (pngd + (png_get_rowbytes(png, info) * y));
	}
	png_read_image(png, row_pointers);
	free(row_pointers);
	loadTextureData(id, width, height, pngd, s);
	free(pngd);
	fclose(fd);
	return 0;
}

int loadTexturesPNG(char* path, int wrap, int* w, int* h, int id, int s, char** map, int maps, int* smap) {
	void* tpngd = NULL;
	int rw = 0;
	int rh = 0;
	int mo = 0;
	for (int mi = 0; mi < maps;) {
		char* me = map[mi];
		char cx[strlen(path) + strlen(me) + 1];
		memcpy(cx, path, strlen(path));
		memcpy(cx + strlen(path), me, strlen(me) + 1);
		FILE* fd = fopen(cx, "rb");
		if (!fd) return -1;
		png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png) {
			fclose(fd);
			return -1;
		}
		png_infop info = png_create_info_struct(png);
		if (!info) {
			fclose(fd);
			return -1;
		}
		png_init_io(png, fd);
		png_read_info(png, info);
		int width = png_get_image_width(png, info);
		if (rw == 0) rw = width + (2 * TEXTURE_BUFFER);
		int height = png_get_image_height(png, info);
		if (rh == 0) rh = height + (2 * TEXTURE_BUFFER);
		if (tpngd == NULL) {
			tpngd = malloc((rh * 4 * rw) * maps);
		}
		png_byte color_type = png_get_color_type(png, info);
		png_byte bit_depth = png_get_bit_depth(png, info);
		if (bit_depth == 16) png_set_strip_16(png);
		if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png);
		if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png);
		if (png_get_valid(png, info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png);
		if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE) png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
		if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(png);
		png_read_update_info(png, info);
		smap[mi] = mo;
		png_byte** row_pointers = (png_byte**) malloc(sizeof(png_byte*) * height);
		int rx = mo % wrap;
		int ry = mo / wrap;
		int prx = rx;
		int pry = ry;
		mo++;
		int bry = 0;
		int ph = height;
		for (int y = TEXTURE_BUFFER; y < height + TEXTURE_BUFFER; y++) {
			if (y >= rh - TEXTURE_BUFFER) {
				height -= rh - (2 * TEXTURE_BUFFER);
				y = TEXTURE_BUFFER;
				rx++;
				if (rx >= wrap) {
					rx = 0;
					ry++;
				}
				mo++;
				//printf("%i vs %i\n", (rh * 4 * rw) * (maps + (mo - (mi - 1))), (rh * 4 * rw) * maps + (mo - (mi - 1)));
				*w = wrap * rw;
				*h = (((maps + mo - mi + wrap) / wrap) + 1) * rh;
				//printf("%i\n", *h * *w * 4);
				tpngd = realloc(tpngd, *h * *w * 4);
			}
			//printf("ri = %i size = %i len = %i\n", (ry * rw * 4 * rh * wrap) + (y * 4 * rw * wrap) + (rx * rw * 4), (rh * 4 * rw) * (maps + (mo - (mi - 1))), png_get_rowbytes(png, info));
			row_pointers[bry] = (png_byte*) ((ry * rw * 4 * rh * wrap) + (y * 4 * rw * wrap) + (rx * rw * 4)) + (4 * TEXTURE_BUFFER);
			bry++;
		}
		height = ph;
		for (int y = 0; y < bry; y++) {
			row_pointers[y] = (uint64_t) row_pointers[y] + (uint64_t) tpngd;
		}
		png_read_image(png, row_pointers);
		rx = prx;
		ry = pry;
		for (int y = 0; y < height + (2 * TEXTURE_BUFFER); y++) {
			if (y >= rh) {
				height -= rh;
				y = 0;
				rx++;
				if (rx >= wrap) {
					rx = 0;
					ry++;
				}
			}
			unsigned char* row = tpngd + ((ry * rw * 4 * rh * wrap) + (y * 4 * rw * wrap) + (rx * rw * 4));
			if (y < TEXTURE_BUFFER) {
				unsigned char* nrow = tpngd + ((ry * rw * 4 * rh * wrap) + (TEXTURE_BUFFER * 4 * rw * wrap) + (rx * rw * 4));
				memcpy(row + (4 * TEXTURE_BUFFER), nrow + (4 * TEXTURE_BUFFER), (rw - (2 * TEXTURE_BUFFER)) * 4);
				for (int i = 0; i < TEXTURE_BUFFER; i++) {
					memcpy(row + (i * 4), row + (4 * TEXTURE_BUFFER), 4);
					memcpy(row + (rw - 1 - i) * 4, row + (rw - 1 - TEXTURE_BUFFER) * 4, 4);
				}
			} else if (y >= rh - TEXTURE_BUFFER) {
				unsigned char* prow = tpngd + ((ry * rw * 4 * rh * wrap) + ((rh - 1 - TEXTURE_BUFFER) * 4 * rw * wrap) + (rx * rw * 4));
				memcpy(row + (4 * TEXTURE_BUFFER), prow + (4 * TEXTURE_BUFFER), (rw - (2 * TEXTURE_BUFFER)) * 4);
				for (int i = 0; i < TEXTURE_BUFFER; i++) {
					memcpy(row + (i * 4), row + (4 * TEXTURE_BUFFER), 4);
					memcpy(row + (rw - 1 - i) * 4, row + (rw - 1 - TEXTURE_BUFFER) * 4, 4);
				}
			} else {
				for (int i = 0; i < TEXTURE_BUFFER; i++) {
					memcpy(row + (i * 4), row + (4 * TEXTURE_BUFFER), 4);
					memcpy(row + (rw - 1 - i) * 4, row + (rw - 1 - TEXTURE_BUFFER) * 4, 4);
				}
			}
		}
		if (streq(me, "grass_top.png") || streq(me, "fern.png") || streq(me, "tallgrass.png") || startsWith(me, "double_plant_grass") || startsWith(me, "double_plant_fern") || startsWith(me, "leaves_")) { // TODO: implement dynamic textures better than this
			for (int y = 0; y < bry; y++) {
				uint32_t* pix = row_pointers[y];
				for (int x = 0; x < rw; x++) {
					//printf("%08X", pix[x]);
					int cc = (pix[x] & 0xFF);
					int r = 71 * ((float) cc / 255.);
					int g = 205 * ((float) cc / 255.);
					int b = 51 * ((float) cc / 255.);
					if (r > 255 || g > 255 || b > 255) {
						int total = r + g + b;
						int h = (r >= g && r >= b) ? r : ((g >= b) ? g : b);
						if (total < 765) {
							float m = (float) (765 - total) / (float) (3 * h - total);
							int g = 255 - m * (float) h;
							r = g + m * r;
							g = g + m * g;
							b = g + m * b;
						} else {
							r = 255;
							g = 255;
							b = 255;
						}
					}
					if (r < 0) r = 0;
					if (g < 0) g = 0;
					if (b < 0) b = 0;
					pix[x] = r | (g << 8) | (b << 16) | (pix[x] & 0xFF000000);
				}
				//printf("\n");
			}
		}
		free(row_pointers);
		png_destroy_read_struct(&png, &info, (png_infopp) 0);
		fclose(fd);
		mi++;
	}
	*w = wrap * rw;
	*h = ((mo / wrap) + 1) * rh;
	tpngd = realloc(tpngd, *h * *w * 4);
	/*FILE *fp = NULL;
	 png_structp png_ptr = NULL;
	 png_infop info_ptr = NULL;
	 png_bytep row = NULL;
	 fp = fopen("/dsk/test.png", "w+");
	 if (fp == NULL) {
	 free(tpngd);
	 return -1;
	 }
	 png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	 if (png_ptr == NULL) {
	 printf("e2\n");
	 }
	 info_ptr = png_create_info_struct(png_ptr);
	 if (info_ptr == NULL) {
	 printf("e3\n");
	 }
	 png_init_io(png_ptr, fp);
	 png_set_IHDR(png_ptr, info_ptr, *w, *h, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	 png_write_info(png_ptr, info_ptr);
	 for (int i = 0; i < *h; i++) {
	 row = tpngd + (*w * 4 * i);
	 png_write_row(png_ptr, row);
	 }
	 png_write_end(png_ptr, NULL);
	 fclose(fp);
	 png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	 png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
	 printf("wrote /dsk/test.png\n");*/
	loadTextureData(id, *w, *h, tpngd, s);
	free(tpngd);
	return 0;
}

void loadTextureData(int id, size_t width, size_t height, void* data, int s) {
	glBindTexture(GL_TEXTURE_2D, id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
//glGenerateMipmap (GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, s ? GL_NEAREST : GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
#ifdef GL_TEXTURE_MAX_ANISOTROPY_EXT
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0);
#endif
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}
