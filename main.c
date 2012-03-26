#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif /* __APPLE__ */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ship.h"
#include "asteroid.h"
#include "list.h"

#define TIMER_TICK 20

#define MAX_BGND_STARS 500

struct ship ship;
struct asteroid asteroids;
struct vector2d star_coords[500];

unsigned int score;
unsigned int lives;

bool key_state[256];
bool spec_key_state[128];

unsigned int win_h = 1024;
unsigned int win_w = 1024;

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

    for (i = 0; i < MAX_BGND_STARS; i++)
    {
        x = (float)(rand() % win_w);
        y = (float)(rand() % win_h);
        star_coords[i].x = x;
        star_coords[i].y = y;
    }
}

static void display()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    /* Flat background */
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

    glFlush();
}

static void generate_asteroids()
{
    /* TODO: Make a bunch of Asteroids to kill */
    init_asteroid(&asteroids);
}

static void init_game_objects()
{
    srand((unsigned int)time(NULL));
    init_ship(&ship, win_w / 2, win_h / 2);
    generate_asteroids();
    generate_stars();
}

static inline void game_init()
{
    init_game_objects();
    init_game_values();
}

static void handle_keystates()
{
    if (key_state[' '])
        fire(&ship);
    if (key_state['r'])
        game_init();
    
    if (spec_key_state[GLUT_KEY_LEFT] ^ spec_key_state[GLUT_KEY_RIGHT])
        rotate_ship(&ship, (spec_key_state[GLUT_KEY_LEFT]) ?
                    TURNING_LEFT: TURNING_RIGHT);
    if (spec_key_state[GLUT_KEY_UP] ^ spec_key_state[GLUT_KEY_DOWN])
        move_ship(&ship, (spec_key_state[GLUT_KEY_UP]) ?
                  MOVING_FORWARD : MOVING_BACKWARD);
}

static void world_tick(int value)
{
    move_bullets(&ship);

    handle_keystates();

    glutPostRedisplay();
    glutTimerFunc(TIMER_TICK, world_tick, 0);
}

static void handle_keyboard(unsigned char key, int x, int y)
{
    key_state[key] = true;
}

static void handle_keyboard_up(unsigned char key, int x, int y)
{
    key_state[key] = false;
}


static void handle_keyboard_special(int key, int x, int y)
{
    spec_key_state[key] = true;
}

static void handle_keyboard_special_up(int key, int x, int y)
{
    spec_key_state[key] = false;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(win_w, win_h);
    glutCreateWindow("Asteroids");

    glutDisplayFunc(display);
    glutKeyboardFunc(handle_keyboard);
    glutKeyboardUpFunc(handle_keyboard_up);
    glutSpecialFunc(handle_keyboard_special);
    glutSpecialUpFunc(handle_keyboard_special_up);
    glutTimerFunc(0, world_tick, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, win_w, 0.0, win_h, 0, 1);
    glViewport(0, 0, win_w, win_h);

    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    
    game_init();
    
    glutMainLoop();

    return 0;
}
