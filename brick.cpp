#include "brick.h"
#include<ios>

float brick_color[][3] = {
    {235.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0},
    {136.0 / 255.0, 97.0 / 255.0, 45.0 / 255.0},
    {234.0 / 255.0, 195.0 / 255.0, 81.0 / 255.0},
    {0, 0, 0},
    {0, 29.0 / 255.0, 245.0 / 255.0}
};

Brick::Brick(int t, float y, float x):type(t){
    float space = 0;
    float hfScale = SCALE / 2;
    durability = 1;
    color = type - 1;
    type = type > 5 ? type - 5 : 0;
    

    x = (WIDTH - BRICK_ROW * SCALE) / 2  + x * SCALE;
    y = HEIGHT - hfScale - y * SCALE;
    center = Vector2D(x, y);

    vtx[0] = Vector2D(x  - hfScale, y  + hfScale);
    vtx[1] = Vector2D(x  + hfScale, y  + hfScale);
    vtx[2] = Vector2D(x  + hfScale - space, y  - hfScale);
    vtx[3] = Vector2D(x  - hfScale + space, y  - hfScale);
    
    bvtx[0] = vtx[0] + Vector2D(-RADIUS, +RADIUS);
    bvtx[1] = vtx[1] + Vector2D(+RADIUS, +RADIUS);
    bvtx[2] = vtx[2] + Vector2D(+RADIUS, -RADIUS);
    bvtx[3] = vtx[3] + Vector2D(-RADIUS, -RADIUS);
}

void Brick::draw() {
    if (type == 0) {
        glBegin(GL_POLYGON);
        glColor3fv(brick_color[color]);
        glVertex2f(vtx[0].x, vtx[0].y);
        glVertex2f(vtx[1].x, vtx[1].y);
        glVertex2f(vtx[2].x, vtx[2].y);
        glVertex2f(vtx[3].x, vtx[3].y);
        glEnd();
    }
    if (type == 1) {
        asset.drawBlockA(center.x, center.y);
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
