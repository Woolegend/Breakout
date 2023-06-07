#include "brick.h"
#include<ios>

Brick::Brick(int t, float x, float y):type(t) {
	float space = 3;
	durability = 1;
	x = 220 + x * 2 * SCALE;
	y = 100 + y * 2 * SCALE;
	center = Vector2D(x, y);
	vtx[0] = Vector2D(x  - SCALE + space, HEIGHTOFVIEW - (y  + SCALE - space));
	vtx[1] = Vector2D(x  + SCALE - space, HEIGHTOFVIEW - (y  + SCALE - space));
	vtx[2] = Vector2D(x  + SCALE - space, HEIGHTOFVIEW - (y  - SCALE + space));
	vtx[3] = Vector2D(x  - SCALE + space, HEIGHTOFVIEW - (y  - SCALE + space));
}

void Brick::drawBrick() {
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(vtx[0].x, vtx[0].y);
	glVertex2f(vtx[1].x, vtx[1].y);
	glVertex2f(vtx[2].x, vtx[2].y);
	glVertex2f(vtx[3].x, vtx[3].y);
	glEnd();
}