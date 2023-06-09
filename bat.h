#define GL_SILENCE_DEPRECATION
#ifndef __OPEN_GL_ICL_
#define __OPEN_GL_ICL_
//#include<OpenGL/OpenGL.h>
//#include<GLUT/GLUT.h>
#include<windows.h>
#include<GL/GL.h>
#include<GL/glut.h>
#endif


#ifndef __VECTOR2D_H_
#define __VECTOR2D_H_
#include "vector2D.h"
#endif

#include "init.h"

#define        LEFT            1
#define        RIGHT            2

class Bat {
public:
    float speed, w, h;
    Vector2D center, vtx[4], bvtx[4];

    Bat(float x, float y);

    void draw();
    void drawBounding();
    void update(bool L, bool R);
};
