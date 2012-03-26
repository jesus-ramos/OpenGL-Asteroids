#include "asteroid.h"
#include "list.h"

void draw_asteroids(struct asteroid *asteroids)
{
    struct asteroid *tmp;
    
    list_for_each_entry(tmp, &asteroids->list, list)
    {
        /* DRAW */
    }
}

void init_asteroid(struct asteroid *asteroid)
{
    INIT_LIST_HEAD(&asteroid->list);
}
