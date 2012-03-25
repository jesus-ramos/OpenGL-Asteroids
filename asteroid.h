#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "list.h"
#include "physics.h"

#define ASTEROID_ROTATE_SPEED 10

struct asteroid
{
    struct position_info pos;
    struct list_head list;
    float angular_speed;
};

void draw_asteroids(struct asteroid *asteroids);
void init_asteroid(struct asteroid *asteroid);

#endif /* _ASTEROID_H */
