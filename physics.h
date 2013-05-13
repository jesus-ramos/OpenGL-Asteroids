#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <math.h>

#define RAD_TO_DEG(rad) (rad * (180 / M_PI))
#define DEG_TO_RAD(deg) (deg * (M_PI / 180))

#define SQUARE(expr) ((expr) * (expr))

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

static inline float bound_float(float val, float min_val, float max_val)
{
    if (val < min_val)
        return max_val - min_val - val;
    else if (val > max_val)
        return (max_val - val) + min_val;
    return val;
}

static inline int bound_position(struct vector2d *coords, float min_x,
                                 float max_x, float min_y, float max_y)
{
    float x, y, bounded;

    x = bound_float(coords->x, min_x, max_x);
    y = bound_float(coords->y, min_y, max_y);
    bounded = coords->x != x || coords->y != y;

    coords->x = x;
    coords->y = y;

    return bounded;
}

static inline int update_and_bound_pos(struct position_info *pos, float dist,
                                        float min_x, float max_x,
                                        float min_y, float max_y)
{
    int bounded;

    update_position(pos, dist);
    bounded = bound_position(&pos->coords, min_x, max_x, min_y, max_y);

    return bounded;
}

static inline float distf(struct vector2d *p1, struct vector2d *p2)
{
    return sqrtf(SQUARE(p2->x - p1->x) + SQUARE(p2->y - p1->y));
}

static inline float distpts(int x1, int y1, int x2, int y2)
{
    return sqrtf(SQUARE(x2 - x1) + SQUARE(y2 - y1));
}

static inline int point_in_polygon(int num_vertices, struct vector2d* poly,
                                   struct vector2d* point)
{
    int i, j, c;

    c = 0;
    for (i = 0, j = num_vertices-1; i < num_vertices; j = i++)
        if (((poly[i].y > point->y) != (poly[j].y > point->y)) &&
            (point->x < (poly[j].x - poly[i].x) * (point->y - poly[i].y) /
             (poly[j].y - poly[i].y) + poly[i].x))
            c = !c;

    return c;
}

#endif /* _PHYSICS_H */
