#ifndef __OPEN_GL_ICL_
#define __OPEN_GL_ICL_
#include<windows.h>
#include<GL/GL.h>
#include<GL/glut.h>
#endif

#ifndef __VECTOR2D_H_
#define __VECTOR2D_H_
#include "vector2D.h"
#endif

#define		PI				3.1415
#define		BALLSLICE		20

class Ball {
public:
	Vector2D center;
	Vector2D* vertex[BALLSLICE];
	Vector2D direction;
	float radius;
	float speed;

	Ball(float x, float y);
	void initVertex();
	void drawBall();
	void update();
	void drawDirection();
};