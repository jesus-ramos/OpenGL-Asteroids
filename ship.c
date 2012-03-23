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
    ship->pos.coords.x = x;
    ship->pos.coords.y = y;
    ship->pos.angle = 0;
    ship->pos.velocity = 0;

    INIT_LIST_HEAD(&ship->bullet_list.list);
}

static void init_bullet(struct bullet *bullet, struct ship *ship)
{
    bullet->pos.coords = ship->pos.coords;
    bullet->pos.angle = -ship->pos.angle;

    update_position(&bullet->pos, SHIP_HEIGHT);
}

void fire(struct ship *ship)
{
    struct bullet *new_bullet;

    if (ship->bullet_count == MAX_BULLET_COUNT)
        return;

    new_bullet = malloc(sizeof(struct bullet));
    if (!new_bullet)
    {
        printf("OOM: bullet\n");
        exit(1);
    }
    init_bullet(new_bullet, ship);

    list_add_tail(&new_bullet->list, &ship->bullet_list.list);

    ship->bullet_count++;
}

void draw_ship(struct ship *ship)
{
    int i;
    struct bullet *tmp;
    struct vector2d ship_coords[] =
        {
            {ship->pos.coords.x, ship->pos.coords.y + SHIP_HEIGHT},
            {ship->pos.coords.x + SHIP_WIDTH, ship->pos.coords.y - SHIP_HEIGHT},
            {ship->pos.coords.x - SHIP_WIDTH, ship->pos.coords.y - SHIP_HEIGHT}
        };

    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glTranslatef(ship->pos.coords.x, ship->pos.coords.y, 0);
    glRotatef(RAD_TO_DEG(ship->pos.angle), 0.0, 0.0, 1.0);
    glTranslatef(-ship->pos.coords.x, -ship->pos.coords.y, 0);
    
    /* Ship inside */
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    for (i = 0; i < 3; i++)
        glVertex2f(ship_coords[i].x, ship_coords[i].y);
    glEnd();

    /* Ship outline */
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for (i = 0; i < 3; i++)
    {
        glVertex2f(ship_coords[i].x, ship_coords[i].y);
        glVertex2f(ship_coords[(i + 1) % 3].x, ship_coords[(i + 1) % 3].y);
    }
    glEnd();

    glPopMatrix();
 
    if (!ship->bullet_count)
        return;

    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    list_for_each_entry(tmp, &ship->bullet_list.list, list)
    {
        glVertex2f(tmp->pos.coords.x, tmp->pos.coords.y);
    }
    glEnd();
}

void rotate_ship(struct ship *ship, int turn_val)
{
    int coeff = (turn_val == TURNING_LEFT) ? 1 : -1;
    ship->pos.angle += coeff * DEG_TO_RAD(SHIP_ROTATE_SPEED);
}

void move_bullets(struct ship *ship, float x_bound, float y_bound)
{
    struct bullet *tmp;
    struct bullet *n;

    if (!ship->bullet_count)
        return;

    list_for_each_entry_safe(tmp, n, &ship->bullet_list.list, list)
    {
        update_position(&tmp->pos, BULLET_MOVE_DIST);
        if (!in_bounds(tmp->pos.coords.x, tmp->pos.coords.y, 0, x_bound, 0, y_bound))
        {
            ship->bullet_count--;
            list_del(&tmp->list);
            free(tmp);
        }
    }
}
