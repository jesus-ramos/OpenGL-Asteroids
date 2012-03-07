#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif /* __APPLE__ */

#include "ship.h"
#include "asteroid.h"
#include "list.h"

#define WIN_H 1024
#define WIN_W 1024

struct ship ship;
struct asteroid *asteroids;

void handle_keyboard_special(int key, int x, int y)
{

}

void display()
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

    draw_ship(&ship);
    draw_asteroids(asteroids);

    glFlush();
}

void init_game_objects()
{
    init_ship(&ship, WIN_W / 2, WIN_H / 2);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(WIN_W, WIN_H);
    glutCreateWindow("Asteroids");

    glutDisplayFunc(display);
    glutSpecialFunc(handle_keyboard_special);

    init_game_objects();
    
    glutMainLoop();

    return 0;
}
