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
	
	//init ball
	ball = new Ball(300, 50);	
	
	//init bat
	bat = new Bat(300, 35);
	
	//init walls
	/*
	wall_num = 6;
	wall[0] = new Wall(125, 1000, 875, 1000);
	wall[1] = new Wall(875, 1000, 1000, 500);
	wall[2] = new Wall(1000, 500, 875, 0);
	wall[3] = new Wall(875, 0, 125, 0);
	wall[4] = new Wall(125, 0, 0, 500);
	wall[5] = new Wall(0, 500, 125, 1000);
	*/
	
	wall_num = 4;
	wall[0] = new Wall(0, 900, 600, 900);
	wall[1] = new Wall(600, 900, 600, 0);
	wall[2] = new Wall(600, 0, 0, 0);
	wall[3] = new Wall(0, 0, 0, 900);
	
	
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
	glPushMatrix();
	glTranslatef(LEFT, BOTTOM, 0);
	ball->drawBall();
	bat->drawBat();
	//ball->drawDirection();
	
	for (int i = 0; i < wall_num; i++) {
		wall[i]->drawWall();
		wall[i]->drawNormal();
	}

	for (int i = 0; i < brick_num; i++) {
		//brick[i]->drawBrick();
	}
	glPopMatrix();
}

void Object::updateObject(bool L, bool R) {
	ball->update();
	bat->update(L, R);
}

void Object::checkCollision() {
	Vector2D *pos = NULL, *pTmp, nVec;
	float dis = 10000, dTmp;

	if (true) {
		for (int i = 0; i < wall_num; i++) {
			pTmp = checkIntersection(wall[i]);
			if (pTmp != NULL) {
				dTmp = (*pTmp - ball->center).scala();
				if (dTmp < dis) {
					dis = dTmp;
					pos = pTmp;
					nVec = wall[i]->normal;
				}
			}
		}
	}
	
	if (true) {
		pTmp = checkIntersection(*bat);
		if (pTmp != NULL) {
			dTmp = (*pTmp - ball->center).scala();
			if (dTmp < dis) {
				dis = dTmp;
				pos = pTmp;
				nVec.getNormalVector(bat->center - *pTmp);
				if(nVec.x * ball->direction.x < 0) nVec = nVec * Vector2D(-1, 1);
				if(nVec.y < 0 ) nVec = nVec * Vector2D(1, -1);
				nVec.normalizer();
			}
		}
	}
	if (false) {
		
	}

	drawDirections(pos, nVec);
	if (dis <= ball->radius) {
		printf("collision\n");
		ball->direction = ball->direction + 2 * nVec;
		ball->direction.normalizer();
	}
	
}

Vector2D* Object::checkIntersection(Wall* w) {
	Vector2D *l2l, *p2l, *c2l;
	float dis;
	l2l = lineToLine(w->start, w->end);
	if (l2l == NULL) return NULL;
	p2l = pointToLine(w->start, w->end);
	c2l = circleToLine(w->start, w->end , *l2l, *p2l);
	return c2l;
}

/*
Vector2D* Object::checkIntersection(Brick brick) {

}
*/

Vector2D* Object::checkIntersection(Bat b) {
	Vector2D *l2l, *p2l, *c2l;
	float dis;
	l2l = lineToLine(b.vtx[0], b.vtx[1]);
	if (l2l == NULL) return NULL;
	p2l = pointToLine(b.vtx[0], b.vtx[1]);
	c2l = circleToLine(b.vtx[0], b.vtx[1] , *l2l, *p2l);
	return c2l;
}

void Object::drawDirections(Vector2D *pos, Vector2D dir) {
	if (pos == NULL) return;
	glPushMatrix();
	glTranslatef(LEFT, BOTTOM, 0);
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	float	delta, theta;
	float	x, y;
	delta = 2 * PI / BALLSLICE;
	for (int i = 0; i < BALLSLICE; i++) {
		theta = delta * i;
		x = ball->radius * cos(theta) + pos->x;
		y = ball->radius * sin(theta) + pos->y;
		glVertex2f(x, y);
	}
	glEnd();

	dir = ball->direction + 2 * dir;
	dir.normalizer();
	dir = dir * 100;

	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex2f(ball->center.x, ball->center.y);
	glVertex2f(pos->x, pos->y);

	glVertex2f(pos->x, pos->y);
	glVertex2f(dir.x + pos->x, dir.y + pos->y);
	glEnd();
	glPopMatrix();
}

Vector2D* Object::lineToLine(Vector2D v1, Vector2D v2) {
	float
		x1 = ball->center.x,
		y1 = ball->center.y,
		x2 = ball->direction.x * 1000 + x1,
		y2 = ball->direction.y * 1000 + y1,
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
		x0 = ball->center.x,
		y0 = ball->center.y,
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

Vector2D* Object::circleToLine(Vector2D v1, Vector2D v2, Vector2D l2l, Vector2D p2l) {
	Vector2D tmp;
	float
		a2c = (ball->center - l2l).scala(),
		p2c = (ball->center - p2l).scala();
	tmp = l2l - ball->radius * a2c / p2c * ball->direction;
	if (tmp.x + 11 >= min(v1.x, v2.x) && tmp.x - 11 <= max(v1.x, v2.x) &&
		tmp.y + 11 >= min(v1.y, v2.y) && tmp.y - 11 <= max(v1.y, v2.y)) {
		return new Vector2D(tmp.x, tmp.y);
	}
}