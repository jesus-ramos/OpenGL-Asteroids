#ifndef ASTEROID_H
#define ASTEROID_H

struct asteroid
{
    struct position_info pos;
    struct list_head list;
    float angular_speed; /* radians */
};

void draw_asteroids(struct asteroid *asteroids);

#endif /* ASTEROID_H */
