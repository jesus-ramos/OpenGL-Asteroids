#include "asteroid.h"
#include "glwrapper.h"
#include "list.h"

#define ASTEROID_ROTATE_SPEED 10

#define NUM_CIRCLE_POINTS 100

static void draw_circle(float radius, int num_points)
{
    int i;
    float angle;
    float x, y;
    
    glBegin(GL_LINE_STRIP);
    for (i = 0; i < num_points; i++)
    {
        angle = i * (2.0 * M_PI / num_points);
        x = cosf(angle) * radius;
        y = sinf(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();
}

int check_asteroid_collision(struct vector2d *coords, struct asteroid *asteroid)
{
    return distf(coords, &asteroid->pos.coords) <= asteroid->radius;
}

void draw_asteroids(struct asteroid *asteroids)
{
    struct asteroid *tmp;
    
    list_for_each_entry(tmp, &asteroids->list, list)
        draw_circle(tmp->radius, NUM_CIRCLE_POINTS);
}

void init_asteroid(struct asteroid *asteroid)
{
    INIT_LIST_HEAD(&asteroid->list);
}
