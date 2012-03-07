#ifndef _PHYSICS_H
#define _PHYSICS_H

struct position_info
{
    float x, y;
    float angle; /* radians */
    float velocity; /* World units / second */
};

void update_position(struct position_info *pos, int elapsed_time);

#endif /* _PHYSICS_H */
