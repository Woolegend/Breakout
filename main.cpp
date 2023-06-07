#ifndef __OPEN_GL_ICL_
#define __OPEN_GL_ICL_
#include<windows.h>
#include<GL/GL.h>
#include<GL/glut.h>
#endif

#include "object.h"

Object obj;
bool isPause, isLDown, isRDown;
int speed;

void init() {
	isPause = false;
	isLDown = false;
	isRDown = false;
	speed = 5;
}

void MyReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTHOFVIEW, 0, HEIGHTOFVIEW);
}

void frameReset() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderScene(void) 
{
	if (isPause) return;
	frameReset();

	obj.drawObject();
	obj.updateObject(isLDown, isRDown);


	Sleep(speed);

	glutSwapBuffers();
	glFlush();
}

void MyKeyDown(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		isLDown = true;
		break;
	case GLUT_KEY_RIGHT:
		isRDown = true;
		break;
	default:
		break;
	}
}
void MyKeyUp(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		isLDown = false;
		break;
	case GLUT_KEY_RIGHT:
		isRDown = false;
		break;
	default:
		break;
	}
}
void MyKey(unsigned char key, int x, int y) {
	switch (key) {
	case ' ':
		isPause = isPause ? false : true;
		break;
	case 'a':
		if (speed > 2) speed -= 1;
		break;
	case 's':
		if (speed < 10) speed += 1;
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WIDTHOFVIEW, HEIGHTOFVIEW);
	glutCreateWindow("Breakout! Bat_and_Ball~");
	init();

	glutSpecialFunc(MyKeyDown);
	glutSpecialUpFunc(MyKeyUp);
	glutKeyboardFunc(MyKey);

	glutReshapeFunc(MyReshape);
	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);
	glutMainLoop();
	return 0;
}