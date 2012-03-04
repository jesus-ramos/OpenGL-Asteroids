#ifndef SHIP_H
#define SHIP_H

#include "physics.h"
#include "list.h"

#define MAX_BULLET_COUNT 5
#define MAX_SPEED 5 /* world units / sec */

#define TURNING_LEFT -1
#define NO_TURNING 0
#define TURNING_RIGHT 1

struct bullet
{
    struct position_info pos;
    struct list_head list;
};

struct ship
{
    struct position_info pos;
    struct bullet *bullet_list;
    int bullet_count;
    int turning;
    int accelerating;
};

void draw_ship(struct ship *ship);

void init_ship(struct ship *ship);
void fire(struct ship *ship);

#endif /* SHIP_H */
