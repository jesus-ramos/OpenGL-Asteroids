#include <stdlib.h>
#include <stdio.h>

#include "asteroid.h"
#include "glwrapper.h"
#include "list.h"

#define ASTEROID_ROTATE_SPEED 10
#define ASTEROID_RADIUS       20

struct vector2d* generatePoints(float centerX, float centerY, float radius, int numPoints)
{
    struct vector2d* points = malloc(sizeof(struct vector2d) * numPoints);
    float x, y, angle;
    float bound = radius * 2;
    int i, diff;
    angle = 0;
    for (i = 0; i < numPoints; i++)
    {
	x = 0;
	y = 0;

	diff = rand() % (int)bound;

	angle = (i + 1) * (2.0f * M_PI / numPoints);
	x = centerX + cosf(angle) * (radius + diff);
	y = centerY + sinf(angle) * (radius + diff);

	points[i].x = x;
	points[i].y = y;
    }

    return points;
}

void draw_polygon(struct vector2d* center, int numPoints, struct vector2d* points, int mode)
{
    int i;
    if(mode == GL_TRIANGLE_FAN)
	glVertex2f(center->x, center->y);

    for(i = 0; i < numPoints; i++)
	glVertex2f(points[i].x, points[i].y);

    glVertex2f(points[0].x, points[0].y);
}

static void draw_asteroid(struct vector2d* center, int numPoints, struct vector2d* points)
{
    glMatrixMode(GL_MODELVIEW);

    //draw inner asteroid
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    draw_polygon(center, numPoints, points, GL_TRIANGLE_FAN);
    glEnd();

    //draw outline
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    draw_polygon(center, numPoints, points, GL_LINE_STRIP);
    glEnd();

}

int check_asteroid_collision(struct vector2d *coords, struct asteroid *asteroid)
{
    int collided = 0;
    collided = pnpoly(asteroid->numPoints, asteroid->points, coords);
    return collided;
}

void move_asteroids(struct asteroid *asteroids)
{
    struct asteroid *tmp;
    int win_h, win_w;
    int i, inbounds;

    get_window_size(&win_w, &win_h);

    list_for_each_entry(tmp, &asteroids->list, list)
    {
        /* MOVE */

	for(i = 0; i < tmp->numPoints; i++)
	{
	    tmp->points[i].x += tmp->pos.velocity * sinf(tmp->pos.angle);
	    tmp->points[i].y += tmp->pos.velocity * cosf(tmp->pos.angle);
	}

	update_position(&tmp->pos, tmp->pos.velocity);

	inbounds = 0;
	for(i = 0; i < tmp->numPoints; i++)
	{
	    struct vector2d point = tmp->points[i];
	    if((point.x >= 0 && point.x <= win_w) &&
	       (point.y >= 0 && point.y <= win_h))
	    {
		inbounds = 1;
	    }
	}
	if(!inbounds)
	{
	    for(i = 0; i < tmp->numPoints; i++)
		bound_position(&tmp->points[i], 0, win_w, 0, win_h);
	    bound_position(&tmp->pos.coords, 0, win_w, 0, win_h);
	}

    }
}

void draw_asteroids(struct asteroid *asteroids)
{
    struct asteroid *tmp;

    list_for_each_entry(tmp, &asteroids->list, list)
	draw_asteroid(&tmp->pos.coords, tmp->numPoints, tmp->points);
}

void init_asteroid(struct asteroid *asteroid, float x, float y)
{
    int numPoints = rand() % 11 + 5;
    float vel = rand() % 3 + 1;
    float velAngle  = rand() % 360;
    struct vector2d* points = generatePoints(x, y, ASTEROID_RADIUS, numPoints);

    asteroid->numPoints = numPoints;
    asteroid->points = points;
    asteroid->pos.coords.x = x;
    asteroid->pos.coords.y = y;
    asteroid->pos.velocity = vel;
    asteroid->pos.angle = DEG_TO_RAD(velAngle);
    asteroid->radius = ASTEROID_RADIUS;
}

void delete_asteroid(struct asteroid *asteroid)
{
    list_del(&asteroid->list);
    free(asteroid->points);
    free(asteroid);
}

void clear_asteroids(struct asteroid *asteroids)
{
    struct asteroid *asteroid, *n;

    list_for_each_entry_safe(asteroid, n, &asteroids->list, list)
        delete_asteroid(asteroid);
}
