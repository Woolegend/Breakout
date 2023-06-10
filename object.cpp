#include "object.h"
#include<ios>

int board[BRICK_COL][BRICK_ROW] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 2, 2, 2, 3, 3, 4, 3, 0, 0, 0, 0, 0},
	{0, 0, 0, 2, 3, 2, 3, 3, 3, 4, 3, 3, 3, 0, 0, 0},
	{0, 0, 0, 2, 3, 2, 2, 3, 3, 3, 4, 3, 3, 3, 0, 0},
	{0, 0, 0, 0, 2, 3, 3, 3, 3, 4, 4, 4, 4, 0, 0, 0},
	{0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 5, 1, 1, 5, 1, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 5, 1, 1, 5, 1, 1, 1, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 5, 5, 5, 5, 1, 1, 1, 1, 0, 0},
	{0, 0, 3, 3, 1, 5, 6, 5, 5, 6, 5, 1, 3, 3, 0, 0},
	{0, 0, 3, 3, 3, 5, 5, 5, 5, 5, 5, 3, 3, 3, 0, 0},
	{0, 0, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 0, 0},
	{0, 0, 0, 0, 5, 5, 5, 0, 0, 5, 5, 5, 0, 0, 0, 0},
	{0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0},
	{0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0}
};

Object::Object() {
	initObject();
}

void Object::initObject() {
	isPlay = false;
	isOver = false;
	isPause = false;
	life = 3;
	brick_num = 0;


	//init ball
	//init bat
	gameReady();

	//init walls
	wall[0] = new Wall(SCALE, HEIGHT, WIDTH - SCALE, HEIGHT);
	wall[1] = new Wall(WIDTH - SCALE, HEIGHT, WIDTH - SCALE, SCALE);
	wall[2] = new Wall(WIDTH - SCALE, SCALE, SCALE, SCALE);
	wall[3] = new Wall(SCALE, SCALE, SCALE, HEIGHT);

	float co = 32 * sqrt(2);
	float sz = 150;
	wall[4] = new Wall(0, 500 - co, sz, 500 - co + sz);
	wall[5] = new Wall(sz, 500 - co + sz, sz - co, 500 + sz);
	wall[6] = new Wall(sz - co, 500 + sz, 0, 500 + co);

	wall[7] = new Wall(900, 500 + co, 900 - sz + co, 500 + sz);
	wall[8] = new Wall(900 - sz + co, 500 + sz, 900 - sz, 500 - co + sz);
	wall[9] = new Wall(900 - sz, 500 - co + sz, 900, 500 - co);

	//init Bricks
	brick = new Brick * *[BRICK_COL];
	for (int i = 0; i < BRICK_COL; i++) {
		brick[i] = new Brick * [BRICK_ROW];
	}
	for (int i = 0; i < BRICK_COL; i++) {
		for (int j = 0; j < BRICK_ROW; j++) {
			if (board[i][j]) {
				brick_num++;
				brick[i][j] = new Brick(board[i][j], i, j);
			}
			else brick[i][j] = NULL;
		}
	}
}

void Object::gameReady() {
	isReady = true;
	ball = new Ball(WIDTH / 2, 80);
	bat = new Bat(WIDTH / 2, 50);
}

void Object::drawObject() {
	ball->draw();

	bat->draw();
	//bat->drawBounding();

	for (int i = 0; i < BRICK_COL; i++) {
		for (int j = 0; j < BRICK_ROW; j++) {
			if (brick[i][j] == NULL)
				continue;
			if (brick[i][j]->durability) {
				brick[i][j]->draw();
				brick[i][j]->drawBounding();
			}
		}
	}



	asset.drawPipe(0, 500, 30, -45);
	asset.drawPipe(900, 500, 30, 45);

	for (int i = 0; i < life; i++) {
		asset.drawMush((i + 1 + 0.5) * SCALE, HEIGHT - SCALE * 0.5, 0);
	}

	/*
	for (int i = 0; i < NUMOFWALL; i++) {
		wall[i]->draw();
		wall[i]->drawNormal();
	}
	*/

	for (int i = 0; i < 30; i++) {
		asset.drawBlockB(15, 15 + i * SCALE);
		asset.drawBlockB(885, 15 + i * SCALE);
		asset.drawBlockB(15 + i * SCALE, 15);
	}


}

void Object::updateObject(bool L, bool R, bool S) {
	static float dir_x = 0;
	// ���� �÷��� ��
	// ��Ʈ ��ġ �ֽ�ȭ
	// �� ��ġ �ֽ�ȭ
	if (isPlay) {
		if (S) {
			isPlay = false;
			isPause = true;
			return;
		}
		ball->update();
		bat->update(L, R);
		return;
	}
	if (isPause) {
		if (S) {
			isPlay = true;
			isPause = false;
			return;
		}
		return;
	}
	// ���� ���� �� �غ� �ܰ�
	// ���� ���� ���� ���� ���
	if (isReady) {
		// �����̽� �Է� ��
		// ���� ���� �÷��̷� ��ȯ
		if (S) {
			isReady = false;
			isPlay = true;
			dir_x = 0;
			return;
		}
		else {
			if (L) {
				if (dir_x > -0.9) dir_x -= 0.01;
			}
			if (R) {
				if (dir_x < 0.9) dir_x += 0.01;
			}
			ball->direction = Vector2D(dir_x, 1.0 - fabs(dir_x));
			ball->direction.normalizer();
			ball->drawDirection();
			return;
		}
	}
	
	// ���� ���� ��
	if (isOver) {
		return;
	}

	// ����� �Ҿ��� ��
	// ����� ������ ���
	// ���� ���¸� �غ� �ܰ�� ��ȯ
	if (life != 0) {
		if (S) gameReady();
		return;
	}
	// ����� ��� �Ҿ��� ���
	// ���� ����
	if (life == 0) {
		isOver = true;
		printf("gameover!!!\n");
		return;
	}
}

void Object::checkCollision() {
	if (!isPlay) return;
	wallCollision();
	brickCollision();
	batCollision();
}

void Object::wallCollision() {
	Vector2D* l2l = NULL, * p2l = NULL, * c2l = NULL, * col = NULL;
	float dis = 10000, tmp;
	int index = 0;
	for (int i = 0; i < NUMOFWALL; i++) {
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
			//drawIntersection(l2l, p2l, c2l, col);
		}
	}

	if (dis <= RADIUS) {
		if (index == 2) {
			isPlay = false;
			life--;
			return;
		}
		ball->direction = ball->direction + wall[index]->normal * 2;
		ball->direction.normalizer();
	}
}

void Object::brickCollision() {
	bool isCollision = false; // �浹 ����
	int c, r; // �浹 ������ �ε����� ����
	float 
		// �浹 ���� �ּ� �Ÿ�
		// ������ �浹 ��, ��� �浹�� ������ �Ÿ��� ����
		// �ټ��� ������ �浹 �� �Ÿ��� ���� ����� ������ �浹
		min = 80, 
		// ���� �߽ɰ� �������� �Ÿ�
		dis;	 
	//�浹 �� ���� ����
	Vector2D nVec;

	//��� ������ ��ġ�� �浹 ���� ����
	for (int i = 1; i < BRICK_COL - 1; i++) {
		for (int j = 1; j < BRICK_ROW - 1; j++) {

			//�浹 ������ ��ŵ�ϴ� ���
			
			// �ش� ��ǥ�� ���� ���� ���
			if (brick[i][j] == NULL) continue;

			// ������ ���� �ʹ� �� ���
			dis = (ball->center - brick[i][j]->center).scala();
			if (min < dis) continue;

			// ������ ��� ���� �ٸ� ������ �ѷ� ���� ���
			if (brick[i + 1][j] != NULL &&
				brick[i][j + 1] != NULL &&
				brick[i - 1][j] != NULL &&
				brick[i][j - 1] != NULL)
				continue;

			float
				cx = ball->center.x,
				cy = ball->center.y;

			// �浹 ���� ����
			// �浹 ���� ���� �����ΰ�?
			if (cx >= fmin(brick[i][j]->bvtx[0].x, brick[i][j]->bvtx[1].x) &&
				cx <= fmax(brick[i][j]->bvtx[0].x, brick[i][j]->bvtx[1].x) &&
				cy >= fmin(brick[i][j]->bvtx[2].y, brick[i][j]->bvtx[1].y) &&
				cy <= fmax(brick[i][j]->bvtx[2].y, brick[i][j]->bvtx[1].y)) {
				c = i, r = j;
				min = dis;

				// �浹 ���� ����
				// �� �� �浹
				if (cx >= fmin(brick[i][j]->vtx[0].x, brick[i][j]->vtx[1].x) &&
					cx <= fmax(brick[i][j]->vtx[0].x, brick[i][j]->vtx[1].x) &&
					cy > brick[i][j]->center.y) {
					isCollision = true;
					nVec = Vector2D(0, 1);
				}
				// ���� �� �浹
				else if (cy >= fmin(brick[i][j]->vtx[1].y, brick[i][j]->vtx[2].y) &&
					cy <= fmax(brick[i][j]->vtx[1].y, brick[i][j]->vtx[2].y) &&
					cx > brick[i][j]->center.x) {
					isCollision = true;
					nVec = Vector2D(1, 0);
				}
				// �Ʒ� �� �浹
				else if (cx >= fmin(brick[i][j]->vtx[2].x, brick[i][j]->vtx[3].x) &&
					cx <= fmax(brick[i][j]->vtx[2].x, brick[i][j]->vtx[3].x) &&
					cy < brick[i][j]->center.y) {
					isCollision = true;
					nVec = Vector2D(0, -1);
				}
				// ���� �� �浹
				else if (cy >= fmin(brick[i][j]->vtx[3].y, brick[i][j]->vtx[0].y) &&
					cy <= fmax(brick[i][j]->vtx[3].y, brick[i][j]->vtx[0].y) &&
					cx < brick[i][j]->center.x) {
					isCollision = true;
					nVec = Vector2D(-1, 0);
				}
				// �𼭸� �浹 ����
				else {
					// �� ��� �𼭸� �浹
					if (cx < brick[i][j]->center.x && cy > brick[i][j]->center.y 
						&&RADIUS >= (ball->center - brick[i][j]->vtx[0]).scala()) {
						printf("0\n");
						isCollision = true;
						nVec = Vector2D(-1, 1);
						nVec.normalizer();
					}
					// �� ��� �𼭸� �浹
					else if (cx > brick[i][j]->center.x && cy > brick[i][j]->center.y
						&& RADIUS >= (ball->center - brick[i][j]->vtx[1]).scala()) {
						printf("1\n");
						isCollision = true;
						nVec = Vector2D(1, 1);
						nVec.normalizer();
					}
					// �� �ϴ� �𼭸� �浹
					else if (cx > brick[i][j]->center.x && cy < brick[i][j]->center.y
						&& RADIUS >= (ball->center - brick[i][j]->vtx[2]).scala()) {
						printf("2\n");
						isCollision = true;
						nVec = Vector2D(1, -1);
						nVec.normalizer();
					}
					// �� �ϴ� �𼭸� �浹
					else if (cx < brick[i][j]->center.x && cy < brick[i][j]->center.y
						&& RADIUS >= (ball->center - brick[i][j]->vtx[3]).scala()) {
						printf("3 \n");
						isCollision = true;
						nVec = Vector2D(-1, -1);
						nVec.normalizer();
					}
					//�𼭸� ���� ���� ��
					else {
						min = 80;
					}
				}
			}
		}
	}

	//������ �浹 ��
	if (isCollision) {
		if (brick[c][r]->type == 0) {
			brick_num--;
			brick[c][r] = NULL;
		}
		ball->direction = ball->direction + 2 * nVec;
		ball->direction.normalizer();
	}
}

void Object::batCollision() {
	if (ball->center.y > (bat->center.y + bat->h + 10)) return;


	float cx = ball->center.x, cy = ball->center.y;
	if (cx >= bat->bvtx[0].x && cx <= bat->bvtx[1].x &&
		cy >= bat->bvtx[2].y && cy <= bat->bvtx[1].y) {
		Vector2D nVec;
		nVec = ball->center - bat->center;
		nVec.normalizer();

		ball->direction = ball->direction + 2 * nVec * Vector2D(0.5, 2);

		ball->direction.normalizer();
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
