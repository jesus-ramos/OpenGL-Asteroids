#ifndef _GLWRAPPER_H
#define _GLWRAPPER_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif /* __APPLE__ */

static inline void get_window_size(int *width, int *height)
{
    *width = glutGet(GLUT_WINDOW_WIDTH);
    *height = glutGet(GLUT_WINDOW_HEIGHT);
}

#endif /* _GLWRAPPER_H */
