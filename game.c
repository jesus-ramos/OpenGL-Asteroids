#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "asteroid.h"
#include "game.h"
#include "glwrapper.h"
#include "keyboard.h"
#include "physics.h"
#include "ship.h"

#define STAR_SIZE 1.0

#define NUM_ASTEROIDS 3

#define TIMER_TICK 20

#define MAX_BGND_STARS 500
#define MAX_LIVES 3

#define GET_RAND_COORDS(x, y)                   \
    do {                                        \
        int width, height;                      \
        GET_WINDOW_SIZE(width, height);         \
        x = (float)(rand() % width);            \
        y = (float)(rand() % height);           \
    } while (0)

#define DECL_DRAW_VALUE_FUNC(name, fmtstring, val, x, y)        \
    static void name()                                          \
    {                                                           \
        char buf[16];                                           \
        int win_h, win_w;                                       \
        GET_WINDOW_SIZE(win_w, win_h);                          \
        glColor3f(1.0, 1.0, 1.0);                               \
        snprintf(buf, 16, fmtstring, val);                      \
        draw_string(x, y, GLUT_BITMAP_HELVETICA_18, buf);       \
    }

struct ship ship;
struct asteroid asteroids;
struct vector2d star_coords[MAX_BGND_STARS];

unsigned int score;
unsigned int lives;
unsigned int level;
char game_over;

static void draw_string(float x, float y, void *font, char *string)
{
    char *c;
    
    glRasterPos2f(x, y);
    for (c = string; *c; c++)
        glutBitmapCharacter(font, *c);
}

static int get_str_width(void *font, char *str)
{
    char *i = str;
    int width = 0;

    while (*i)
        width += glutBitmapWidth(font, *i++);

    return width;
}

DECL_DRAW_VALUE_FUNC(draw_level, "Level %u", level,
                     win_w / 20, win_h - win_h / 15)

DECL_DRAW_VALUE_FUNC(draw_score, "Score: %d", score,
                     win_w - win_w / 7, win_h - win_h / 15)

DECL_DRAW_VALUE_FUNC(draw_lives, "Lives: %d", lives,
                     win_w - win_w / 7, win_h - win_h / 15 - 18)

static void draw_stars()
{
    int i;

    glPointSize(STAR_SIZE);
    
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    for (i = 0; i < MAX_BGND_STARS; i++)
        glVertex2f(star_coords[i].x, star_coords[i].y);
    glEnd();
}

static void generate_stars()
{
    int i;

    for (i = 0; i < MAX_BGND_STARS; i++)
        GET_RAND_COORDS(star_coords[i].x, star_coords[i].y);
}

static void draw_game_over()
{
    int win_w, win_h;
    char *str = "GAME OVER";
    char buf[32];
    int str_width;
    
    GET_WINDOW_SIZE(win_w, win_h);
    str_width = get_str_width(GLUT_BITMAP_HELVETICA_18, str);
    snprintf(buf, 32, "Final Score: %d", score);
    
    draw_string(win_w / 2 - str_width / 2, win_h / 2,
                GLUT_BITMAP_HELVETICA_18, str);
    
    str_width = get_str_width(GLUT_BITMAP_HELVETICA_18, buf);
    draw_string(win_w / 2 - str_width / 2, win_h / 2 + 18,
                GLUT_BITMAP_HELVETICA_18, buf);
}

void display()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    
    draw_stars();

    if (game_over)
    {
        draw_game_over();
        goto out;
    }
    
    draw_ship(&ship);
    draw_asteroids(&asteroids);
    draw_score();
    draw_level();
    draw_lives();

out:
    glFlush();
}

static void generate_asteroids()
{
    int i;
    float x, y;
    struct asteroid *tmp;
        
    INIT_LIST_HEAD(&asteroids.list);
    
    for (i = 0; i < NUM_ASTEROIDS; i++)
    {
        tmp = malloc(sizeof(struct asteroid));
        if (!tmp)
        {
            printf("OOM: asteroid\n");
            exit(EXIT_FAILURE);
        }
        
        GET_RAND_COORDS(x, y);
        init_asteroid(tmp, x, y);
        list_add_tail(&tmp->list, &asteroids.list);
    }
}

static void init_game_values()
{
    score = 0;
    lives = MAX_LIVES;
    level = 1;
    game_over = 0;
}

static void init_game_objects()
{
    int win_w, win_h;

    GET_WINDOW_SIZE(win_w, win_h);
    
    srand((unsigned int)time(NULL));
    init_ship(&ship, win_w / 2, win_h / 2);
    generate_asteroids();
    generate_stars();
}

void game_init()
{
    init_game_objects();
    init_game_values();
}

static void advance_level()
{
    level++;
    generate_asteroids();
    clear_bullets(&ship);
}

static void check_collisions()
{
    struct asteroid *asteroid;
    struct bullet *bullet;
    int win_w, win_h;

    GET_WINDOW_SIZE(win_w, win_h);

    list_for_each_entry(asteroid, &asteroids.list, list)
    {
        if (check_asteroid_collision(&ship.pos.coords, asteroid))
        {
            init_ship(&ship, win_w / 2, win_h / 2);
            lives--;
            if (lives == 0)
                game_over = 1;
        }
        
        list_for_each_entry(bullet, &ship.bullet_list.list, list)
            if (check_asteroid_collision(&bullet->pos.coords, asteroid))
            {
                score += 10;
                
                delete_bullet(&ship, bullet);
                delete_asteroid(asteroid);
                break;
            }
    }

    if (list_empty(&asteroids.list))
        advance_level();
}

void game_reset()
{
    clear_bullets(&ship);
    game_init();
}

void game_tick(int value)
{
    int should_redisplay = 1;
    
    if (game_over)
    {
        should_redisplay = 0;
        goto out;
    }
    
    move_bullets(&ship);
    move_asteroids(&asteroids);

    check_collisions();

out:
    handle_keystates();

    if (should_redisplay)
        glutPostRedisplay();
    glutTimerFunc(TIMER_TICK, game_tick, 0);
}
