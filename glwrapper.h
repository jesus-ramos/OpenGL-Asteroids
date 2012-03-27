#ifndef _GLWRAPPER_H
#define _GLWRAPPER_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif /* __APPLE__ */

#define GET_WINDOW_SIZE(width, height)          \
    do {                                        \
        width = glutGet(GLUT_WINDOW_WIDTH);     \
        height = glutGet(GLUT_WINDOW_HEIGHT);   \
    } while (0)

#endif /* _GLWRAPPER_H */
