#include "wall.h"

Wall::Wall(){}

Wall::Wall(float x1, float y1, float x2, float y2)
    :start(x1, y1), end(x2, y2)
{
    direction =end - start;
    length = direction.scala();
    direction.normalizer();
    normal.getNormalVector(direction);
    normal.normalizer();
}

void Wall::draw(){
    glPushMatrix();
    glTranslatef(start.x, start.y, 0);
    
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(direction.x * length, direction.y * length);
    glEnd();
    
    glPopMatrix();
}

void Wall::drawNormal(){
    glPushMatrix();
    glTranslatef(start.x, start.y, 0);
    glTranslatef(direction.x * length * 0.5, direction.y * length * 0.5, 0);
    
    glColor3f(1, 0, 0);
    glPointSize(10);
    glBegin(GL_POINTS);
        glVertex2f(0, 0);
    glEnd();
    
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(normal.x * 100, normal.y * 100);
    glEnd();
    
    glPopMatrix();

    
}
