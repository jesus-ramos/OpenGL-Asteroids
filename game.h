#ifndef _GAME_H
#define _GAME_H

#include "ship.h"

extern struct ship ship;

void game_init();
void game_tick(int value);
void display();
void game_reset();

void handle_keyboard(unsigned char key, int x, int y);
void handle_keyboard_up(unsigned char key, int x, int y);
void handle_keyboard_special(int key, int x, int y);
void handle_keyboard_special_up(int key, int x, int y);

#endif /* _GAME_H */
