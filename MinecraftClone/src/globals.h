/*
 * gloabls.h
 *
 *  Created on: Mar 5, 2016
 *      Author: root
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <GLFW/glfw3.h>

int width;
int height;
int swidth;
int sheight;
int mouseX;
int mouseY;
int mouseButton;
int csf;
int def_width;
int def_height;
int def_wrap;
int hasMouse;
GLFWwindow* window;
char** blockMap;
int* blockSizeMap;
int blockMapLength;
float hnear;
float hfar;
float wnear;
float wfar;
double eyeX;
double eyeY;
double eyeZ;
double lookX;
double lookY;
double lookZ;
float viewDistance;

#define PI 3.141592653589793

#ifdef __MINGW32__
#define INSTALLDIR "C:/oglt/"
#else
#define INSTALLDIR "/dsk/ogla/"
#endif

#endif /* GLOBALS_H_ */
