#include <stdlib.h>

#include "keyboard.h"
#include "glwrapper.h"
#include "game.h"

#define DECL_KEYBOARD_HANDLER(name, val)        \
    void name(unsigned char key, int x, int y)  \
    {                                           \
        key_state[key] = val;                   \
    }

#define DECL_SPECIAL_HANDLER(name, val)         \
    void name(int key, int x, int y)            \
    {                                           \
        spec_key_state[key] = val;              \
    }

char key_state[256];
char spec_key_state[128];

void handle_keystates()
{
    if (key_state['q'])
        exit(EXIT_SUCCESS);
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

DECL_KEYBOARD_HANDLER(handle_keyboard, 1)
DECL_KEYBOARD_HANDLER(handle_keyboard_up, 0)
DECL_SPECIAL_HANDLER(handle_keyboard_special, 1)
DECL_SPECIAL_HANDLER(handle_keyboard_special_up, 0)
