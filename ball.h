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

#ifndef __ASSET_H_
#define __ASSET_H_
#include "asset.h"
#endif

#include "init.h"

class Ball {
public:
    Vector2D center;
    Vector2D direction;
    Asset asset;
    int type, star_time;
    float speed;

    Ball(float x, float y);
    void draw();
    void update();
    void setType(int t);
    void drawDirection();
};
