#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "list.h"
#include "physics.h"

struct asteroid
{
    struct position_info pos;
    struct list_head list;
    float angular_speed; /* radians */
};

void draw_asteroids(struct asteroid *asteroids);

#endif /* _ASTEROID_H */
