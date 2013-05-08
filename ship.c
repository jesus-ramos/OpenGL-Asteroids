#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "glwrapper.h"
#include "list.h"
#include "ship.h"

#define MAX_BULLET_COUNT  (1UL << 30)
#define BULLET_MOVE_DIST  10
#define BULLET_FIRE_WAIT  3
#define BULLET_LIFETIME   100
#define BULLET_SIZE       1.5
#define NUM_CIRCLE_POINTS 500
#define SHIP_MOVE_DIST    6
#define SHIP_ROTATE_SPEED 10

void init_ship(struct ship *ship, float x, float y, float sRad)
{
    memset(ship, 0, sizeof(struct ship));

    ship->pos.coords.x = x;
    ship->pos.coords.y = y;
    ship->shield_radius = sRad;
    ship->invincible = 0;
    ship->status = NORMAL;
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

    if (ship->fire_wait)
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
        exit(EXIT_FAILURE);
    }
    init_bullet(new_bullet, ship);

    list_add_tail(&new_bullet->list, &ship->bullet_list.list);

    ship->bullet_count++;
    ship->fire_wait = 1;
}

static void draw_bullets(struct bullet *bullet_list)
{
    struct bullet *tmp;

    glPointSize(BULLET_SIZE);

    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    list_for_each_entry(tmp, &bullet_list->list, list)
        glVertex2f(tmp->pos.coords.x, tmp->pos.coords.y);
    glEnd();
}


static void draw_circle_loop(float radius, int num_points, struct vector2d *coords)
{
    int i;
    float x, y;
    float angle;

    for (i = 0; i < num_points; i++)
    {
        angle = i * (2.0f * M_PI / num_points);
        x = coords->x + cosf(angle) * radius;
        y = coords->y + sinf(angle) * radius;
        glVertex2f(x, y);
    }
    glVertex2f(coords->x + radius, coords->y);
}

static void draw_circle(float radius, int num_points, struct vector2d *coords)
{
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    draw_circle_loop(radius, num_points, coords);
    glEnd();
}

void draw_ship(struct ship *ship)
{
    int i;
    SHIP_COORDS(ship);

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
    switch(ship->status)
    {
	case NORMAL:
	    glColor3f(1.0, 1.0, 1.0); break;
	case INVINCIBLE:
	{
	    if(blink)
		glColor3f(0.0, 1.0, 1.0);
	    else
		glColor3f(1.0, 1.0, 1.0);
	    blink = !blink;
	    break;
	}
    }

    glBegin(GL_LINES);
    for (i = 0; i < 3; i++)
    {
        glVertex2f(ship_coords[i].x, ship_coords[i].y);
        glVertex2f(ship_coords[(i + 1) % 3].x, ship_coords[(i + 1) % 3].y);
    }
    glEnd();
    glPopMatrix();

//    draw_circle(ship->shield_radius*2, NUM_CIRCLE_POINTS, &ship->pos.coords);

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

void clear_bullets(struct ship *ship)
{
    struct bullet *bullet, *n;

    list_for_each_entry_safe(bullet, n, &ship->bullet_list.list, list)
        delete_bullet(ship, bullet);
}

void move_bullets(struct ship *ship)
{
    struct bullet *tmp;
    struct bullet *n;
    int win_h, win_w;

    get_window_size(&win_w, &win_h);

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

    get_window_size(&win_w, &win_h);

    update_and_bound_pos(&ship->pos, direction * SHIP_MOVE_DIST,
                         0, win_w, 0, win_h);
}

