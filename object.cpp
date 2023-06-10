#include "object.h"
#include<ios>

//마리오 게임 보드
int board[BRICK_COL][BRICK_ROW] = {
	// 모서리 인덱스는 0으로 고정
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 2, 1, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 3, 2, 1, 2, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 3, 3, 4, 1, 3, 1, 1, 4, 4, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1, 1, 4, 4, 3, 3, 1, 1, 1, 4, 0 ,0, 0, 0},
	{0, 0, 0, 0, 3, 4, 4, 5, 5, 4, 4, 4, 4, 5, 2, 1, 3, 3, 0, 0},
	{0, 0, 0, 0, 3, 3, 5, 6, 7, 4, 3, 3, 4, 4, 4, 3, 3, 7, 3, 0},
	{0, 0, 0, 0, 1, 7, 6, 6, 7, 4, 3, 1, 3, 3, 3, 3, 3, 3, 3, 0},
	{0, 0, 0, 0, 6, 7, 7, 6, 7, 7, 3, 3, 1, 5, 1, 5, 1, 5, 0, 0},
	{0, 0, 0, 7, 6, 6, 7, 7, 8, 7, 7, 3, 3, 3, 3, 3, 3, 0, 0, 0},
	{0, 0, 6, 7, 7, 6, 6, 8, 8, 8, 7, 7, 7, 7, 7, 7, 6, 7, 0, 0},
	{0, 0, 6, 6, 7, 7, 8, 8, 6, 3, 3, 3, 3, 3, 3, 6, 7, 7, 0, 0},
	{0, 0, 5, 6, 6, 6, 5, 6, 6, 3, 3, 3, 3, 3, 3, 7, 7, 6, 6, 0},
	{0, 6, 0, 5, 6, 5, 8, 8, 8, 6, 6, 6, 6, 6, 6, 8, 6, 6, 5 ,0},
	{0, 6, 6, 6, 8, 8, 6, 6, 6, 8, 3, 3, 3, 3, 3, 8 ,6, 5, 0, 0},
	{0, 0, 6, 6, 8 ,6, 6, 6, 6, 8, 6, 6, 6, 6, 8, 6, 6, 0, 0, 0},
	{0, 0, 0, 6, 8, 6, 6, 6, 6, 8, 8, 3, 3, 8, 6, 6, 6, 0, 0, 0},
	{0, 0, 0, 0, 0, 6, 5, M, 5, F, 0, 0, 0, 6, 6, S, 5, 6, 5, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

};

Object::Object() {
	gameReady();
	initObject();
}

void Object::initObject() {
	isPlay = false;
	isOver = false;
	isPause = false;
	coin = 0;
	life = 3;
	brick_num = 0;

	wall[0] = new Wall(SCALE, HEIGHT, WIDTH - SCALE, HEIGHT);
	wall[1] = new Wall(WIDTH - SCALE, HEIGHT, WIDTH - SCALE, SCALE);
	wall[2] = new Wall(WIDTH - SCALE, SCALE, SCALE, SCALE);
	wall[3] = new Wall(SCALE, SCALE, SCALE, HEIGHT);

	float co = 32 * sqrt(2);
	float sz = 100;	
	float jp = 16;
	// 좌측 상단 파이프 생성
	wall[4] = new Wall(co + sz, 900 - sz, co, 900);
	wall[5] = new Wall(0, 900 - co, sz, 900 - sz - co);
	wall[6] = new Wall(sz - jp, 900 - sz - co + jp, co + sz - jp, 900 - sz + jp);
	// 우측 상단 파이프 생성
	wall[7] = new Wall(900 - co, 900, 900 - co - sz, 900 - sz);
	wall[8] = new Wall(900 - sz, 900 - co - sz, 900, 900 - co);
	wall[9] = new Wall(900 - co - sz + jp, 900 - sz + jp, 900 - sz + jp, 900 - co - sz + jp);


	sz = 80;
	jp = 64;
	// 좌측 하단 파이프 생성
	wall[10] = new Wall(sz, 450 + co - sz, 0, 450 + co);
	wall[11] = new Wall(sz - jp, 450 - sz - co + jp, co + sz - jp, 450 - sz + jp);

	// 우측 하단 파이프 생성
	wall[12] = new Wall(900, 450 + co, 900 - sz, 450 + co - sz);
	wall[13] = new Wall(900 - co - sz + jp, 450 - sz + jp, 900 - sz + jp, 450 - co - sz + jp);


	brick = new Brick * *[BRICK_COL];
	for (int i = 0; i < BRICK_COL; i++) {
		brick[i] = new Brick * [BRICK_ROW];
	}

	// board[i][j] = N
	// N = 0		: 빈 공간
	// N = 1 ~ 5	: 일반 벽돌 
	// N = 6 ~ 8	: 아이템 박스
	for (int i = 0; i < BRICK_COL; i++) {
		for (int j = 0; j < BRICK_ROW; j++) {
			if (board[i][j]) {
				brick[i][j] = new Brick(board[i][j], i, j);
				if (brick[i][j]->type == BRICK_NORMAL)
					brick_num++;
			}
			else brick[i][j] = NULL;
		}
	}
}

// 게임 상태 [준비 단계]로 전환
void Object::gameReady() {
	isReady = true;
	// 공 위치 초기화
	ball = new Ball(WIDTH / 2, 150);
	// 배트 위치 초기화
	bat = new Bat(WIDTH / 2, 50);
}

// 생성된 오브젝트 그리기
void Object::drawObject() {

	//공 그리기
	ball->draw();
	//배트 그리기
	bat->drawBounding();
	if (pipe_time) {
		asset.drawPipe(
			bat->center.x, 
			bat->center.y, 
			pipe_time / 5, 
			pipe_angle);
		pipe_time--;
	}
	bat->draw();

	//벽돌 그리기
	for (int i = 0; i < BRICK_COL; i++) {
		for (int j = 0; j < BRICK_ROW; j++) {
			if (brick[i][j] == NULL)
				continue;
			brick[i][j]->draw();
		}
	}

	//사선 파이프 그리기
	asset.drawPipe(0, 900, 30, -135);
	asset.drawPipe(900, 900, 30, 135);
	asset.drawPipe(0, 450, 10, -135);
	asset.drawPipe(900, 450, 10, 135);

	//목숨 개수 그리기
	for (int i = 0; i < life; i++) {
		asset.drawMush((i + 1 + 0.5) * SCALE, HEIGHT - SCALE * 0.5, 0);
	}
	
	//벽면 그리기
	for (int i = 0; i < 30; i++) {
		asset.drawBlockB(15, 15 + i * SCALE);
		asset.drawBlockB(885, 15 + i * SCALE);
		asset.drawBlockB(15 + i * SCALE, 15);
	}

	asset.drawCoin(760, 880);
	asset.drawNumber(790, 883, coin/100);
	asset.drawNumber(820, 883, coin%100/10);
	asset.drawNumber(850, 883, coin%10);
}

void Object::updateObject(bool l, bool r, bool s) {
	static float dir_x = 0;
	if (isPlay) {
		if (s) {
			isPlay = false;
			isReady = false;
			life--;
			return;
		}
		ball->update();
		bat->update(l, r);
		return;
	}
	if (isPause) {
		if (s) {
			isPlay = true;
			isPause = false;
			return;
		}
		return;
	}
	if (isReady) {
		if (s) {
			isReady = false;
			isPlay = true;
			dir_x = 0;
			return;
		}
		else {
			if (l) {
				if (dir_x > -0.6) dir_x -= 0.01;
			}
			if (r) {
				if (dir_x < 0.6) dir_x += 0.01;
			}
			ball->direction = Vector2D(dir_x, 1.0 - fabs(dir_x));
			ball->drawDirection();
			ball->direction.normalizer();
			ball->center = bat->center + 100 * ball->direction;
			pipe_time = 100;
			pipe_angle = ball->direction.x * -69;
			return;
		}
	}
	if (isOver) {
		return;
	}
	if (life != 0) {
		if (s) gameReady();
		return;
	}
	if (life == 0) {
		isOver = true;
		return;
	}
}

void Object::checkCollision() {
	//게임 상태 [게임 단계]일 때 확인
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
			drawIntersection(l2l, p2l, c2l, col);
		}
	}

	if (dis <= RADIUS) {
		if (index == 2) {
			isPlay = false;
			life--;
			return;
		}
		if (index == 6) {
			ball->center = Vector2D(855, 395);
			ball->direction = Vector2D(-1, -1);
			return;
		}
		if (index == 9) {
			ball->center = Vector2D(55, 395);
			ball->direction = Vector2D(1, -1);
			return;
		}
		if (index == 11) {
			ball->center = Vector2D(120, 780);
			ball->direction = Vector2D(1, -1);
			return;
		}
		if (index == 13) {
			ball->center = Vector2D(780, 780);
			ball->direction = Vector2D(-1, -1);
			return;
		}
		else {
			ball->direction = ball->direction + wall[index]->normal * 1.5;
			ball->direction.normalizer();
		}
	}
}
 
void Object::brickCollision() {
	bool isCollision = false; 
	int c, r,
		collision_point = -1;
	float
		min = 80,
		dis;
	Vector2D nVec;
	for (int i = 1; i < BRICK_COL - 1; i++) {
		for (int j = 1; j < BRICK_ROW - 1; j++) {
			if (brick[i][j] == NULL) continue;
			if (brick[i][j]->type == BRICK_ITEM) {
				itemCollision(i, j);
				continue;
			}
			dis = (ball->center - brick[i][j]->center).scala();
			if (min < dis) continue;

			float
				cx = ball->center.x,
				cy = ball->center.y;

			if (cx >= fmin(brick[i][j]->bvtx[0].x, brick[i][j]->bvtx[1].x) &&
				cx <= fmax(brick[i][j]->bvtx[0].x, brick[i][j]->bvtx[1].x) &&
				cy >= fmin(brick[i][j]->bvtx[2].y, brick[i][j]->bvtx[1].y) &&
				cy <= fmax(brick[i][j]->bvtx[2].y, brick[i][j]->bvtx[1].y)) {
				c = i, r = j;
				
				if (ball->type == BALL_STAR) {
					isCollision = true;
					nVec = Vector2D();
					continue;
				}

				min = dis;

				// 윗 면 충돌
				if (cx >= fmin(brick[i][j]->vtx[0].x, brick[i][j]->vtx[1].x) &&
					cx <= fmax(brick[i][j]->vtx[0].x, brick[i][j]->vtx[1].x) &&
					cy > brick[i][j]->center.y) {
					isCollision = true;
					collision_point = BRICK_TOP;
					nVec = ball->center - brick[i][j]->center;
					nVec.normalizer();
				}
				// 우측 면 충돌
				else if (cy >= fmin(brick[i][j]->vtx[1].y, brick[i][j]->vtx[2].y) &&
					cy <= fmax(brick[i][j]->vtx[1].y, brick[i][j]->vtx[2].y) &&
					cx > brick[i][j]->center.x) {
					isCollision = true;
					collision_point = BRICK_RIGHT;
					nVec = ball->center - brick[i][j]->center;
					nVec.normalizer();
				}
				// 아랫 면 충돌
				else if (cx >= fmin(brick[i][j]->vtx[2].x, brick[i][j]->vtx[3].x) &&
					cx <= fmax(brick[i][j]->vtx[2].x, brick[i][j]->vtx[3].x) &&
					cy < brick[i][j]->center.y) {
					isCollision = true;
					collision_point = BRICK_BOTTOM;
					nVec = ball->center - brick[i][j]->center;
					nVec.normalizer();
				}
				// 좌측 면 충돌
				else if (cy >= fmin(brick[i][j]->vtx[3].y, brick[i][j]->vtx[0].y) &&
					cy <= fmax(brick[i][j]->vtx[3].y, brick[i][j]->vtx[0].y) &&
					cx < brick[i][j]->center.x) {
					isCollision = true;
					collision_point = BRICK_LEFT;
					nVec = ball->center - brick[i][j]->center;
					nVec.normalizer();
				}
				// 모서리 충돌 판정
				else {
					// 좌 상단 모서리 충돌
					if (cx < brick[i][j]->center.x && cy > brick[i][j]->center.y
						&& RADIUS >= (ball->center - brick[i][j]->vtx[0]).scala()) {
						isCollision = true;
						collision_point = BRICK_LEFT_TOP;
						nVec = ball->center - brick[i][j]->center;
						nVec.normalizer();
					}
					// 우 상단 모서리 충돌
					else if (cx > brick[i][j]->center.x && cy > brick[i][j]->center.y
						&& RADIUS >= (ball->center - brick[i][j]->vtx[1]).scala()) {
						isCollision = true;
						collision_point = BRICK_RIGHT_TOP;
						nVec = ball->center - brick[i][j]->center;
						nVec.normalizer();
					}
					// 우 하단 모서리 충돌
					else if (cx > brick[i][j]->center.x && cy < brick[i][j]->center.y
						&& RADIUS >= (ball->center - brick[i][j]->vtx[2]).scala()) {
						isCollision = true;
						collision_point = BRICK_RIGHT_BOTTOM;
						nVec = ball->center - brick[i][j]->center;
						nVec.normalizer();
					}
					// 좌 하단 모서리 충돌
					else if (cx < brick[i][j]->center.x && cy < brick[i][j]->center.y
						&& RADIUS >= (ball->center - brick[i][j]->vtx[3]).scala()) {
						isCollision = true;
						collision_point = BRICK_LFET_BOTTOM;
						nVec = ball->center - brick[i][j]->center;
						nVec.normalizer();
					}
					else { min = 80; }
				}
			}
		}

		if (isCollision) {
			// 기본 벽돌
			if (brick[c][r]->type == BRICK_NORMAL) {
				brick_num--;
				brick[c][r]->collision();
				coin++;
			}
			// 아이템 박스
			else if (brick[c][r]->type == BRICK_ITEMBOX) {
				if (collision_point == BRICK_BOTTOM ||
					ball->type == BALL_STAR) {
					brick[c][r]->collision();
				}
			}
			ball->direction = ball->direction + 2 * nVec ;
			ball->direction.normalizer();
		}
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

		ball->direction = nVec * Vector2D(0.3, 1);
		ball->direction.normalizer();
	}
}

void Object::itemCollision(int c, int r) {
	float
		cx = brick[c][r]->center.x,
		cy = brick[c][r]->center.y;
	if (cx >= bat->bvtx[0].x && cx <= bat->bvtx[1].x 
		&& cy >= bat->bvtx[2].y && cy <= bat->bvtx[1].y) {
		if (brick[c][r]->item == ITEM_MUSH) {
			life++;
		}
		if (brick[c][r]->item == ITEM_FLOWER) {
			ball->setType(BALL_FLOWER);
		}
		if (brick[c][r]->item == ITEM_STAR) {
			ball->setType(BALL_STAR);
		}
		delete[] brick[c][r];
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

// 두 선분의 교점을 반환
// 선분A 시점, 선분A 종점, 선분B 시점, 선분B 종점
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

// 선분 위 한 점과 가장 가까운 점 좌표를 반환
// 점의 중점, 선분 시점, 선분 종점
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

// 선분과 선분 교점과 점과 선분 교점을 이용해 원과 선의 교점 좌표를 반환
// 선분과 선분의 교점, 점과 선분의 교점
Vector2D* Object::circleToLine(Vector2D l2l, Vector2D p2l) {
	Vector2D tmp;
	float
		a2c = (ball->center - l2l).scala(),
		p2c = (ball->center - p2l).scala();
	tmp = l2l - RADIUS * a2c / p2c * ball->direction;
	return new Vector2D(tmp.x, tmp.y);
}
