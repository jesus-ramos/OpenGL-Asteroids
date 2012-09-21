#ifndef _SHIP_H
#define _SHIP_H

#include "physics.h"
#include "list.h"

#define MOVING_FORWARD  1
#define MOVING_BACKWARD -1
#define TURNING_LEFT    -1
#define TURNING_RIGHT   1

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
void delete_bullet(struct ship *ship, struct bullet *bullet);
void clear_bullets(struct ship *ship);

#endif /* _SHIP_H */
