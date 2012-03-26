#ifndef _SHIP_H
#define _SHIP_H

#include "physics.h"
#include "list.h"

#define MAX_BULLET_COUNT (1UL << 30)
#define BULLET_MOVE_DIST 10
#define BULLET_FIRE_WAIT 3
#define BULLET_LIFETIME 100

#define BULLET_SIZE 1.5

#define SHIP_MOVE_DIST 6

#define SHIP_HEIGHT 15
#define SHIP_WIDTH 10

#define SHIP_ROTATE_SPEED 10

#define TURNING_LEFT -1
#define TURNING_RIGHT 1

#define MOVING_FORWARD 1
#define MOVING_BACKWARD -1

struct bullet
{
    struct position_info pos;
    struct list_head list;
    int life;
};

struct ship
{
    struct position_info pos;
    struct bullet bullet_list;
    int bullet_count;
    int fire_wait;
};

void draw_ship(struct ship *ship);
void init_ship(struct ship *ship, float x, float y);
void fire(struct ship *ship);
void move_ship(struct ship *ship, int direction);
void rotate_ship(struct ship *ship, int turn_val);
void move_bullets(struct ship *ship);

#endif /* _SHIP_H */
