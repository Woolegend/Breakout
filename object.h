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

#define		NUMOFWALL		4

class Object {
	Ball* ball;
	Wall* wall[NUMOFWALL];
public:
	Object();
	void initObject();
	void drawObject();
	void checkCollision();
	void collision(Wall* wall);
};