#include "bat.h"


Bat::Bat(float x, float y): center(x, y) {
    speed = 1, h = 10, w = 100;
    update(true, true);
}

void Bat::draw() {
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(vtx[0].x, vtx[0].y);
    glVertex2f(vtx[1].x, vtx[1].y);
    glVertex2f(vtx[2].x, vtx[2].y);
    glVertex2f(vtx[3].x, vtx[3].y);
    glEnd();
}

void Bat::update(bool L, bool R) {
    if (L) center.x = center.x - speed;
    if (R) center.x = center.x + speed;

    vtx[0] = Vector2D(center.x - w, center.y + h);
    vtx[1] = Vector2D(center.x + w, center.y + h);
    vtx[2] = Vector2D(center.x + w, center.y - h);
    vtx[3] = Vector2D(center.x - w, center.y - h);

    bvtx[0] = vtx[0] + Vector2D(-RADIUS, +RADIUS);
    bvtx[1] = vtx[1] + Vector2D(+RADIUS, +RADIUS);
    bvtx[2] = vtx[2] + Vector2D(+RADIUS, -RADIUS);
    bvtx[3] = vtx[3] + Vector2D(-RADIUS, -RADIUS);
}

void Bat::drawBounding() {
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(bvtx[0].x, bvtx[0].y);
    glVertex2f(bvtx[1].x, bvtx[1].y);
    glVertex2f(bvtx[2].x, bvtx[2].y);
    glVertex2f(bvtx[3].x, bvtx[3].y);
    glEnd();
}