#ifndef _GAME_H
#define _GAME_H

#include "ship.h"

extern struct ship ship;

void game_init();
void game_tick(int value);
void display();

#endif /* _GAME_H */
