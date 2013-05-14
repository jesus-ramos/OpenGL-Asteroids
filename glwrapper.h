#ifndef _GLWRAPPER_H
#define _GLWRAPPER_H

#include <GL/freeglut.h>
#include <GL/glut.h>

static inline void get_window_size(int *width, int *height)
{
    *width = glutGet(GLUT_WINDOW_WIDTH);
    *height = glutGet(GLUT_WINDOW_HEIGHT);
}

#endif /* _GLWRAPPER_H */
