#include "asteroid.h"
#include "list.h"

void draw_asteroids(struct asteroid *asteroids)
{
    /* Walk the asteroid list and draw each one */
}

void check_for_collision(struct position_info *pos, struct asteroid *asteroids)
{
    /*
     * Walk the asteroid list and check for a collision if we find one
     * remove that element from the list, free it, and return
     * (shouldn't get more than 1 collision per bullet
     */
}
