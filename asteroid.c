#include <stdlib.h>

#include "asteroid.h"
#include "glwrapper.h"
#include "list.h"

#define ASTEROID_ROTATE_SPEED 10
#define NUM_CIRCLE_POINTS     1000
#define ASTEROID_RADIUS       100

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
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    draw_circle_loop(radius, num_points, coords);
    glEnd();
    
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    draw_circle_loop(radius, num_points, coords);
    glEnd();
}

#undef DRAW_CIRCLE_LOOP

int check_asteroid_collision(struct vector2d *coords, struct asteroid *asteroid)
{
    return distf(coords, &asteroid->pos.coords) <= asteroid->radius;
}

void move_asteroids(struct asteroid *asteroids)
{
    struct asteroid *tmp;

    list_for_each_entry(tmp, &asteroids->list, list)
    {
        /* MOVE */
    }
}

void draw_asteroids(struct asteroid *asteroids)
{
    struct asteroid *tmp;

    list_for_each_entry(tmp, &asteroids->list, list)
        draw_circle(tmp->radius, NUM_CIRCLE_POINTS, &tmp->pos.coords);
}

void init_asteroid(struct asteroid *asteroid, float x, float y)
{
    asteroid->pos.coords.x = x;
    asteroid->pos.coords.y = y;
    asteroid->radius = ASTEROID_RADIUS;
}

void delete_asteroid(struct asteroid *asteroid)
{
    list_del(&asteroid->list);
    free(asteroid);
}

void clear_asteroids(struct asteroid *asteroids)
{
    struct asteroid *asteroid, *n;

    list_for_each_entry_safe(asteroid, n, &asteroids->list, list)
        delete_asteroid(asteroid);
}
