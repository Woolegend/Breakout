#include "object.h"
#include<ios>

int board[BRICK_COL][BRICK_ROW] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 2, 2, 2, 3, 3, 4, 3, 0, 0, 0, 0},
    {0, 0, 2, 3, 2, 3, 3, 3, 4, 3, 3, 3, 0, 0},
    {0, 0, 2, 3, 2, 2, 3, 3, 3, 4, 3, 3, 3, 0},
    {0, 0, 0, 2, 3, 3, 3, 3, 4, 4, 4, 4, 0, 0},
    {0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 5, 1, 1, 5, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 5, 1, 1, 5, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 5, 5, 5, 5, 1, 1, 1, 1, 0},
    {0, 3, 3, 1, 5, 3, 5, 5, 3, 5, 1, 3, 3, 0},
    {0, 3, 3, 3, 5, 5, 5, 5, 5, 5, 3, 3, 3, 0},
    {0, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 0},
    {0, 0, 0, 5, 5, 5, 0, 0, 5, 5, 5, 0, 0, 0},
    {0, 0, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0},
    {0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
    wall_num = 10;
    wall[0] = new Wall(40, 1000, 960, 1000);
    wall[1] = new Wall(960, 1000, 960, 0);
    wall[2] = new Wall(960, 0, 40, 0);
    wall[3] = new Wall(40, 0, 40, 1000);
    
    float co = 32 * sqrt(2);
    float sz = 130;
    wall[4] = new Wall(0, 500 - co, sz, 500 - co + sz);
    wall[5] = new Wall(sz, 500 - co + sz, sz - co, 500 + sz);
    wall[6] = new Wall(sz - co, 500 + sz, 0, 500 + co);
    
    wall[7] = new Wall(1000, 500 + co, 1000 - sz + co, 500 + sz);
    wall[8] = new Wall(1000 - sz + co, 500 + sz, 1000 - sz, 500 - co + sz);
    wall[9] = new Wall(1000 - sz, 500 - co + sz, 1000, 500 - co);

    //init Bricks
    brick = new Brick**[BRICK_COL];
    for (int i = 0; i < BRICK_COL; i++) {
        brick[i] = new Brick*[BRICK_ROW];
    }
    for (int i = 0; i < BRICK_COL; i++) {
        for (int j = 0; j < BRICK_ROW; j++) {
            if (board[i][j]) {
                brick[i][j] = new Brick(board[i][j], i, j);
            }
            else brick[i][j] = NULL;
        }
    }
}

void Object::drawObject() {
    ball->drawBall();
    
    for (int i = 0; i < BRICK_COL; i++) {
        for (int j = 0; j < BRICK_ROW; j++) {
            if (brick[i][j] == NULL)
                continue;
            if (brick[i][j]->durability)
                brick[i][j]->draw();
        }
    }



    asset.drawPipe(0, 500, 30, -45);
    asset.drawPipe(1000, 500, 30, 45);

    glLineWidth(10);
    for (int i = 0; i < wall_num; i++) {
        wall[i]->draw();
        wall[i]->drawNormal();
    }
    glLineWidth(1);

    
    for (int i = 0; i < 25; i++) {
        asset.drawBlockB(20, 20 + i * 40);
        asset.drawBlockB(980, 20 + i * 40);
    }

   
}


void Object::updateObject(bool L, bool R) {
    ball->update();
    bat->update(L, R);
}


void Object::checkCollision() {
    wallCollision();
    brickCollision();
}


void Object::wallCollision(){
    Vector2D *l2l, *p2l, *c2l, *col;
    float dis = 10000, tmp;
    int index = 0;
    for (int i = 0; i < wall_num; i++) {
        l2l = lineToLine(
            ball->center,
            ball->direction * 10000 + ball->center,
            wall[i]->start,
            wall[i]->end);
        if (l2l == NULL) continue;
        p2l = pointToLine(ball->center, wall[i]->start, wall[i]->end);
        c2l = circleToLine(*l2l, *p2l);
        col = pointToLine(*c2l, wall[i]->start, wall[i]->end);
        tmp = (*col - ball->center).scala();
        if (tmp < dis) {
            dis = tmp;
            index = i;
            drawIntersection(l2l, p2l, c2l, col);
        }
    }
    if (dis <= RADIUS) {
        ball->direction = ball->direction + wall[index]->normal * 2;
        ball->direction.normalizer();
    }
}

void Object::brickCollision() {
    int c, r;
    float exc = 70, tmp;
    Vector2D nVec;
    for (int i = 1; i < BRICK_COL - 1; i++) {
        for (int j = 1; j < BRICK_ROW - 1; j++) {
            // no brick
            if (brick[i][j] == NULL) continue;
            // too fal
            tmp = (ball->center - brick[i][j]->center).scala();
            // fenced in brick
            if (tmp > exc) continue;
            if (brick[i + 1][j] != NULL &&
                brick[i][j + 1] != NULL &&
                brick[i - 1][j] != NULL &&
                brick[i][j - 1] != NULL)
                continue;

            float
                cx = ball->center.x,
                cy = ball->center.y;

            // in bounding box?
            if (cx >= fmin(brick[i][j]->bvtx[0].x, brick[i][j]->bvtx[1].x) &&
                cx <= fmax(brick[i][j]->bvtx[0].x, brick[i][j]->bvtx[1].x) &&
                cy >= fmin(brick[i][j]->bvtx[2].y, brick[i][j]->bvtx[1].y) &&
                cy <= fmax(brick[i][j]->bvtx[2].y, brick[i][j]->bvtx[1].y)){
                exc = tmp;
                c = i;
                r = j;

                glPointSize(5);
                glColor3f(1, 1, 1);
                glBegin(GL_POINTS);
                glVertex2f(brick[i][j]->center.x, brick[i][j]->center.y);
                glEnd();

                //up face
                if (cx >= fmin(brick[i][j]->vtx[0].x, brick[i][j]->vtx[1].x) &&
                    cx <= fmax(brick[i][j]->vtx[0].x, brick[i][j]->vtx[1].x) &&
                    cy > brick[i][j]->center.y) {
                    nVec = Vector2D(0, 1);
                }
                else if (cy >= fmin(brick[i][j]->vtx[1].y, brick[i][j]->vtx[2].y) &&
                    cy <= fmax(brick[i][j]->vtx[1].y, brick[i][j]->vtx[2].y) &&
                    cx > brick[i][j]->center.x) {
                    nVec = Vector2D(1, 0);
                }
                else if (cx >= fmin(brick[i][j]->vtx[2].x, brick[i][j]->vtx[3].x) &&
                    cx <= fmax(brick[i][j]->vtx[2].x, brick[i][j]->vtx[3].x) &&
                    cy < brick[i][j]->center.y) {
                    nVec = Vector2D(0, -1);
                }
                else if (cy >= fmin(brick[i][j]->vtx[3].y, brick[i][j]->vtx[0].y) &&
                    cy <= fmax(brick[i][j]->vtx[3].y, brick[i][j]->vtx[0].y) &&
                    cx < brick[i][j]->center.x) {
                    nVec = Vector2D(-1, 0);
                }
                else {
                    if (cx < brick[i][j]->center.x && cy > brick[i][j]->center.y) {
                        nVec = Vector2D(-1, 1);
                        nVec.normalizer();
                    }
                    else if (cx > brick[i][j]->center.x && cy > brick[i][j]->center.y) {
                        nVec = Vector2D(1, 1);
                        nVec.normalizer();
                    }
                    else if (cx > brick[i][j]->center.x && cy < brick[i][j]->center.y) {
                        nVec = Vector2D(1, -1);
                        nVec.normalizer();
                    }
                    else if (cx < brick[i][j]->center.x && cy < brick[i][j]->center.y) {
                        nVec = Vector2D(-1, -1);
                        nVec.normalizer();
                    }
                    else {
                        printf("exc in brick collision !!!!\n");
                    }
                }
            }
        }
    }
    if (exc < 70) {
        ball->direction = ball->direction + 2 * nVec;
        ball->direction.normalizer();
        brick[c][r] = NULL;
    }
}

void Object::drawIntersection(Vector2D* l2l, Vector2D* p2l, Vector2D* c2l, Vector2D* col) {
    glPointSize(5);
    glColor3f(0, 0, 1);
    glBegin(GL_POINTS);
    glVertex2f(l2l->x, l2l->y);
    glVertex2f(p2l->x, p2l->y);
    glVertex2f(c2l->x, c2l->y);
    glVertex2f(col->x, col->y);
    glEnd();

    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex2f(ball->center.x, ball->center.y);
    glVertex2f(l2l->x, l2l->y);

    glVertex2f(ball->center.x, ball->center.y);
    glVertex2f(p2l->x, p2l->y);
    glEnd();

    float    delta, theta;
    float    x, y;
    delta = 2 * PI / BALLSLICE;
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < BALLSLICE; i++) {
        theta = delta * i;
        x = RADIUS * cos(theta) + c2l->x;
        y = RADIUS * sin(theta) + c2l->y;
        glVertex2f(x, y);
    }
    glEnd();
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
