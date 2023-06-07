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

#define		WIDTH			1200
#define		HEIGHT			1200
#define		LEFT			100
#define		BOTTOM			100
#define		NUMOFWALL		10
#define		BRICK_COL		5
#define		BRICK_ROW		15

class Object {
	Ball* ball;
	Bat* bat;
	Wall* wall[NUMOFWALL];
	Brick* brick[BRICK_COL * BRICK_ROW];
	int brick_num;
	int wall_num;
public:
	Object();
	void initObject();
	void drawObject();
	void updateObject(bool L, bool R);
	void drawDirections(Vector2D* pos, Vector2D dir);
	void checkCollision();
	Vector2D* checkIntersection(Wall* w);
	Vector2D* checkIntersection(Brick b);
	Vector2D* checkIntersection(Bat b);
	Vector2D* lineToLine(Vector2D v1, Vector2D v2);
	Vector2D* pointToLine(Vector2D v1, Vector2D v2);
	Vector2D* circleToLine(Vector2D v1, Vector2D v2, Vector2D l2l, Vector2D p2l);
};