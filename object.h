#define GL_SILENCE_DEPRECATION
#ifndef __OPEN_GL_ICL_
#define __OPEN_GL_ICL_
//#include<OpenGL/OpenGL.h>
//#include<GLUT/GLUT.h>
#include<windows.h>
#include<GL/GL.h>
#include<GL/glut.h>
#endif

#ifndef __BALL_H_
#define __BALL_H_
#include "ball.h"
#endif

#ifndef __WALL_H_
#define __WALL_H_
#include "wall.h"
#endif

#ifndef __BAT_H_
#define __BAT_H_
#include "bat.h"
#endif

#ifndef __BRICK_H_
#define __BRICK_H_
#include "brick.h"
#endif

#ifndef __MATH_H_
#define __MATH_H_
#include <math.h>
#endif

#ifndef __ASSET_H_
#define __ASSET_H_
#include "asset.h"
#endif

#include "init.h"

class Object {
    Ball* ball;
    Bat* bat;
    Wall* wall[NUMOFWALL];
    Brick*** brick;
    Asset asset;
    int life, brick_num, pipe_time;
    float col_dis, pipe_angle;
    bool isPlay, isReady, isOver, isPause;
public:
    Object();
    void initObject();
    void gameReady();
    void drawObject();
    void updateObject(bool l, bool r, bool s);
    void checkCollision();
    void wallCollision();
    void brickCollision();
    void batCollision();
    void itemCollision(int c, int r);
    void drawIntersection(Vector2D* l2l, Vector2D* p2l, Vector2D *c2l, Vector2D *col);
    Vector2D* lineToLine(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4);
    Vector2D* pointToLine(Vector2D c, Vector2D v1, Vector2D v2);
    Vector2D* circleToLine(Vector2D l2l, Vector2D p2l);
};

