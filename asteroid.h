#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "list.h"
#include "physics.h"

/**
 * @brief Structure that maintains asteroid position and speed
 */
struct asteroid
{
    struct position_info pos; /**< Coordinate of the asteroid */
    struct list_head list;    /**< List of asteroids currently on the screen */
    float angular_speed;      /**< Angular speed (rotation) of the asteroid */
    float radius;             /**< Asteroid radius */
    int num_points;           /**< Number of points that make up the asteroid */
                              /**< polygon */
    struct vector2d *points;  /**< Array of points that make up the asteroid */
                              /**< polygon */
};

void draw_asteroids(struct asteroid *asteroids);
void init_asteroid(struct asteroid *asteroid, float x, float y);
int check_asteroid_collision(struct vector2d *coords, struct asteroid *asteroid);
void delete_asteroid(struct asteroid *asteroid);
void clear_asteroids(struct asteroid *asteroids);
void move_asteroids(struct asteroid *asteroids);

#endif /* _ASTEROID_H */
