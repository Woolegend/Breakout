#define GL_SILENCE_DEPRECATION
#ifndef __OPEN_GL_ICL_
#define __OPEN_GL_ICL_
//#include<OpenGL/OpenGL.h>
//#include<GLUT/GLUT.h>
#include<windows.h>
#include<GL/GL.h>
#include<GL/glut.h>
#endif

#include "object.h"

Object obj;
bool clickSpace, isLDown, isRDown;

void init() {
    clickSpace = false;
    isLDown = false;
    isRDown = false;
}

void MyReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

void frameReset() {
    glClearColor(0.8, 0.8, 0.8, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderScene(void)
{
    frameReset();

    obj.drawObject();
    obj.checkCollision();
    obj.updateObject(isLDown, isRDown, clickSpace);
    clickSpace = false;

    Sleep(5);

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
        clickSpace = clickSpace ? false : true;
        break;
    case 'a':
    case 'A':
        break;
    case 's':
    case 'S':
        break;
    default:
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
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
