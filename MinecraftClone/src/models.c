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
		/*if (streq(me, "grass_top.png")) { // TODO: implement dynamic textures better than this
		 for (int y = 0; y < bry; y++) {
		 uint32_t* pix = row_pointers[y];
		 for (int x = 0; x < rw; x++) {
		 pix[x] &= 0x00FFFFFF;
		 pix[x] |= 0xFF000000;
		 pix[x] |= 0x000000FF;
		 pix[x] = (71) | (205 << 8) | (51 << 16) | (0);
		 }
		 }
		 }*/
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
//glGenerateMipmap (GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, s ? GL_NEAREST : GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
#ifdef GL_TEXTURE_MAX_ANISOTROPY_EXT
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0);
#endif
//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}
