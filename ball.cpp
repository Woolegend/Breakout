#include "ball.h"
#include<ios>

Ball::Ball(float x, float y) : center(x, y)
{
    speed = 1;
    time = 0;
    type = BALL_NORMAL;
    direction = Vector2D(0, 1);
    direction.normalizer();
    initVertex();
}

void Ball::initVertex() {
    float    delta, theta;
    float    x, y;
    delta = 2 * PI / BALLSLICE;
    for (int i = 0; i < BALLSLICE; i++) {
        theta = delta * i;
        x = RADIUS * cos(theta);
        y = RADIUS * sin(theta);
        vertex[i] = new Vector2D(x, y);
    }
}

void Ball::draw() {
    glPushMatrix();
    glTranslatef(center.x, center.y, 0);
    glBegin(GL_POLYGON);
    if (type == BALL_STAR) glColor3f(1.0, 0.0, 0.0);
    else glColor3f(1.0, 1.0, 0.0);
    for (int i = 0; i < BALLSLICE; i++)
        glVertex2f(vertex[i]->x, vertex[i]->y);
    glEnd();
    glPopMatrix();
}

void Ball::update() {
    center = center + speed * direction;
    if (-0.05 < direction.y && direction.y < 0.05) {
        direction.y = 0.5;
        direction.x *= 0.5;
        direction.normalizer();
    }
    if (time) {
        if (--time == 0) {
            type = BALL_NORMAL;
        }
    }
}

void Ball::setType(int t) {
    if (t == BALL_STAR) {
        type = BALL_STAR;
        time = 2000;
    }
}


void Ball::drawDirection(){
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(center.x, center.y);
    glVertex2f(center.x + direction.x * 300, center.y + direction.y * 300);
    glEnd();
}


