#include "ball.h"

Ball::Ball(float x, float y) : center(x, y)
{
	radius = 10;
	speed = 5;
	direction = new Vector2D(1, 1);
	direction->normalizer();
	initVertex();
}

void Ball::initVertex() {
	float	delta, theta;
	float	x, y;
	delta = 2 * PI / BALLSLICE;
	for (int i = 0; i < BALLSLICE; i++) {
		theta = delta * i;
		x = radius * cos(theta);
		y = radius * sin(theta);
		vertex[i] = new Vector2D(x, y);
	}
}

void Ball::drawBall() {
	glPushMatrix();
	glTranslatef(center.x, center.y, 0);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
	for (int i = 0; i < BALLSLICE; i++)
		glVertex2f(vertex[i]->x, vertex[i]->y);
	glEnd();
	glPopMatrix();
}

void Ball::update() {
	center.addVector(direction, speed);
}


void Ball::drawDirection(){
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(center.x, center.y);
	glVertex2f(center.x + direction->x * 1000, center.y + direction->y * 1000);

	glVertex2f(center.x, center.y);
	glVertex2f(center.x + direction->x * 1000, center.y);

	glVertex2f(center.x, center.y);
	glVertex2f(center.x, center.y + direction->y * 1000);
	glEnd();
}