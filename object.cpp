#include "object.h"
#include<ios>

int board[BRICK_COL][BRICK_ROW] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

Object::Object() {
    initObject();
}

void Object::initObject() {

    //init ball
    ball = new Ball(300, 50);

    //init bat
    bat = new Bat(300, 35);

    //init walls
    wall_num = 4;
    wall[0] = new Wall(0, 1000, 1000, 1000);
    wall[1] = new Wall(1000, 1000, 1000, 0);
    wall[2] = new Wall(1000, 0, 0, 0);
    wall[3] = new Wall(0, 0, 0, 1000);


    //init Bricks
    brick_num = 0;
    for (int h = 0; h < BRICK_COL; h++) {
        for (int w = 0; w < BRICK_ROW; w++) {
            if (board[h][w]) brick_num++;
            brick[h * BRICK_ROW + w] = new Brick(board[h][w], w, h);
        }
    }
}

void Object::drawObject() {
    ball->drawBall();

    for (int i = 0; i < wall_num; i++) {
        wall[i]->draw();
        wall[i]->drawNormal();
    }

    for (int i = 0; i < brick_num; i++) {
        if(brick[i]->durability)
            brick[i]->drawBrick();
    }
    
    for (int i = 0; i < brick_num; i++) {
        if(brick[i]->durability)
            brick[i]->drawBounding();
        
    }
}

void Object::updateObject(bool L, bool R) {
    ball->update();
    bat->update(L, R);
}

void Object::wallCollision(int index){
    Vector2D *l2l, *p2l, *c2l, *col;
    float dis = 10000, tmp;
    for(int i = 0; i<wall_num; i++){
        l2l = lineToLine(ball->center, ball->direction * 1000 + ball->center,
                         wall[index]->start, wall[index]->end);
        if(l2l == NULL) continue;
        p2l = pointToLine(ball->center, wall[index]->start, wall[index]->end);
        c2l = circleToLine(*l2l, *p2l);
        tmp = (*c2l - ball->center).scala();
        if(tmp < dis){
            tmp = dis;
            col = pointToLine(*c2l, wall[index]->start, wall[index]->end);
        }
    }
}

Vector2D* Object::lineToLine(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4) {
    float
        x1 = v1.x,
        y1 = v1.y,
        x2 = v2.x,
        y2 = v2.y,
        x3 = v3.x,
        y3 = v3.y,
        x4 = v4.x,
        y4 = v4.y,
        a1 = y2 - y1,
        a2 = y4 - y3,
        b1 = x1 - x2,
        b2 = x3 - x4,
        c1 = a1 * x1 + b1 * y1,
        c2 = a2 * x3 + b2 * y3,
        det = a1 * b2 - a2 * b1;
    if (det != 0) {
        float
            x = (b2 * c1 - b1 * c2) / det,
            y = (a1 * c2 - a2 * c1) / det;
        if (x + 1 >= fmin(x1, x2) && x - 1 <= fmax(x1, x2) &&
            x + 1 >= fmin(x3, x4) && x - 1 <= fmax(x3, x4) &&
            y + 1 >= fmin(y1, y2) && y - 1 <= fmax(y1, y2) &&
            y + 1 >= fmin(y3, y4) && y - 1 <= fmax(y3, y4)) {
            return new Vector2D(x, y);
        }
        return NULL;
    }
    return NULL;
}

Vector2D* Object::pointToLine(Vector2D c, Vector2D v1, Vector2D v2) {
    float
        x0 = c.x,
        y0 = c.y,
        lx1 = v2.x,
        ly1 = v2.y,
        lx2 = v1.x,
        ly2 = v1.y,
        a = ly2 - ly1,
        b = lx1 - lx2,
        c1 = a * lx1 + b * ly1,
        c2 = (b * -1) * x0 + a * y0,
        det = a * a + b * b,
        cx = 0,
        cy = 0;
    if (det != 0) {
        cx = (a * c1 - b * c2) / det;
        cy = (a * c2 + b * c1) / det;
    }
    else {
        cx = x0;
        cy = y0;
    }
    return new Vector2D(cx, cy);
}

Vector2D* Object::circleToLine(Vector2D l2l, Vector2D p2l) {
    Vector2D tmp;
    float
        a2c = (ball->center - l2l).scala(),
        p2c = (ball->center - p2l).scala();
    tmp = l2l - RADIUS * a2c / p2c * ball->direction;
    return new Vector2D(tmp.x, tmp.y);
}
