#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <math.h>

struct vector2d
{
    float x, y;
};

struct position_info
{
    struct vector2d coords;
    float angle; /* radians */
    float velocity; /* World units / second */
};

static inline void update_position(struct position_info *pos, float elapsed_time)
{
    float dist = pos->velocity * elapsed_time;

    pos->coords.x += dist * sinf(pos->angle);
    pos->coords.y += dist * cosf(pos->angle);
}

#endif /* _PHYSICS_H */
