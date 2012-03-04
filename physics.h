#ifndef PHYSICS_H
#define PHYSICS_H

struct position_info
{
    float x, y;
    float angle; /* radians */
    float velocity; /* World units / second */
};

void update_position(struct position_info *pos, int elapsed_time);

#endif /* PHYSICS_H */
