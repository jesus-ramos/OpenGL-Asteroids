#include <stdlib.h>
#include <stdio.h>

#include "asteroid.h"
#include "glwrapper.h"
#include "list.h"

#define ASTEROID_ROTATE_SPEED 10
#define NUM_CIRCLE_POINTS     1000
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

	struct vector2d * pt = (struct vector2d*) malloc(sizeof(struct vector2d));

	pt->x = x;
	pt->y = y;

	points[i] = *pt;
    }
	
    return points;
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

int check_asteroid_collision(struct vector2d *coords, struct asteroid *asteroid)
{
    int collided = 0;
    // return distf(coords, &asteroid->pos.coords) <= asteroid->radius;
    
    return collided;
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
	draw_asteroid(&(tmp->pos.coords), tmp->numPoints, tmp->points);
}

void init_asteroid(struct asteroid *asteroid, float x, float y)
{
    int numPoints = rand() % 11 + 5;

    struct vector2d* points = generatePoints(x, y, ASTEROID_RADIUS, numPoints);

    asteroid->numPoints = numPoints;
    asteroid->points = points;
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
