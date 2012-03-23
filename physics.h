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
    float velocity;
};

static inline void update_position(struct position_info *pos, float dist)
{
    pos->coords.x += dist * sinf(pos->angle);
    pos->coords.y += dist * cosf(pos->angle);
}

static inline int in_bounds(float x, float y, float x_low, float x_high,
                            float y_low, float y_high)
{
    return x >= x_low && x <= x_high && y >= y_low && y <= y_high;
}

#endif /* _PHYSICS_H */
