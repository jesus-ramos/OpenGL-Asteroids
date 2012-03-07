#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif /* __APPLE__ */

#include <stdlib.h>
#include <stdio.h>

#include "ship.h"
#include "list.h"

void init_ship(struct ship *ship, float x, float y)
{
    ship->bullet_count = 0;
    ship->bullet_list = NULL;
    ship->pos.coords.x = x;
    ship->pos.coords.y = y;
    ship->pos.angle = 0;
    ship->pos.velocity = 0;
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
    struct bullet *tmp;

    /* Ship inside */
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    /* TODO */
    glEnd();

    /* Ship outline */
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    /* TODO */
    glEnd();

    if (!ship->bullet_list)
        return;
    
    list_for_each_entry(tmp, &ship->bullet_list->list, list)
    {
        /* DRAW */
    }
}
