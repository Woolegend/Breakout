#include "bat.h"


Bat::Bat(float x, float y): center(x, y) {
    speed = 1, h = 5, w = 100;
    update(true, true);
}

void Bat::drawBat() {
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
}
