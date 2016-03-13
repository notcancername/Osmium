#include "gui.h"
#include "globals.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef __MINGW32__
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <pthread.h>
#include <time.h>
#include <png.h>
#include <math.h>
#include "entity.h"
#include "world.h"
#include <errno.h>
#include "render.h"
#include "models.h"
#include <GL/glext.h>
#ifdef __MINGW32__
# include <winsock2.h>
#else
# include <sys/socket.h>
#endif
#include "network.h"
#include "ingame.h"
#include "block.h"

#define HEIGHT 0.4

int fr = 30;
int rr = 0;
int b1d = 0;
float chx = 0.;
float chy = 0.;

int lmx = -1;
int lmy = -1;

void tick() {
	gui_tick();
	ingame_tick();
}

void keyboardCallback(unsigned char key, int x, int y) {
	gui_keydown(key);
}

void keyboardSpecCallback(unsigned char key, int x, int y) {
	gui_speckeydown(key);
}

void keyboardUpCallback(unsigned char key, int x, int y) {

}

struct timespec ts;
double lt;
double lf;
int frames;

void displayCallback() {
	frames++;
	width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);
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
	float partialTick = (ms2 - lt) / 50.;
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
	glutSwapBuffers();
	glutPostRedisplay();
	mouseButton = -1;
	//clock_gettime(CLOCK_MONOTONIC, &ts2);
	//printf("render-time: %f\n", ((double) ts2.tv_sec * 1000. + (double) ts2.tv_nsec / 1000000.) - ms2);
}

int moc = 0;

void mouseMotionCallback(int x, int y) {
	if (gs.player != NULL && spawnedIn) {
		if (!moc) {
			moc = 1;
			claimMouse();
		}
		if (lmx >= 0) {
			int dx = lmx - x;
			int dy = lmy - y;
			gs.player->pitch -= dy * 0.1;
			if (gs.player->pitch > 89.9) gs.player->pitch = 89.9;
			if (gs.player->pitch < -89.9) gs.player->pitch = -89.9;
			gs.player->yaw -= dx * 0.1;
			if (dx * dx + dy * dy > 0.) {
				glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
			}
		}
		lmx = glutGet(GLUT_WINDOW_WIDTH) / 2;
		lmy = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	} else if (moc) {
		moc = 0;
		unclaimMouse();
	}
	mouseX = x / (csf == 0 ? 1 : csf);
	mouseY = y / (csf == 0 ? 1 : csf);
}

void mouseCallback(int button, int state, int x, int y) {
	if (button == 3 || button == 4) {
		if (state == GLUT_UP) return;
		//if (button == 3) {
		//	heldItem++;
		//	if (heldItem == 9) heldItem = 0;
		//} else {
		//	heldItem--;
		//	if (heldItem == -1) heldItem = 8;
		//}
	}
	if (state == GLUT_DOWN) mouseButton = button;
}

int main(int argc, char *argv[]) {
#ifdef __MINGW32__
	WORD versionWanted = MAKEWORD(1, 1);
	WSADATA wsaData;
	WSAStartup(versionWanted, &wsaData);
#endif
	width = 800;
	height = 600;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Minecraft 1.9 (C Version)");
#ifdef __MINGW32__
	glewInit();
#endif
	glutKeyboardFunc(keyboardCallback);
	glutKeyboardUpFunc(keyboardUpCallback);
	glutSpecialFunc(keyboardSpecCallback);
	glutDisplayFunc(displayCallback);
	glutMotionFunc(mouseMotionCallback);
	glutMouseFunc(mouseCallback);
	glutPassiveMotionFunc(mouseMotionCallback);
	glEnable (GL_MULTISAMPLE);
	glEnable (GL_MULTISAMPLE_ARB);
	glEnable (GL_DEPTH_TEST);
	printf("Loading... [FROM=%s]\n", INSTALLDIR);
	loadTexturePNG(INSTALLDIR "floor.png", TX_FLOOR, 0);
	loadTexturePNG(INSTALLDIR "crosshair.png", TX_CROSSHAIR, 0);
	loadGUI();
	loadIngame();
	loadBlocks();
	struct vertex_tex floorv[4];
	virtTexCoord2f(&floorv[0], 0., 0.);
	virtVertex3f(&floorv[0], -1000., 0., -1000.);
	virtTexCoord2f(&floorv[1], 6000.0, 0.0);
	virtVertex3f(&floorv[1], 1000, 0, -1000);
	virtTexCoord2f(&floorv[2], 6000.0, 6000.0);
	virtVertex3f(&floorv[2], 1000, 0, 1000);
	virtTexCoord2f(&floorv[3], 0.0, 6000.0);
	virtVertex3f(&floorv[3], -1000, 0, 1000);
	createVAO(floorv, 4, &mod_floor, 1, 0);
	createTexCube(0.5, &mod_cube);
	def_wrap = 32;
	loadTexturesPNG(INSTALLDIR "assets/minecraft/textures/blocks/", def_wrap, &def_width, &def_height, TX_DEFAULT, 1);
	//world = newWorld();
	//setBlockWorld(world, BLK_WOOD, 0, 0, 0);
	//setBlockWorld(world, BLK_WOOD, 2, 0, 0);
	//setBlockWorld(world, BLK_WOOD, 0, 0, 2);
	//setBlockWorld(world, BLK_WOOD, 2, 0, 2);
	//setBlockWorld(world, BLK_WOOD, -1, 0, 0);
	//setBlockWorld(world, BLK_WOOD, 0, 0, -1);
	//setBlockWorld(world, BLK_WOOD, -1, 0, -1);
	//ourPlayer = newEntity(0, 0., HEIGHT, 3., ENTITY_OURPLAYER, 0., 0.);
	//spawnEntity(world, ourPlayer);
	printf("Loaded.\n");
	clock_gettime(CLOCK_MONOTONIC, &ts);
	lt = (double) ts.tv_sec * 1000. + (double) ts.tv_nsec / 1000000.;
	lf = lt;
	glutMainLoop();
}
