#include "glwrapper.h"
#include "game.h"

int win_width = 800;
int win_height = 800;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(win_width, win_height);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - win_width) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - win_height) / 2);

    glutCreateWindow("Asteroids");

    glutDisplayFunc(display);
    glutKeyboardFunc(handle_keyboard);
    glutKeyboardUpFunc(handle_keyboard_up);
    glutSpecialFunc(handle_keyboard_special);
    glutSpecialUpFunc(handle_keyboard_special_up);
    glutTimerFunc(0, game_tick, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, win_width, 0.0, win_height, 0, 1);

    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

    game_init();

    glutMainLoop();

    return 0;
}
