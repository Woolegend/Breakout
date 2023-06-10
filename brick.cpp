#include "brick.h"
#include<ios>

float brick_color[][3] = {
    {235.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0},
    {136.0 / 255.0, 97.0 / 255.0, 45.0 / 255.0},
    {234.0 / 255.0, 195.0 / 255.0, 81.0 / 255.0},
    {0, 0, 0},
    {0, 29.0 / 255.0, 245.0 / 255.0}
};

Brick::Brick(int t, float y, float x){
    angle = 0;
    durability = 1;
    if (t > 5) {
        type = BRICK_ITEMBOX;
        if (t == 6) item = ITEM_MUSH;
        else if (t == 7) item = ITEM_FLOWER;
        else if (t == 8) item = ITEM_STAR;
        color = -1;
    }
    else {
        type = BRICK_NORMAL;
        item = ITEM_NONE;
        color = t - 1;
    }
    
    x = (WIDTH - BRICK_ROW * SCALE) / 2  + x * SCALE;
    y = HEIGHT - SCALE/2 - y * SCALE;
    center = Vector2D(x, y);
    init();
}

void Brick::init() {
    float hfScale = SCALE / 2;
    vtx[0] = Vector2D(center.x - hfScale, center.y + hfScale);
    vtx[1] = Vector2D(center.x + hfScale, center.y + hfScale);
    vtx[2] = Vector2D(center.x + hfScale, center.y - hfScale);
    vtx[3] = Vector2D(center.x - hfScale, center.y - hfScale);

    bvtx[0] = vtx[0] + Vector2D(-RADIUS, +RADIUS);
    bvtx[1] = vtx[1] + Vector2D(+RADIUS, +RADIUS);
    bvtx[2] = vtx[2] + Vector2D(+RADIUS, -RADIUS);
    bvtx[3] = vtx[3] + Vector2D(-RADIUS, -RADIUS);
}

void Brick::draw() {
    if (type == BRICK_NORMAL) {
        glBegin(GL_POLYGON);
        glColor3fv(brick_color[color]);
        glVertex2f(vtx[0].x, vtx[0].y);
        glVertex2f(vtx[1].x, vtx[1].y);
        glVertex2f(vtx[2].x, vtx[2].y);
        glVertex2f(vtx[3].x, vtx[3].y);
        glEnd();
        return;
    }
    if (type == BRICK_ITEMBOX) {
        asset.drawBlockA(center.x, center.y);
        return;
    }
    if (type == BRICK_ITEM) {
        if (center.y < -20) {
            delete[] this;
            return;
        }
        if (item == ITEM_MUSH) {
            asset.drawMush(center.x, center.y, angle);  
        }
        if (item == ITEM_STAR) {
            asset.drawStar(center.x, center.y, angle);
        }
        center = center + gravity;
        gravity.y -= 0.005;
        angle += 1;
        init();
        return;
        
    }
}

void Brick::drawBounding() {
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(bvtx[0].x, bvtx[0].y);
    glVertex2f(bvtx[1].x, bvtx[1].y);
    glVertex2f(bvtx[2].x, bvtx[2].y);
    glVertex2f(bvtx[3].x, bvtx[3].y);
    glEnd();
}

void Brick::collision() {
    durability--;
    if (durability < 1) {
        if (item != ITEM_NONE) {
            type = BRICK_ITEM;
            gravity = Vector2D(0, 1);
            return;
        }
        else {
            delete[] this;
        }
    }
    return;
}