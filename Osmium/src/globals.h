/*
 * gloabls.h
 *
 *  Created on: Mar 5, 2016
 *      Author: root
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <GLFW/glfw3.h>
#include "bmodel.h"

extern int width;
extern int height;
extern int swidth;
extern int sheight;
extern int mouseX;
extern int mouseY;
extern int mouseButton;
extern int csf;
extern int def_width;
extern int def_height;
extern int def_wrap;
extern int hasMouse;
extern GLFWwindow* window;
extern char** blockMap;
extern int* blockSizeMap;
extern int blockMapLength;
extern float hnear;
extern float hfar;
extern float wnear;
extern float wfar;
extern double eyeX;
extern double eyeY;
extern double eyeZ;
extern double lookX;
extern double lookY;
extern double lookZ;
extern float viewDistance;
extern int viewBobbing;
extern char* username;
extern char* uuid;
extern char* accessToken;
extern struct bnamespace** gbns;
extern size_t gbn_count;

#define PI 3.141592653589793

#ifdef __MINGW32__
#define INSTALLDIR ""
#else
#define INSTALLDIR ""
#endif

#endif /* GLOBALS_H_ */
