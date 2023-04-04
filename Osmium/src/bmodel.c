/*
 * bmodel.c
 *
 *  Created on: May 21, 2016
 *      Author: root
 */

#include "bmodel.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "json.h"
#include "xstring.h"
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

struct bmodel* readBmodel(char* path) {
	char* nplx = strrchr(path, '/');
	if (nplx == NULL) {
		errno = EINVAL;
		return NULL;
	}
	nplx++;
	nplx = strdup(nplx);
	{
		char* tx = strchr(nplx, '.');
		tx[0] = 0;
	}
	int bfd = open(path, O_RDONLY);
	if (bfd < 0) return NULL;
	char* buf = malloc(4097);
	size_t cr = 0;
	size_t cp = 4096;
	ssize_t r = 0;
	while ((r = read(bfd, buf + cr, cp - cr - 1)) > 0) {
		cr += r;
		if (cp - cr <= 2048) {
			cp += 4096;
			buf = realloc(buf, cp + 1);
		}
	}
	buf[cr] = 0;
	close(bfd);
	struct json_object json;
	if (parseJSON(&json, buf) < 0) return (struct bmodel *)-1;
	struct bmodel* bm = malloc(sizeof(struct bmodel));
	memset(bm, 0, sizeof(struct bmodel));
	bm->name = nplx;
	struct json_object* tmp = getJSONValue(&json, "parent");
	if (tmp != NULL && tmp->type == JSON_STRING) {
		bm->parent = tmp->data.string;
		tmp->data.string = NULL;
	}
	tmp = getJSONValue(&json, "ambientocclusion");
	if (tmp != NULL && tmp->type == JSON_FALSE) bm->ambientocc = 0;
	else bm->ambientocc = 1;
	tmp = getJSONValue(&json, "display");
	if (tmp != NULL && tmp->type == JSON_OBJECT) for (size_t i = 0; i < tmp->child_count; i++) {
		struct json_object* tmp2 = tmp->children[i];
		if (tmp2 == NULL || tmp2->type != JSON_OBJECT) continue;
		struct bdisplay* cd = NULL;
		if (streq_nocase(tmp2->name, "thirdperson_righthand")) cd = &bm->display[BD_TP_RIGHT];
		else if (streq_nocase(tmp2->name, "thirdperson_lefthand")) cd = &bm->display[BD_TP_LEFT];
		else if (streq_nocase(tmp2->name, "firstperson_righthand")) cd = &bm->display[BD_FP_RIGHT];
		else if (streq_nocase(tmp2->name, "firstperson_lefthand")) cd = &bm->display[BD_FP_LEFT];
		else if (streq_nocase(tmp2->name, "gui")) cd = &bm->display[BD_GUI];
		else if (streq_nocase(tmp2->name, "head")) cd = &bm->display[BD_HEAD];
		else if (streq_nocase(tmp2->name, "ground")) cd = &bm->display[BD_GROUND];
		else if (streq_nocase(tmp2->name, "fixed")) cd = &bm->display[BD_FIXED];
		else continue;
		for (size_t x = 0; x < tmp2->child_count; x++) {
			struct json_object* tmp3 = tmp2->children[x];
			if (tmp3 == NULL || tmp3->type != JSON_ARRAY || tmp3->child_count != 3) continue;
			float* rt = NULL;
			if (streq_nocase(tmp3->name, "rotation")) {
				rt = cd->rot;
				cd->defined[0] = 1;
			} else if (streq_nocase(tmp3->name, "translation")) {
				rt = cd->xl;
				cd->defined[1] = 1;
			} else if (streq_nocase(tmp3->name, "scale")) {
				rt = cd->scale;
				cd->defined[2] = 1;
			}
			rt[0] = tmp3->children[0]->data.number;
			rt[1] = tmp3->children[1]->data.number;
			rt[2] = tmp3->children[2]->data.number;
		}
	}
	tmp = getJSONValue(&json, "textures");
	if (tmp != NULL && tmp->type == JSON_OBJECT) {
		bm->textures = malloc(sizeof(struct btexture) * tmp->child_count);
		bm->texture_count = tmp->child_count;
		for (size_t i = 0; i < tmp->child_count; i++) {
			if (tmp->children[i] == NULL || tmp->children[i]->type != JSON_STRING) {
				memset(&bm->textures[i], 0, sizeof(struct btexture));
				continue;
			}
			bm->textures[i].name = tmp->children[i]->name;
			tmp->children[i]->name = NULL;
			bm->textures[i].path = tmp->children[i]->data.string;
			tmp->children[i]->data.string = NULL;
		}
	}
	tmp = getJSONValue(&json, "elements");
	if (tmp != NULL && tmp->type == JSON_ARRAY) {
		bm->elements = malloc(sizeof(struct belement) * tmp->child_count);
		bm->element_count = tmp->child_count;
		for (size_t i = 0; i < tmp->child_count; i++) {
			struct json_object* tmp2 = tmp->children[i];
			struct belement* be = &bm->elements[i];
			memset(be, 0, sizeof(struct belement));
			if (tmp2 == NULL || tmp2->type != JSON_OBJECT) continue;
			struct json_object* tmp3 = getJSONValue(tmp2, "from");
			if (tmp3 != NULL && tmp3->type == JSON_ARRAY && tmp3->child_count == 3) {
				be->from[0] = tmp3->children[0]->data.number;
				be->from[1] = tmp3->children[1]->data.number;
				be->from[2] = tmp3->children[2]->data.number;
			}
			tmp3 = getJSONValue(tmp2, "to");
			if (tmp3 != NULL && tmp3->type == JSON_ARRAY && tmp3->child_count == 3) {
				be->to[0] = tmp3->children[0]->data.number;
				be->to[1] = tmp3->children[1]->data.number;
				be->to[2] = tmp3->children[2]->data.number;
			}
			be->rescale = 0;
			be->angle = 0;
			be->axis = 'x';
			be->orig[0] = 8.;
			be->orig[1] = 8.;
			be->orig[2] = 8.;
			tmp3 = getJSONValue(tmp2, "rotation");
			if (tmp3 != NULL && tmp3->type == JSON_OBJECT) {
				struct json_object* tmp4 = getJSONValue(tmp2, "orig");
				if (tmp4 != NULL && tmp4->type == JSON_ARRAY && tmp4->child_count == 3) {
					be->orig[0] = tmp4->children[0]->data.number;
					be->orig[1] = tmp4->children[1]->data.number;
					be->orig[2] = tmp4->children[2]->data.number;
				}
				tmp4 = getJSONValue(tmp2, "axis");
				if (tmp4 != NULL && tmp4->type == JSON_STRING && strlen(tmp3->data.string) == 1) be->axis = tmp3->data.string[0];
				tmp4 = getJSONValue(tmp2, "angle");
				if (tmp4 != NULL && tmp4->type == JSON_NUMBER) {
					be->angle = tmp4->data.number;
				}
				tmp4 = getJSONValue(tmp2, "rescale");
				if (tmp4 != NULL && tmp4->type == JSON_TRUE) be->rescale = 1;
			}
			tmp3 = getJSONValue(tmp2, "rescale");
			if (tmp3 != NULL && tmp3->type == JSON_FALSE) be->shade = 0;
			else be->shade = 1;
			tmp3 = getJSONValue(tmp2, "faces");
			if (tmp3 != NULL && tmp3->type == JSON_OBJECT && tmp3->child_count < 6) {
				for (size_t x = 0; x < tmp3->child_count; x++) {
					struct json_object* tmp4 = tmp3->children[x];
					if (tmp4 == NULL || tmp4->type != JSON_OBJECT) continue;
					struct bface* bf = NULL;
					if (streq_nocase(tmp4->name, "down")) bf = &be->faces[CF_DOWN];
					else if (streq_nocase(tmp4->name, "up")) bf = &be->faces[CF_UP];
					else if (streq_nocase(tmp4->name, "north")) bf = &be->faces[CF_NORTH];
					else if (streq_nocase(tmp4->name, "south")) bf = &be->faces[CF_SOUTH];
					else if (streq_nocase(tmp4->name, "west")) bf = &be->faces[CF_WEST];
					else if (streq_nocase(tmp4->name, "east")) bf = &be->faces[CF_EAST];
					else continue;
					struct json_object* tmp5 = getJSONValue(tmp4, "uv");
					if (tmp5 != NULL && tmp5->type == JSON_ARRAY && tmp5->child_count == 4) {
						bf->uvd = 1;
						bf->uv1[0] = tmp5->children[0]->data.number;
						bf->uv1[1] = tmp5->children[1]->data.number;
						bf->uv2[0] = tmp5->children[2]->data.number;
						bf->uv2[1] = tmp5->children[3]->data.number;
					} else bf->uvd = 0;
					tmp5 = getJSONValue(tmp4, "texture");
					if (tmp5 != NULL && tmp5->type == JSON_STRING) {
						bf->texture = tmp5->data.string;
						tmp5->data.string = NULL;
					}
					tmp5 = getJSONValue(tmp4, "cullface");
					if (tmp5 != NULL && tmp5->type == JSON_STRING) {
						if (streq_nocase(tmp5->data.string, "down")) bf->cullface = CF_DOWN;
						else if (streq_nocase(tmp5->data.string, "up")) bf->cullface = CF_UP;
						else if (streq_nocase(tmp5->data.string, "north")) bf->cullface = CF_NORTH;
						else if (streq_nocase(tmp5->data.string, "south")) bf->cullface = CF_SOUTH;
						else if (streq_nocase(tmp5->data.string, "west")) bf->cullface = CF_WEST;
						else if (streq_nocase(tmp5->data.string, "east")) bf->cullface = CF_EAST;
						else bf->cullface = CF_DEFAULT;
					} else bf->cullface = CF_DEFAULT;
					tmp5 = getJSONValue(tmp4, "rotation");
					if (tmp5 != NULL && tmp5->type == JSON_NUMBER) {
						bf->rotation = tmp5->data.number;
					}
					tmp5 = getJSONValue(tmp4, "tintindex");
					if (tmp5 != NULL && tmp5->type == JSON_NUMBER) {
						bf->tintindex = tmp5->data.number;
					} else bf->tintindex = -1;
				}
			}
		}
	}
	freeJSON(&json);
	return bm;
}

int readAllBmodels(char* directory, struct bmodel*** bmodels, size_t* bmodel_count) {
	*bmodels = NULL;
	*bmodel_count = 0;
	DIR* dir = opendir(directory);
	if (dir == NULL) return -1;
	size_t dl = strlen(directory);
	struct dirent* de;
	while ((de = readdir(dir))) {
		if (streq(de->d_name, ".") || streq(de->d_name, "..")) continue;
		size_t snl = strlen(de->d_name);
		char tp[dl + snl + 2];
		memcpy(tp, directory, dl);
		int as = directory[dl - 1] != '/';
		if (as) tp[dl] = '/';
		memcpy(tp + dl + as, de->d_name, snl);
		tp[dl + as + snl] = 0;
		if (*bmodels == NULL) *bmodels = malloc(sizeof(struct bmodel*));
		else *bmodels = realloc(*bmodels, sizeof(struct bmodel*) * (1 + (*bmodel_count)));
		(*bmodels)[(*bmodel_count)++] = readBmodel(tp);
	}
	return 0;
}

void resolveBmodels(struct bnamespace** bns, size_t bns_count) {
	for (size_t u = 0; u < bns_count; u++) {
		struct bnamespace* bn = bns[u];
		for (size_t i = 0; i < bn->bmodel_count; i++) {
			struct bmodel* bm = bn->bmodels[i];
			if (bm == NULL) continue;
			char* bmpsp = NULL;
			char* cp = bm->parent;
			while (cp != NULL && (bmpsp = strchr(cp, '/'))) {
				bmpsp[0] = 0;
				bmpsp++;
				int f = 0;
				for (size_t o = 0; o < bns_count; o++) {
					if (streq_nocase(bn->name, cp)) {
						for (size_t p = 0; p < bns[o]->bmodel_count; p++) {
							if (streq_nocase(bn->bmodels[p]->name, bmpsp)) {
								f = 1;
								cp = bn->bmodels[p]->parent;
								if (bm->elements == NULL) {
									bm->element_count = bn->bmodels[p]->element_count;
									bm->elements = malloc(bm->element_count * sizeof(struct belement));
									memcpy(bm->elements, bn->bmodels[p]->elements, bm->element_count * sizeof(struct belement));
								} else {
									bm->elements = realloc(bm->elements, sizeof(struct belement) * (bn->bmodels[p]->element_count + bm->element_count));
									memcpy(bm->elements + bm->element_count, bn->bmodels[p]->elements, bn->bmodels[p]->element_count * sizeof(struct belement));
								}
								if (bm->textures == NULL) {
									bm->texture_count = bn->bmodels[p]->texture_count;
									bm->textures = malloc(bm->texture_count * sizeof(struct btexture));
									memcpy(bm->textures, bn->bmodels[p]->textures, bm->texture_count * sizeof(struct btexture));
								} else {
									bm->textures = realloc(bm->textures, sizeof(struct btexture) * (bn->bmodels[p]->texture_count + bm->texture_count));
									memcpy(bm->textures + bm->texture_count, bn->bmodels[p]->textures, bn->bmodels[p]->texture_count * sizeof(struct btexture));
								}
								break;
							}
						}
						break;
					}
				}
				bmpsp--;
				bmpsp[0] = '/';
				if (!f) {
					printf("Warning: model <%s> has an invalid parent!\n", bm->name);
					break;
				}
			}
			for (size_t p = 0; p < bm->texture_count; p++) {
				struct btexture* btp = &bm->textures[p];
				if (streq(btp->name, "particle")) continue;
				while (btp->path != NULL && strlen(btp->path) >= 1 && btp->path[0] == '#') {
					for (size_t o = 0; o < bm->texture_count; o++) {
						struct btexture* bto = &bm->textures[o];
						if (streq_nocase(bto->name, btp->path + 1)) {
							btp->path = bto->path;
							goto cntdd;
						}
					}
					break;
					cntdd: ;
				}
			}
		}
	}
}

struct blockstate* readBlockstate(char* path) {
	char* nplx = strrchr(path, '/');
	if (nplx == NULL) {
		errno = EINVAL;
		return NULL;
	}
	nplx++;
	nplx = strdup(nplx);
	{
		char* tx = strchr(nplx, '.');
		tx[0] = 0;
	}
	int bfd = open(path, O_RDONLY);
	if (bfd < 0) return NULL;
	char* buf = malloc(4097);
	size_t cr = 0;
	size_t cp = 4096;
	ssize_t r = 0;
	while ((r = read(bfd, buf + cr, cp - cr - 1)) > 0) {
		cr += r;
		if (cp - cr <= 2048) {
			cp += 4096;
			buf = realloc(buf, cp + 1);
		}
	}
	buf[cr] = 0;
	close(bfd);
	struct json_object json;
	if (parseJSON(&json, buf) < 0) return (struct bmodel *)-1;
	struct blockstate* bs = malloc(sizeof(struct blockstate));
	memset(bs, 0, sizeof(struct blockstate));
	bs->name = nplx;
	struct json_object* mpv = getJSONValue(&json, "variants");
	if (mpv == NULL || mpv->type != JSON_OBJECT) {
		mpv = getJSONValue(&json, "multipart");
		if (mpv == NULL || mpv->type != JSON_OBJECT) goto mpvn;
		bs->multipart = 1;
		bs->bsu.multipart.case_count = mpv->child_count;
		bs->bsu.multipart.cases = malloc(sizeof(struct bsmpcase) * mpv->child_count);
		memset(&bs->bsu.multipart.cases, 0, sizeof(struct bsmpcase) * mpv->child_count);
	} else {
		bs->multipart = 0;
		bs->bsu.variants.variant_count = mpv->child_count;
		bs->bsu.variants.variants = malloc(sizeof(struct bsvariant) * mpv->child_count);
		for (size_t i = 0; i < mpv->child_count; i++) {
			struct json_object* v = mpv->children[i];
			if (v == NULL) {
				memset(&bs->bsu.variants.variants[i], 0, sizeof(struct bsvariant));
				continue;
			}
			bs->bsu.variants.variants[i].name = v->name;
			struct json_object* mc = v;
			if (v->child_count == 1 && v->children[0] != NULL && v->children[0]->type == JSON_ARRAY) {
				mc = v->children[0];
			}
			bs->bsu.variants.variants[i].bsmodel_count = mc->child_count;
			bs->bsu.variants.variants[i].bsmodels = malloc(mc->child_count * sizeof(struct bsmodel));
			for (size_t o = 0; o < mc->child_count; o++) {
				memset(&bs->bsu.variants.variants[i].bsmodels[o], 0, sizeof(struct bsmodel));
				bs->bsu.variants.variants[i].bsmodels[o].weight = 1.;
				struct json_object* mcs = mc->children[o];
				if (mcs == NULL || mcs->type != JSON_OBJECT) continue;
				struct json_object* mcsx = getJSONValue(mcs, "model");
				if (mcsx != NULL && mcsx->type == JSON_STRING) {
					bs->bsu.variants.variants[i].bsmodels[o].model = mcsx->data.string;
					mcsx->data.string = NULL;
				}
				mcsx = getJSONValue(mcs, "x");
				if (mcsx != NULL && mcsx->type == JSON_NUMBER) bs->bsu.variants.variants[i].bsmodels[o].x = mcsx->data.number;
				mcsx = getJSONValue(mcs, "y");
				if (mcsx != NULL && mcsx->type == JSON_NUMBER) bs->bsu.variants.variants[i].bsmodels[o].y = mcsx->data.number;
				mcsx = getJSONValue(mcs, "weight");
				if (mcsx != NULL && mcsx->type == JSON_NUMBER) bs->bsu.variants.variants[i].bsmodels[o].weight = mcsx->data.number;
				mcsx = getJSONValue(mcs, "uvlock");
				if (mcsx != NULL && mcsx->type == JSON_TRUE) bs->bsu.variants.variants[i].bsmodels[o].uvlock = 1;
			}
		}
	}
	mpvn: ;
	freeJSON(&json);
	return bs;
}

int readAllBlockstates(char* directory, struct blockstate*** bss, size_t* bs_count) {

}
