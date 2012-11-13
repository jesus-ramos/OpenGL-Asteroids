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

static inline void bound_position(struct vector2d *coords, float min_x, float max_x,
                                  float min_y, float max_y)
{
    coords->x = bound_float(coords->x, min_x, max_x);
    coords->y = bound_float(coords->y, min_y, max_y);
}

static inline void update_and_bound_pos(struct position_info *pos, float dist,
                                        float min_x, float max_x,
                                        float min_y, float max_y)
{
    update_position(pos, dist);
    bound_position(&pos->coords, min_x, max_x, min_y, max_y);
}

static inline float distf(struct vector2d *p1, struct vector2d *p2)
{
    return sqrtf(SQUARE(p2->x - p1->x) + SQUARE(p2->y - p1->y));
}

//magic
static inline int pnpoly(int numVerts, struct vector2d* poly, struct vector2d* point)
{
    int i, j, c = 0;
    for (i = 0, j = numVerts-1; i < numVerts; j = i++) {
	if (((poly[i].y > point->y) != (poly[j].y > point->y)) &&
	    (point->x < (poly[j].x - poly[i].x) * (point->y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x))
	    c = !c;
    }
    return c;
}

#endif /* _PHYSICS_H */
