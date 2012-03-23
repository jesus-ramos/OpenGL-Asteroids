#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif /* __APPLE__ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ship.h"
#include "asteroid.h"
#include "list.h"

#define WIN_H 1024
#define WIN_W 1024

#define TIMER_TICK 20 /* ms per tick */

#define MAX_BGND_STARS 500

/* Drawable Objects */
struct ship ship;
struct asteroid *asteroids;
struct vector2d star_coords[500];

/* Game state */
unsigned int score;
unsigned int lives;

static void init_game_values()
{
    score = 0;
    lives = 3;
}

static void draw_string(float x, float y, void *font, char *string)
{
    char *c;
    
    glRasterPos2f(x, y);
    for (c = string; *c; c++)
        glutBitmapCharacter(font, *c);
}

static void draw_score()
{
    char buf[16];

    snprintf(buf, 16, "Score: %d", score);
    draw_string(WIN_W - WIN_W / 7, WIN_H - WIN_H / 15,
                GLUT_BITMAP_HELVETICA_18, buf);
}

static void draw_stars()
{
    int i;

    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    for (i = 0; i < MAX_BGND_STARS; i++)
        glVertex2f(star_coords[i].x, star_coords[i].y);
    glEnd();
}

static void handle_keyboard_special(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT)
    {
        int turn_val = (key == GLUT_KEY_LEFT) ? TURNING_LEFT : TURNING_RIGHT;
        rotate_ship(&ship, turn_val);
    }
}

static void init_stars()
{
    int i;
    float x, y;

    for (i = 0; i < MAX_BGND_STARS; i++)
    {
        x = (float)(rand() % WIN_W);
        y = (float)(rand() % WIN_H);
        star_coords[i].x = x;
        star_coords[i].y = y;
    }
}

static void display()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    /* Flat background */
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, WIN_H);
    glVertex2f(WIN_W, WIN_H);
    glVertex2f(WIN_W, 0.0);
    glEnd();

    draw_stars();
    draw_ship(&ship);
    draw_asteroids(asteroids);
    draw_score();

    glFlush();
}

static void init_game_objects()
{
    srand((unsigned int)time(NULL));
    init_ship(&ship, WIN_W / 2, WIN_H / 2);
    init_stars();
    /* TODO: init asteroids */
}

static inline void game_init()
{
    init_game_objects();
    init_game_values();
}

static void world_tick(int value)
{
    glutPostRedisplay();
    glutTimerFunc(TIMER_TICK, world_tick, 0);
}

static void handle_keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'r':
            game_init();
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(WIN_W, WIN_H);
    glutCreateWindow("Asteroids");

    glutDisplayFunc(display);
    glutKeyboardFunc(handle_keyboard);
    glutSpecialFunc(handle_keyboard_special);
    glutTimerFunc(0, world_tick, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIN_W, 0.0, WIN_H, 0, 1);
    glMatrixMode(GL_MODELVIEW);

    game_init();
    
    glutMainLoop();

    return 0;
}
