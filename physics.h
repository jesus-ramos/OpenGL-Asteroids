#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <math.h>

/**
 * @brief Converts an angle from radians to degrees
 *
 * @param rad angle in radians to convert
 */
#define RAD_TO_DEG(rad) (rad * (180 / M_PI))

/**
 * @brief Converts an angle from degrees to radians
 *
 * @param deg angle in degrees to convert
 */
#define DEG_TO_RAD(deg) (deg * (M_PI / 180))

/**
 * @brief Takes a mathematical expression and raises it to the 2nd power
 *
 * @param expr mathematical expression to square
 */
#define SQUARE(expr) ((expr) * (expr))

/**
 * @brief A two dimensional vector point
 */
struct vector2d
{
    float x; /**< X coordinate of the point */
    float y; /**< Y coordinate of the point */
};

/**
 * @brief Positional information
 */
struct position_info
{
    struct vector2d coords; /**< Location of the object */
    float angle;            /**< Angle the object is facing (in radians) */
    float velocity;         /**< Velocity of the object */
};

/**
 * @brief Updates the position vector by a certain distance
 *
 * @param[out] pos position to update
 * @param dist distance to modify pos by
 */
static inline void update_position(struct position_info *pos, float dist)
{
    pos->coords.x += dist * sinf(pos->angle);
    pos->coords.y += dist * cosf(pos->angle);
}

/**
 * @brief Bound a float value between min_val and max_val
 *
 * @param val float value to bound
 * @param min_val minimum value to bound to
 * @param max_val maximum value to bound to
 *
 * @return bounded version of val
 */
static inline float bound_float(float val, float min_val, float max_val)
{
    if (val < min_val)
        return max_val - min_val - val;
    else if (val > max_val)
        return (max_val - val) + min_val;
    return val;
}

/**
 * @brief Bound a position in the coordinate plane
 *
 * @param[out] coords coordinates to bound in the plane
 * @param min_x minimum x value for the plane
 * @param max_x maximum x value for the plane
 * @param min_y minimum y value for the plane
 * @param max_y maximum y value for the plane
 *
 * @return 1 if the coords was bounded, 0 otherwise
 */
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

/**
 * @brief Update and bound a position vector
 *
 * @param[out] pos position to update and bound
 * @param dist distance to update the vector by
 * @param min_x minimum x value for the boundary plane
 * @param max_x maximum x value for the boundary plane
 * @param min_y minimum y value for the boundary plane
 * @param max_y maximum y value for the boundary plane
 *
 * @return 1 if pos value was bound after being updated, 0 otherwise
 */
static inline int update_and_bound_pos(struct position_info *pos, float dist,
                                        float min_x, float max_x,
                                        float min_y, float max_y)
{
    update_position(pos, dist);

    return bound_position(&pos->coords, min_x, max_x, min_y, max_y);
}

/**
 * @brief Calculate distance between two points
 *
 * @return distance from (x1, y1) to (x2, y2)
 */
static inline float distpts(int x1, int y1, int x2, int y2)
{
    return sqrtf(SQUARE(x2 - x1) + SQUARE(y2 - y1));
}

/**
 * @brief Calculate distance between two points described by vectors
 *
 * @param[in] p1 start point of the line
 * @param[in] p2 end point of the line
 *
 * @return distance between p1 and p2
 */
static inline float distf(struct vector2d *p1, struct vector2d *p2)
{
    return distpts(p1->x, p1->y, p2->x, p2->y);
}

/**
 * @brief Determines whether a point lies in a polygon
 *
 * @param num_vertices number of vertices in the polygon
 * @param[in] poly array of points describing the polygon
 * @param[in] point point that is possibly in the polygon
 *
 * @return positive value of the point is in the polygon, 0 otherwise
 */
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
