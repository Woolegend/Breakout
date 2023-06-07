#include "wall.h"

Wall::Wall()
{
	setDirection();
	setNormal();
}

Wall::Wall(float x1, float y1, float x2, float y2)
	:start(x1, y1), end(x2, y2)
{
	setDirection();
	setNormal();
}

void Wall::setDirection() {
	direction.setVector(&start, &end);
	length = direction.scala();
	direction.normalizer();
}

void Wall::setNormal() {
	normal.getNormalVector(direction);
	normal.normalizer();
}

void Wall::drawWall() {
	glPushMatrix();
	glTranslatef(start.x, start.y, 0);
	glBegin(GL_LINES);
	glLineWidth(10);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0, 0);
	glVertex2f(direction.x * length, direction.y * length);
	glEnd();
	glPopMatrix();
}

void Wall::drawNormal() {
	glPushMatrix();
	glTranslatef(start.x, start.y, 0);
	glTranslatef(direction.x * length * 0.5, direction.y * length * 0.5, 0);
	glBegin(GL_LINES);
	glLineWidth(10);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(0, 0);
	glVertex2f(normal.x * 100, normal.y * 100);
	glEnd();
	glPopMatrix();
}

void Wall::drawBoundingBox() {

}
