#include <stdlib.h>
#include <stdio.h>

#include "ship.h"
#include "list.h"

void init_ship(struct ship *ship, float x, float y)
{
    ship->bullet_count = 0;
    ship->bullet_list = NULL;
    ship->pos.x = x;
    ship->pos.y = y;
    ship->angle = 0;
    ship->velocity = 0;
}

static void init_bullet(struct bullet *bullet, struct ship *ship)
{
    init_list_head(&bullet->list);

    /* FIXME: LOCATIONS */
    bullet->pos = ship->pos;
}

void fire(struct ship *ship)
{
    struct bullet *new_bullet;

    if (ship->bullet_count == MAX_BULLET_COUNT)
        return;

    ship->bullet_count++;

    new_bullet = malloc(sizeof(struct bullet));
    if (!new_bullet)
    {
        printf("OOM: bullet\n");
        exit(1);
    }
    init_bullet(new_bullet, ship);

    if (!ship->bullet_list)
        ship->bullet_list = new_bullet;
    else
        list_add_tail(&new_bullet->list, &ship->bullet_list->list);
}

void draw_ship(struct ship *ship)
{
    /* Draw ship itself */

    /* Walk bullet_list and draw bullets too */
}
