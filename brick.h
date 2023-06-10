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

class Brick {
public:
    int type, color, item, durability;
    float angle;
    Vector2D center, vtx[4], bvtx[4], gravity;
    Asset asset;

    Brick(int t, float x, float y);

    void init();
    void draw();
    void drawBounding();
    void collision();
};
