#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "list.h"
#include "physics.h"

struct asteroid
{
    struct position_info pos;
    struct list_head list;
    float angular_speed;
    float radius;
};

void draw_asteroids(struct asteroid *asteroids);
void init_asteroid(struct asteroid *asteroid, float x, float y);
int check_asteroid_collision(struct vector2d *coords, struct asteroid *asteroid);

#endif /* _ASTEROID_H */
