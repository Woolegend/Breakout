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
};