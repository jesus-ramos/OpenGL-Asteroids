#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "asteroid.h"
#include "game.h"
#include "glwrapper.h"
#include "keyboard.h"
#include "physics.h"
#include "ship.h"

struct ship ship;
struct asteroid asteroids;
struct vector2d star_coords[MAX_BGND_STARS];

unsigned int score;
unsigned int lives;
unsigned int level;

static void draw_string(float x, float y, void *font, char *string)
{
    char *c;
    
    glRasterPos2f(x, y);
    for (c = string; *c; c++)
        glutBitmapCharacter(font, *c);
}

static void draw_level()
{
    char buf[16];
    int params[4];
    int win_h, win_w;

    glGetIntegerv(GL_VIEWPORT, params);

    win_w = params[2];
    win_h = params[3];

    glColor3f(1.0, 1.0, 1.0);
    snprintf(buf, 16, "Level %u", level);
    draw_string(win_w / 20, win_h - win_h / 15,
                GLUT_BITMAP_HELVETICA_18, buf);
}

static void draw_score()
{
    char buf[16];
    int params[4];
    int win_h, win_w;

    glGetIntegerv(GL_VIEWPORT, params);

    win_w = params[2];
    win_h = params[3];

    glColor3f(1.0, 1.0, 1.0);
    snprintf(buf, 16, "Score: %d", score);
    draw_string(win_w - win_w / 7, win_h - win_h / 15,
                GLUT_BITMAP_HELVETICA_18, buf);
}

static void draw_stars()
{
    int i;

    glPointSize(1.0);
    
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    for (i = 0; i < MAX_BGND_STARS; i++)
        glVertex2f(star_coords[i].x, star_coords[i].y);
    glEnd();
}

static void generate_stars()
{
    int i;
    float x, y;
    int params[4];

    glGetIntegerv(GL_VIEWPORT, params);

    for (i = 0; i < MAX_BGND_STARS; i++)
    {
        x = (float)(rand() % params[2]);
        y = (float)(rand() % params[3]);
        star_coords[i].x = x;
        star_coords[i].y = y;
    }
}

void display()
{
    int params[4];
    int win_h, win_w;
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    
    glGetIntegerv(GL_VIEWPORT, params);

    win_h = params[3];
    win_w = params[2];
    
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, win_h);
    glVertex2f(win_w, win_h);
    glVertex2f(win_w, 0.0);
    glEnd();

    draw_stars();
    draw_ship(&ship);
    draw_asteroids(&asteroids);
    draw_score();
    draw_level();

    glFlush();
}

static void generate_asteroids()
{
    /* TODO: Make a bunch of Asteroids to kill */
    init_asteroid(&asteroids);
}

static void init_game_values()
{
    score = 0;
    lives = MAX_LIVES;
    level = 1;
}

static void init_game_objects()
{
    int params[4];

    glGetIntegerv(GL_VIEWPORT, params);
    
    srand((unsigned int)time(NULL));
    init_ship(&ship, params[2] / 2, params[3] / 2);
    generate_asteroids();
    generate_stars();
}

void game_init()
{
    init_game_objects();
    init_game_values();
}

void game_tick(int value)
{
    move_bullets(&ship);

    handle_keystates();

    glutPostRedisplay();
    glutTimerFunc(TIMER_TICK, game_tick, 0);
}
