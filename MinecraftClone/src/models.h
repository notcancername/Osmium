/*
 * models.h
 *
 *  Created on: Feb 23, 2016
 *      Author: root
 */

#ifndef MODELS_H_
#define MODELS_H_

#include "render.h"
#include <stdlib.h>
#include <stdio.h>

#define TEXTURE_BUFFER 1

int loadTexturePNG(char* path, int id, int s);

int loadTexturesPNG(char* path, int wrap, int* w, int* h, int id, int s, char** map, int maps, int* smap);

void loadTextureData(int id, size_t width, size_t height, void* data, int s);

#endif /* MODELS_H_ */
