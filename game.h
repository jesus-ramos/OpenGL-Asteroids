#ifndef _GAME_H
#define _GAME_H

#include "ship.h"

#define TIMER_TICK 20

#define MAX_BGND_STARS 500

#define MAX_LIVES 3

extern struct ship ship;

void game_init();
void game_tick(int value);
void display();

#endif /* _GAME_H */
