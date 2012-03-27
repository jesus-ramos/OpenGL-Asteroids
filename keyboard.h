#ifndef _KEYBOARD_H
#define _KEYBOARD_H

extern char key_state[256];
extern char spec_key_state[128];

void handle_keystates();

#define DEF_KEYBOARD_HANDLER(name, val)         \
    void name(unsigned char key, int x, int y)  \
    {                                           \
        key_state[key] = val;                   \
    }

#define DEF_SPECIAL_HANDLER(name, val)          \
    void name(int key, int x, int y)            \
    {                                           \
        spec_key_state[key] = val;              \
    }

void handle_keyboard(unsigned char key, int x, int y);
void handle_keyboard_up(unsigned char key, int x, int y);
void handle_keyboard_special(int key, int x, int y);
void handle_keyboard_special_up(int key, int x, int y);

#endif /* _KEYBOARD_H */
