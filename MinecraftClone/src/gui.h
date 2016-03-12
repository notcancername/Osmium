/*
 * gui.h
 *
 *  Created on: Mar 5, 2016
 *      Author: root
 */

#ifndef GUI_H_
#define GUI_H_

void drawGUI(float partialTick);

void gui_tick();

void loadGUI();

void claimMouse();

void unclaimMouse();

void gui_keydown(char key);

void gui_speckeydown(int key);

#endif /* GUI_H_ */
