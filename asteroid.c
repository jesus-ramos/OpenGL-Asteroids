#include "asteroid.h"
#include "list.h"

void draw_asteroids(struct asteroid *asteroids)
{
    struct asteroid *tmp;
    
    if (!asteroids)
        return;

    list_for_each_entry(tmp, &asteroids->list, list)
    {
        /* DRAW */
    }
}
