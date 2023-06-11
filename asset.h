#ifndef __OPEN_GL_ICL_
#define __OPEN_GL_ICL_
//#include<OpenGL/OpenGL.h>
//#include<GLUT/GLUT.h>
#include<windows.h>
#include<GL/GL.h>
#include<GL/glut.h>
#endif

#include "init.h"

class Asset {
public:
	void drawBlockA(float x, float y);
	void drawBlockB(float x, float y);
	void drawPipe(float x, float y, int l, float a);
	void drawMush(float x, float y, float a);
	void drawFlower(float x, float y, float a);
	void drawStar(float x, float y, float a);
	void drawMarioIdle(float x, float y, bool f, int t);
	void drawMarioJump(float x, float y, bool f, int t);
	void drawMarioFall(float x, float y, bool f, int t);
	void drawLuigiMove(float x, float y, bool f, int t);
	void drawCoin(float x, float y);
	void drawNumber(float x, float y, int n);
	void drawCloud(float x, float y, int s);
	void drawWallCloud(float x, float y, float s);
	void drawFireBall(float x, float y, float a);
};