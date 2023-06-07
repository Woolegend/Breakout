#include "object.h"
#include<ios>

int board[BRICK_COL][BRICK_ROW] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


Object::Object() {
	initObject();
}

void Object::initObject() {
	ball = new Ball(400, 100);	
	bat = new Bat(300, 35);

	wall[0] = new Wall(0, 0, 0, 900);
	wall[1] = new Wall(0, 900, 600, 900);
	wall[2] = new Wall(600, 900, 600, 0);
	wall[3] = new Wall(600, 0, 0, 0);

	/*
	wall[0] = new Wall(125, 1000, 875, 1000);
	wall[1] = new Wall(875, 1000, 1000, 500);
	wall[2] = new Wall(1000, 500, 875, 0);
	wall[3] = new Wall(875, 0, 125, 0);
	wall[4] = new Wall(125, 0, 0, 500);
	wall[5] = new Wall(0, 500, 125, 1000);
	*/

	brick_num = 0;
	for (int h = 0; h < BRICK_COL; h++) {
		for (int w = 0; w < BRICK_ROW; w++) {
			if (board[h][w]) brick_num++;
			brick[h * BRICK_ROW + w] = new Brick(board[h][w], w, h);
		}
	}
}

void Object::drawObject() {
	glPushMatrix();
	glTranslatef(LEFT, BOTTOM, 0);
	ball->drawBall();
	bat->drawBat();
	//ball->drawDirection();
	Vector2D L2L, P2L, C2L, nor;
	Vector2D *tmp;
	for (int i = 0; i < NUMOFWALL; i++) {
		wall[i]->drawWall();
		wall[i]->drawNormal();
	}
	for (int i = 0; i < brick_num; i++) {
		brick[i]->drawBrick();
	}

	//wall
	for (int i = 0; i < NUMOFWALL; i++) {
		tmp = lineToLine(wall[i]->start, wall[i]->end);
		if (tmp != NULL) {
			L2L.setVector(tmp);
			P2L.setVector(pointToLine(wall[i]->start, wall[i]->end));
			nor = wall[i]->normal;
		}
	}

	//bat
	tmp = lineToLine(bat->vtx[0], bat->vtx[1]);
	if (tmp != NULL) {
		L2L.setVector(tmp);
		P2L.setVector(pointToLine(bat->vtx[0], bat->vtx[1]));
		nor.getNormalVector((bat->vtx[1] - bat->vtx[0]) * -1);
		nor.normalizer();
		
	}

	//brick
	for (int i = 0; i < brick_num; i++) {
		for (int j = 0; j < 4; j++) {
			tmp = lineToLine(brick[i]->vtx[j], brick[i]->vtx[(j+1)%3]);
			if (tmp != NULL) {
				L2L.setVector(tmp);
				P2L.setVector(pointToLine(brick[i]->vtx[j], brick[i]->vtx[(j + 1) % 3]));
				nor.getNormalVector(brick[i]->vtx[j] - brick[i]->vtx[(j + 1) % 3]);
				break;
			}
		}
	}

	collision(P2L, nor);
	drawDirections(L2L, P2L, nor);
	glPopMatrix();
}

void Object::updateObject(bool L, bool R) {
	ball->update();
	bat->update(L, R);
}

void Object::drawDirections(Vector2D l2l, Vector2D p2l, Vector2D nor) {
	Vector2D dir;
	dir = nor * 2 + ball->direction;
	dir.normalizer();
	dir = dir * 100 + l2l;

	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex2f(ball->center.x, ball->center.y);
	glVertex2f(l2l.x, l2l.y);

	glVertex2f(ball->center.x, ball->center.y);
	glVertex2f(p2l.x, p2l.y);

	glVertex2f(l2l.x, l2l.y);
	glVertex2f(dir.x, dir.y);
	glEnd();

	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex2f(p2l.x, p2l.y);
	glColor3f(0, 0, 1);
	glVertex2f(l2l.x, l2l.y);
	glEnd();
}

void Object::collision(Vector2D p2l, Vector2D nor) {
	float distance = (p2l - ball->center).scala();
	if (distance <= ball->radius) {
		ball->direction = ball->direction + (nor * 2);
		ball->direction.normalizer();
	}
}

Vector2D* Object::lineToLine(Vector2D v1, Vector2D v2) {
	float
		x1 = ball->center.x,
		y1 = ball->center.y,
		x2 = ball->direction.x * 10000 + x1,
		y2 = ball->direction.y * 10000 + y1,
		x3 = v1.x,
		y3 = v1.y,
		x4 = v2.x,	
		y4 = v2.y,
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
		if (x + 1 >= min(x1, x2) && x - 1 <= max(x1, x2) &&
			x + 1 >= min(x3, x4) && x - 1 <= max(x3, x4) &&
			y + 1 >= min(y1, y2) && y - 1 <= max(y1, y2) &&
			y + 1 >= min(y3, y4) && y - 1 <= max(y3, y4)) {		
			return new Vector2D(x, y);
		}
		return NULL;
	}
	return NULL;
}

Vector2D* Object::pointToLine(Vector2D v1, Vector2D v2) {
	float
		x = ball->center.x,
		y = ball->center.y,
		lx1 = v2.x,
		ly1 = v2.y,
		lx2 = v1.x,
		ly2 = v1.y,
		a = ly2 - ly1,
		b = lx2 - lx1,
		c1 = a * lx1 + b * ly1,
		c2 = -b * x + a * y,
		det = a * a + b * b,
		cx = 0,
		cy = 0;
	if (det != 0) {
		cx = (a * c1 - b * c2) / det;
		cy = (a * c2 + b * c1) / det;
	}
	else {
		cx = x;
		cy = y;
	}
	return new Vector2D(cx, cy);
}

// Vector2D* Object::circleToLine(Vector2D l2l, Vector2D p2l) {}