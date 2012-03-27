#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "glwrapper.h"
#include "list.h"
#include "ship.h"

void init_ship(struct ship *ship, float x, float y)
{
    ship->bullet_count = 0;
    ship->pos.coords.x = x;
    ship->pos.coords.y = y;
    ship->pos.angle = 0;
    ship->pos.velocity = 0;
    ship->fire_wait = 0;

    INIT_LIST_HEAD(&ship->bullet_list.list);
}

static void init_bullet(struct bullet *bullet, struct ship *ship)
{
    bullet->pos.coords = ship->pos.coords;
    bullet->pos.angle = ship->pos.angle;
    bullet->life = 0;

    update_position(&bullet->pos, SHIP_HEIGHT);
}

void fire(struct ship *ship)
{
    struct bullet *new_bullet;

    if (ship->fire_wait != 0)
    {
        ship->fire_wait = (ship->fire_wait == BULLET_FIRE_WAIT) ?
            0 : ship->fire_wait + 1;
        return;
    }
    
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
    ship->fire_wait = 1;
}

void draw_bullets(struct bullet *bullet_list)
{
    struct bullet *tmp;

    glPointSize(BULLET_SIZE);
    
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    list_for_each_entry(tmp, &bullet_list->list, list)
        glVertex2f(tmp->pos.coords.x, tmp->pos.coords.y);
    glEnd();
}

void draw_ship(struct ship *ship)
{
    int i;
    struct vector2d ship_coords[] =
        {
            {ship->pos.coords.x, ship->pos.coords.y + SHIP_HEIGHT},
            {ship->pos.coords.x + SHIP_WIDTH, ship->pos.coords.y - SHIP_HEIGHT},
            {ship->pos.coords.x - SHIP_WIDTH, ship->pos.coords.y - SHIP_HEIGHT}
        };

    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glTranslatef(ship->pos.coords.x, ship->pos.coords.y, 0);
    glRotatef(-RAD_TO_DEG(ship->pos.angle), 0.0, 0.0, 1.0);
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
 
    draw_bullets(&ship->bullet_list);
}

void rotate_ship(struct ship *ship, int turn_val)
{
    ship->pos.angle += turn_val * DEG_TO_RAD(SHIP_ROTATE_SPEED);
}

void delete_bullet(struct ship *ship, struct bullet *bullet)
{
    ship->bullet_count--;
    list_del(&bullet->list);
    free(bullet);
}

void move_bullets(struct ship *ship)
{
    struct bullet *tmp;
    struct bullet *n;
    int win_h, win_w;

    GET_WINDOW_SIZE(win_w, win_h);
    
    list_for_each_entry_safe(tmp, n, &ship->bullet_list.list, list)
    {
        if (++tmp->life == BULLET_LIFETIME)
        {
            delete_bullet(ship, tmp);
            continue;
        }
        update_and_bound_pos(&tmp->pos, BULLET_MOVE_DIST,
                             0, win_w, 0, win_h);
    }
}

void move_ship(struct ship *ship, int direction)
{
    int win_h, win_w;

    GET_WINDOW_SIZE(win_w, win_h);

    update_and_bound_pos(&ship->pos, direction * SHIP_MOVE_DIST,
                         0, win_w, 0, win_h);
}
