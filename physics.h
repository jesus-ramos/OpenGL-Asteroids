#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <math.h>

#define RAD_TO_DEG(rad) (rad * (180 / M_PI))
#define DEG_TO_RAD(deg) (deg * (M_PI / 180))

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
