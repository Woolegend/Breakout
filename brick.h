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

#define		EMPTY			0;
#define		NORMAL			1;

class Brick {
public:
	int type;
	float scale;
	Vector2D center, vtx[4];

	Brick(int tp, float x, float y);

	void drawBrick();
};