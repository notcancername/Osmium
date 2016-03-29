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

#define TEXTURE_BUFFER 4

void loadBaseModels();

#define BIPED_HEAD children[0]
#define BIPED_HEADWEAR children[1]
#define BIPED_BODY children[2]
#define BIPED_RIGHTARM children[3]
#define BIPED_LEFTARM children[4]
#define BIPED_RIGHTLEG children[5]
#define BIPED_LEFTLEG children[6]

struct model mod_biped;

struct modr {
		int txx;
		int txy;
		int txw;
		int txh;
		float rotX;
		float defRotX;
		float rotY;
		float defRotY;
		float rotZ;
		float defRotZ;
		float rpX;
		float defrpX;
		float rpY;
		float defrpY;
		float rpZ;
		float defrpZ;
		struct vao* vao;
		struct modr** children;
		size_t child_count;
};

struct model {
		int tex;
		float txh;
		float txw;
		struct modr** children;
		size_t child_count;
};

void newModel(struct model* model, int tx, int width, int height);

void newModr(struct modr* modr, int txx, int txy, int txw, int txh, float rpX, float rpY, float rpZ);

void setModrAngles(struct modr* modr, float rotX, float rotY, float rotZ);

void setModrDefAngles(struct modr* modr, float rotX, float rotY, float rotZ);

void setModrAnglePoint(struct modr* modr, float rpX, float rpY, float rpZ);

void setModrDefAnglePoint(struct modr* modr, float rpX, float rpY, float rpZ);

void resetModr(struct modr* modr);

void resetModel(struct model* model);

void addModrChild(struct modr* modr, struct modr* child);

void addModelChild(struct model* model, struct modr* child);

void createModelCube(struct modr* modr, struct vertex_tex* vexs, float x, float y, float z, int width, int height, int depth, float scale, int mirror);

void drawModr(struct modr* modr);

void drawModel(struct model* model);

int loadTexturePNG(char* path, int id, int s);

int loadTexturesPNG(char* path, int wrap, int* w, int* h, int id, int s, char** map, int maps, int* smap);

void loadTextureData(int id, size_t width, size_t height, void* data, int s);

#endif /* MODELS_H_ */
