#include "ball.h"
#include<ios>

Ball::Ball(float x, float y) : center(x, y)
{
    speed = 2;
    star_time = 0;
    type = BALL_NORMAL;
    direction = Vector2D(0, 1);
    direction.normalizer();
}

void Ball::draw() {
    if (type == BALL_NONE) return;
    if (type == BALL_FIRE) {
        static int angle = 0;
        asset.drawFireBall(center.x, center.y, angle += 10);
        return;
    }
    int t = star_time ? BALL_STAR : type;
    if (direction.x < 0) {
        if(direction.y > 0){
            asset.drawMarioJump(center.x, center.y, true, t);
            return;
        }
        else {
            asset.drawMarioFall (center.x, center.y, true, t);
            return;
        }
    }
    else{
        if (direction.y > 0) {
            asset.drawMarioJump(center.x, center.y, false, t);
            return;
        }
        else {
            asset.drawMarioFall(center.x, center.y, false, t);
        return;
    }
    }
}

void Ball::update() {
    center = center + speed * direction;
    if(star_time) star_time--;
}

void Ball::setType(int t) {
    if (t == BALL_STAR) {
        star_time = 2000;
    }
    else if (t == BALL_FLOWER) {
        type = BALL_FLOWER;
    }
    else if (t == BALL_FIRE) {
        type = BALL_FIRE;
    }
    else if (t == BALL_NONE) {
        type = BALL_NONE;
    }
}


void Ball::drawDirection(){
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(center.x, center.y);
    glVertex2f(center.x + direction.x * 300, center.y + direction.y * 300);
    glEnd();
}


