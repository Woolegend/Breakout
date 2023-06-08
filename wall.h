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

class Wall {
public:
    Vector2D start, end;
    Vector2D direction, normal;
    float length;

    Wall();
    Wall(float x1, float y1, float x2, float y2);
    
    void draw();
    void drawNormal();
};

