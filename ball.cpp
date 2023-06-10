#include "ball.h"
#include<ios>

Ball::Ball(float x, float y) : center(x, y)
{
    speed = 1.5;
    time = 0;
    type = BALL_NORMAL;
    direction = Vector2D(0, 1);
    direction.normalizer();
}

void Ball::draw() {
    if(direction.x < 0)
        asset.drawMarioJump(center.x, center.y, true, type);
    else
        asset.drawMarioJump(center.x, center.y, false, type);
}

void Ball::update() {
    center = center + speed * direction;
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
    else if (t == BALL_FLOWER) {
        type = BALL_FLOWER;
    }
}


void Ball::drawDirection(){
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(center.x, center.y);
    glVertex2f(center.x + direction.x * 300, center.y + direction.y * 300);
    glEnd();
}


