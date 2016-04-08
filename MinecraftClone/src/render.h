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

struct __attribute__((packed)) vertex {
		float x;
		float y;
		float z;
};

struct __attribute__((packed)) vertex_tex {
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
		int vib;
		size_t index_count;
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
#define TX_STEVE 15
#define TX_ITEMS 16
#define TX_IV_INVENTORY 17
#define TX_IV_CHEST 18
#define TX_IV_WORKBENCH 19
#define TX_IV_FURNACE 20
#define TX_IV_DISPENSER 21
#define TX_IV_ENCHANTINGTABLE 22
#define TX_IV_BREWINGSTAND 23
#define TX_IV_VILLAGER 24
#define TX_IV_BEACON 25
#define TX_IV_ANVIL 26
#define TX_IV_HOPPER 27
#define TX_IV_HORSE 28
#define TX_CREEPER 29
#define TX_SKELETON 30
#define TX_SPIDER 31
#define TX_WITHERSKELETON 32
#define TX_ZOMBIE 33
#define TX_SLIME 34
#define TX_GHAST 35
#define TX_ZPIGMAN 36
#define TX_ENDERMAN 37
#define TX_CAVESPIDER 38
#define TX_SILVERFISH 39
#define TX_BLAZE 40
#define TX_MAGMACUBE 41
#define TX_ENDERDRAGON 42
#define TX_WITHER 43
#define TX_BAT 44
#define TX_WITCH 45
#define TX_ENDERMITE 46
#define TX_GUARDIAN 47
#define TX_SHULKER 48
#define TX_PIG 49
#define TX_SHEEP 50
#define TX_COW 51
#define TX_CHICKEN 52
#define TX_SQUID 53
#define TX_WOLF 54
#define TX_MOOSHROOM 55
#define TX_SNOWMAN 56
#define TX_OCELOT 57
#define TX_IRONGOLEM 58
#define TX_HORSEBLACK 59
#define TX_RABBITBLACK 60
#define TX_VILLAGERBUTCHER 61
#define TX_GHASTSHOOTING 62
#define TX_ZOMBIEBUTCHER 63
#define TX_MINECART 64
#define TX_ENDERCRYSTAL 65
#define TX_ENDERCRYSTALBEAM 66
#define TX_ARROW 67
#define TX_ZOMBIEFARMER 68
#define TX_ZOMBIELIBRARIAN 69
#define TX_ZOMBIEPRIEST 70
#define TX_ZOMBIESMITH 71
#define TX_ZOMBIEVILLAGER 72
//#define TX_WITHERSKULL 73
//#define TX_SHULKERBULLET 74
#define TX_ENDERMANEYES 75
#define TX_WITHERARMOR 76
#define TX_WITHERINVULNERABLE 77
#define TX_SHULKERSPARK 78
#define TX_PIGSADDLE 79
#define TX_SHEEPFUR 80
#define TX_WOLFANGRY 81
#define TX_LEASHKNOT 82
#define TX_ARMORSTAND 83
#define TX_WOLFTAME 84
#define TX_SPECTRALARROW 85
#define TX_TIPPEDARROW 86
#define TX_CREEPERARMOR 87
#define TX_OCELOTBLACK 88
#define TX_OCELOTRED 89
#define TX_OCELOTSIAMESE 90
#define TX_ELDERGUARDIAN 91
#define TX_HORSEDONKEY 92
#define TX_HORSEBROWN 93
#define TX_HORSECHESTNUT 94
#define TX_HORSECREAMY 95
#define TX_HORSEDARKBROWN 96
#define TX_HORSEGRAY 97
#define TX_HORSESKELETON 98
#define TX_HORSEWHITE 99
#define TX_HORSEZOMBIE 100
#define TX_HORSEMULE 101
#define TX_HORSEDIAMONDARMOR 102
#define TX_HORSEGOLDARMOR 102
#define TX_HORSEIRONARMOR 103
#define TX_RABBITBROWN 104
#define TX_RABBITCAERBANNOG 105
#define TX_RABBITGOLD 106
#define TX_RABBITSALT 107
#define TX_RABBITTOAST 108
#define TX_RABBITWHITE 109
#define TX_RABBITWHITESPLOTCH 110
#define TX_VILLAGERFARMER 111
#define TX_VILLAGERLIBRARIAN 112
#define TX_VILLAGERPRIEST 113
#define TX_VILLAGERSMITH 114
#define TX_VILLAGER 115
#define TX_BOATACACIA 116
#define TX_BOATBIRCH 117
#define TX_BOATDARKOAK 118
#define TX_BOATJUNGLE 119
#define TX_BOATOAK 120
#define TX_BOATSPRUCE 121

void virtVertex3f(union uvertex* vert, float x, float y, float z);

void virtTexCoord2f(struct vertex_tex* vert, float x, float y);

void createVAO(struct vertex* verticies, size_t count, struct vao* vao, int textures, int overwrite, uint16_t restart);

void deleteVAO(struct vao* vao);

void createSubCube(float size, struct vertex_tex* vrt, float x, float y, float z, unsigned char faceMask, float tx1, float ty1, float tx2, float ty2);

void createMultSub(float xwid, float ywid, float zwid, struct vertex_tex* vrt, float x, float y, float z, unsigned char faceMask, float* tx1, float* ty1, float* tx2, float* ty2);

void createMultSubCube(float size, struct vertex_tex* vrt, float x, float y, float z, unsigned char faceMask, float* tx1, float* ty1, float* tx2, float* ty2);

void createTexCube(float size, struct vao* vao);

void drawSkeleton(struct vao* vao);

void drawTriangles(struct vao* vao);

void drawTriangleStrips4(struct vao* vao);

void drawQuads(struct vao* vao);

struct plane {
		double nx;
		double ny;
		double nz;
		double px;
		double py;
		double pz;
};

void drawChunk(struct chunk* chunk, struct plane* planes);

void drawWorld(struct world* world);

void drawChar(char c, int italic);

void drawString(char* str, int x, int y, uint32_t color);

size_t stringWidth(char* str);

void trimStringToWidth(char* str, size_t width);

void drawTexturedModalRect(int x, int y, int z, int textureX, int textureY, int width, int height);

void drawRect(int x, int y, int z, int width, int height, uint32_t color);

#endif /* RENDER_H_ */
