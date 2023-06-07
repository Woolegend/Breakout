#ifndef __OPEN_GL_ICL_
#define __OPEN_GL_ICL_
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


#include "init.h"

class Object {
	Ball* ball;
	Bat* bat;
	Wall* wall[NUMOFWALL];
	Brick* brick[BRICK_COL * BRICK_ROW];
	Vector2D L2L, P2L, C2L, NOR, COL;
	int brick_num, wall_num;
	float col_dis;
public:
	Object();
	void initObject();
	void drawObject();
	void updateObject(bool L, bool R);
};

