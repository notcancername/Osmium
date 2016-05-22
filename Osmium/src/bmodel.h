/*
 * bmodel.h
 *
 *  Created on: May 21, 2016
 *      Author: root
 */

#ifndef BMODEL_H_
#define BMODEL_H_

#include <stdint.h>
#include <stdlib.h>

#define BD_TP_RIGHT 0
#define BD_TP_LEFT 1
#define BD_FP_RIGHT 2
#define BD_FP_LEFT 3
#define BD_GUI 4
#define BD_HEAD 5
#define BD_GROUND 6
#define BD_FIXED 7

#define CF_DOWN 0
#define CF_UP 1
#define CF_NORTH 2
#define CF_SOUTH 3
#define CF_WEST 4
#define CF_EAST 5
#define CF_DEFAULT 6;

struct bdisplay {
		float rot[3];
		float xl[3];
		float scale[3];
		uint8_t defined[3];
};

struct btexture {
		char* name;
		char* path;
};

struct bface {
		float uv1[2];
		float uv2[2];
		uint8_t uvd;
		char* texture;
		uint8_t cullface;
		uint8_t rotation;
		int8_t tintindex;
};

struct belement {
		float from[3];
		float to[3];
		float orig[3];
		char axis;
		uint8_t rescale;
		float angle;
		uint8_t shade;
		struct bface faces[6];
};

struct bmodel {
		char* name;
		char* parent;
		uint8_t ambientocc;
		struct bdisplay display[8];
		struct btexture* textures;
		size_t texture_count;
		struct belement* elements;
		size_t element_count;
};

struct bnamespace {
		char* name;
		struct bmodel** bmodels;
		size_t bmodel_count;
};

struct bsmodel {
		char* model;
		float x;
		float y;
		uint8_t uvlock;
		float weight;
};

struct bsvariant {
		char* name;
		struct bsmodel* bsmodels;
		size_t bsmodel_count;
};

struct bsvariants {
		struct bsvariant* variants;
		size_t variant_count;
};

struct bsmpclause {
		char* name;
		char** values;
		size_t value_count;
};

struct bsmpclauses {
		struct bsmpclause* clauses;
		size_t cause_count;
};

struct bsmpwhen {
		uint8_t or;
		struct bsmpclauses** pclauses;
		size_t pclause_count;
};

struct bsmpcase {
		struct bsmpwhen** whens;
		size_t when_count;
		struct bsvariants** applies;
		size_t apply_count;
};

struct bsmultipart {
		struct bsmpcase* cases;
		size_t case_count;
};

union blockstateu {
		struct bsvariants variants;
		struct bsmultipart multipart;
};

struct blockstate {
		uint8_t multipart;
		union blockstateu bsu;
		char* name;
};

struct bmodel* readBmodel(char* path);

int readAllBmodels(char* directory, struct bmodel*** bmodels, size_t* bmodel_count);

void resolveBmodels(struct bnamespace** bns, size_t bns_count);

struct blockstate* readBlockstate(char* path);

int readAllBlockstates(char* directory, struct blockstate*** bss, size_t* bs_count);

#endif /* BMODEL_H_ */
