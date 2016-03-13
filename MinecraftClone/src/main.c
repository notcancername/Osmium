#include <stdio.h>
#include <stdlib.h>
#ifdef __MINGW32__
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#include "gui.h"
#include "globals.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <pthread.h>
#include <time.h>
#include <png.h>
#include <math.h>
#include "entity.h"
#include "world.h"
#include <errno.h>
#include "render.h"
#include "models.h"
#ifdef __MINGW32__
# include <winsock2.h>
#else
# include <sys/socket.h>
#endif
#include "network.h"
#include "ingame.h"
#include "block.h"

int fr = 30;
int rr = 0;
int b1d = 0;
float chx = 0.;
float chy = 0.;

void tick() {
	gui_tick();
	ingame_tick();
}

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	gui_keyboardCallback(key, scancode, action, mods);
}

void textCallback(GLFWwindow* window, unsigned int codepoint) {
	gui_textCallback(codepoint);
}

struct timespec ts;
double lt;
double lf;
int frames;

void displayCallback() {
	frames++;
	glfwGetFramebufferSize(window, &width, &height);
	int v5 = 1000;
	int sf = 1;
	swidth = width;
	sheight = height;
	while (sf < v5 && swidth / (sf + 1) >= 320 && sheight / (sf + 1) >= 240) {
		sf++;
	}
	swidth = (int) ceil(swidth / sf);
	sheight = (int) ceil(sheight / sf);
	csf = sf;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	double ms2 = (double) ts.tv_sec * 1000. + (double) ts.tv_nsec / 1000000.;
	while (ms2 > lt + 50.) {
		lt += 50.;
		tick();
	}
	if (ms2 > lf + 1000.) {
		double t = ms2 - lf;
		lf = ms2;
		printf("FPS: %f\n", (float) frames / (t / 1000.));
		frames = 0;
	}

	//struct timespec ts2;
	//clock_gettime(CLOCK_MONOTONIC, &ts2);
	//printf("tick-time: %f\n", ((double) ts2.tv_sec * 1000. + (double) ts2.tv_nsec / 1000000.) - ms2);
	float partialTick = 1. - ((ms2 - lt) / 50.);
	//ppitch = ourPlayer->pitch * (1. - partialTick) + ourPlayer->lpitch * partialTick;
	//pyaw = ourPlayer->yaw * (1. - partialTick) + ourPlayer->lyaw * partialTick;
	//px = ourPlayer->x * (1. - partialTick) + ourPlayer->lx * partialTick;
	//py = ourPlayer->y * (1. - partialTick) + ourPlayer->ly * partialTick;
	//pz = ourPlayer->z * (1. - partialTick) + ourPlayer->lz * partialTick;
	glEnable (GL_TEXTURE_2D);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glViewport(0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0., swidth, sheight, 0., 1000., 3000.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0., 0., -2000.);
	//glMatrixMode (GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(-1., 1., -1., 1., 1., 20.);
	//gluPerspective((sprinting && moveForward > 0) ? 105 : 95., (double) width / (double) height, 0.01, 10.);
	//glMatrixMode (GL_MODELVIEW);
	//glLoadIdentity();
	//float v3 = cos(-pyaw * 0.017453292 - PI);
	//float v4 = sin(-pyaw * 0.017453292 - PI);
	//float v5 = -cos(-ppitch * 0.017453292);
	//float ly = sin(-ppitch * 0.017453292) + py;
	//float lx = px + v4 * v5;
	//float lz = pz + v3 * v5;
	//gluLookAt(px, py, pz, lx, ly, lz, 0., 1., 0.);
	//drawScreen(partialTick);
	//glMatrixMode (GL_PROJECTION);
	//glLoadIdentity();
	//double wp = (double) width / 600.;
	//double hp = (double) height / 600.;
	//glOrtho(-1. * wp, 1. * wp, -1. * hp, 1. * hp, -20., 20.);
	//glMatrixMode (GL_MODELVIEW);
	//glLoadIdentity();
	//glDisable (GL_DEPTH_TEST);
	drawGUI(partialTick);
	//
	size_t error = glGetError();
	if (error) {
		char* es;
		if (error == GL_INVALID_ENUM) {
			es = "GL_INVALID_ENUM";
		} else if (error == GL_INVALID_VALUE) {
			es = "GL_INVALID_VALUE";
		} else if (error == GL_INVALID_OPERATION) {
			es = "GL_INVALID_OPERATION";
#ifdef GL_INVALID_FRAMEBUFFER_OPERATION
		} else if (error == GL_INVALID_FRAMEBUFFER_OPERATION) {
			es = "GL_INVALID_FRAMEBUFFER_OPERATION";
#endif
		} else if (error == GL_STACK_OVERFLOW) {
			es = "GL_STACK_OVERFLOW";
		} else if (error == GL_STACK_UNDERFLOW) {
			es = "GL_STACK_UNDERFLOW";
		} else if (error == GL_OUT_OF_MEMORY) {
			es = "GL_OUT_OF_MEMORY";
		} else es = "UNKNOWN";
		printf("GLError: %s\n", es);
	}
	glFlush();
	mouseButton = -1;
	//clock_gettime(CLOCK_MONOTONIC, &ts2);
	//printf("render-time: %f\n", ((double) ts2.tv_sec * 1000. + (double) ts2.tv_nsec / 1000000.) - ms2);
}

void mouseMotionCallback(GLFWwindow* window, double x, double y) {
	gui_mouseMotionCallback(x, y);
	mouseX = x / (csf == 0 ? 1 : csf);
	mouseY = y / (csf == 0 ? 1 : csf);
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == 3 || button == 4) {
		//if (state == GLUT_UP) return;
		//if (button == 3) {
		//	heldItem++;
		//	if (heldItem == 9) heldItem = 0;
		//} else {
		//	heldItem--;
		//	if (heldItem == -1) heldItem = 8;
		//}
	}
	if (action == GLFW_PRESS) mouseButton = button;
}

void error_callback(int error, const char* description) {
	printf("GLFW error: %s\n", description);
}

void cursorEnterCallback(GLFWwindow* window, int entered) {
	hasMouse = entered;
}

int main(int argc, char *argv[]) {
#ifdef __MINGW32__
	WORD versionWanted = MAKEWORD(1, 1);
	WSADATA wsaData;
	WSAStartup(versionWanted, &wsaData);
#endif
	printf("Loading... [FROM=%s]\n", INSTALLDIR);
	width = 800;
	height = 600;
	if (!glfwInit()) return -1;
	glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
	glfwSetErrorCallback(error_callback);
	window = glfwCreateWindow(800, 600, "Minecraft 1.9 (C Version)", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent (window);
#ifdef __MINGW32__
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(err != GLEW_OK) {
		printf("GLEW Init error: %s\n", glewGetErrorString(err));
		glfwTerminate();
		return -1;
	}
	if(!glewIsSupported("GL_VERSION_2_1") || !glewIsSupported("GL_ARB_vertex_program")) {
		printf("OpenGL version 2.1+ or GL_ARB_vertex_program not satisfied.\n");
		glfwTerminate();
		return -1;
	}
#endif
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	glEnable (GL_MULTISAMPLE);
	glEnable (GL_MULTISAMPLE_ARB);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_TEXTURE_2D);
	loadGUI();
	loadIngame();
	loadBlocks();
	def_wrap = 32;
	loadTexturesPNG(INSTALLDIR "assets/minecraft/textures/blocks/", def_wrap, &def_width, &def_height, TX_DEFAULT, 1);
	clock_gettime(CLOCK_MONOTONIC, &ts);
	lt = (double) ts.tv_sec * 1000. + (double) ts.tv_nsec / 1000000.;
	lf = lt;
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetCursorEnterCallback(window, cursorEnterCallback);
	glfwSetCharCallback(window, textCallback);
	glfwSetCursorPosCallback(window, mouseMotionCallback);
	glfwSetMouseButtonCallback(window, mouseCallback);
	printf("Loaded.\n");
	while (!glfwWindowShouldClose(window)) {
		displayCallback();
		glfwSwapBuffers(window);
		glfwSwapInterval(1);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
//glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);

//glutKeyboardFunc(keyboardCallback);
//glutKeyboardUpFunc(keyboardUpCallback);
//glutSpecialFunc(keyboardSpecCallback);
//glutDisplayFunc(displayCallback);
//glutMotionFunc(mouseMotionCallback);
//glutMouseFunc(mouseCallback);
//glutPassiveMotionFunc(mouseMotionCallback);
//glutSetKeyRepeat (GLUT_KEY_REPEAT_OFF);
}
