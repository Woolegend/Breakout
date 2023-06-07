#include "brick.h"
#include<ios>

Brick::Brick(int tp, float x, float y) {
	type = tp;
	scale = 40;
	float spc = 3;
	vtx[0].setVector(x * scale + spc, 900 - y * scale - spc);
	vtx[1].setVector((x + 1) * scale - spc, 900 - y * scale - spc);
	vtx[2].setVector((x + 1) * scale - spc, 900 - (y + 1) * scale + spc);
	vtx[3].setVector(x * scale + spc, 900 - (y + 1) * scale + spc);
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