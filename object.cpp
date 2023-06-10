#include "object.h"
#include<ios>

//마리오 게임 보드
int board[BRICK_COL][BRICK_ROW] = {
	// 모서리 인덱스는 0으로 고정
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
	{0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

// 오브젝트 생성자
// 게임 상태를 [준비 단계]로 전환
// 각종 오브젝트들 생성
Object::Object() {
	gameReady();
	initObject();
}

// 각종 오브젝트들 생성
void Object::initObject() {

	//게임 단계 초기화
	isPlay = false;
	isOver = false;
	isPause = false;
	//목숨 개수 초기화
	life = 3;
	//일반 벽돌 개수를 저장할 변수
	brick_num = 0;

	//벽면 생성
	//사방을 둘러 싼 4개의 벽면 생성
	wall[0] = new Wall(SCALE, HEIGHT, WIDTH - SCALE, HEIGHT);
	wall[1] = new Wall(WIDTH - SCALE, HEIGHT, WIDTH - SCALE, SCALE);
	wall[2] = new Wall(WIDTH - SCALE, SCALE, SCALE, SCALE);
	wall[3] = new Wall(SCALE, SCALE, SCALE, HEIGHT);

	//사선으로 기울어진 파이프의 벽면
	float co = 32 * sqrt(2); // 기울기 가중
	float sz = 150;			 // 파이프의 사이즈
	// 좌측 파이프 생성
	wall[4] = new Wall(0, 500 - co, sz, 500 - co + sz);
	wall[5] = new Wall(sz, 500 - co + sz, sz - co, 500 + sz);
	wall[6] = new Wall(sz - co, 500 + sz, 0, 500 + co);
	// 우측 파이프 생성
	wall[7] = new Wall(900, 500 + co, 900 - sz + co, 500 + sz);
	wall[8] = new Wall(900 - sz + co, 500 + sz, 900 - sz, 500 - co + sz);
	wall[9] = new Wall(900 - sz, 500 - co + sz, 900, 500 - co);

	// 벽돌 생성
	// 벽돌을 저장할 배열 동적 할당
	brick = new Brick * *[BRICK_COL];
	for (int i = 0; i < BRICK_COL; i++) {
		brick[i] = new Brick * [BRICK_ROW];
	}

	// board[i][j] = N
	// N = 0		: 빈 공간
	// N = 1 ~ 5	: 일반 벽돌 
	// N = 6		: 아이템 박스
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
	ball = new Ball(WIDTH / 2, 100);
	// 배트 위치 초기화
	bat = new Bat(WIDTH / 2, 50);
}

// 생성된 오브젝트 그리기
void Object::drawObject() {

	//공 그리기
	ball->draw();
	//배트 그리기
	bat->draw();
	bat->drawBounding();

	//벽돌 그리기
	for (int i = 0; i < BRICK_COL; i++) {
		for (int j = 0; j < BRICK_ROW; j++) {
			if (brick[i][j] == NULL)
				continue;
			brick[i][j]->draw();
			brick[i][j]->drawBounding();
		}
	}

	//사선 파이프 그리기
	asset.drawPipe(0, 500, 30, -45);
	asset.drawPipe(900, 500, 30, 45);

	//목숨 개수 그리기
	for (int i = 0; i < life; i++) {
		asset.drawMush((i + 1 + 0.5) * SCALE, HEIGHT - SCALE * 0.5, 0);
	}

	/*
	for (int i = 0; i < NUMOFWALL; i++) {
		wall[i]->draw();
		wall[i]->drawNormal();
	}
	*/

	//벽면 그리기
	for (int i = 0; i < 30; i++) {
		asset.drawBlockB(15, 15 + i * SCALE);
		asset.drawBlockB(885, 15 + i * SCALE);
		asset.drawBlockB(15 + i * SCALE, 15);
	}


}

// 생성된 오브젝트 정보 최신화
// 매개변수
// bool L : 좌측 화살표 입력
// bool R : 우측 화살표 입력
// bool S : 스페이스바 입력
void Object::updateObject(bool L, bool R, bool S) {
	static float dir_x = 0;
	// 게임 플레이 중
	// 배트 위치 최신화
	// 공 위치 최신화
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
	// 게임 시작 전 준비 단계
	// 공의 시작 방향 선택 사능
	if (isReady) {
		// 스페이스 입력 시
		// 게임 상태 플레이로 전환
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
			ball->drawDirection();
			ball->direction.normalizer();
			return;
		}
	}

	// 게임 종료 시
	if (isOver) {
		return;
	}

	// 목숨을 잃었을 때
	// 목숨이 남았을 경우
	// 게임 상태를 준비 단계로 전환
	if (life != 0) {
		if (S) gameReady();
		return;
	}
	// 목숨을 모두 잃었을 경우
	// 게임 종료
	if (life == 0) {
		isOver = true;
		return;
	}
}

// 각종 충돌 판정 확인
void Object::checkCollision() {
	//게임 상태 [게임 단계]일 때 확인
	if (!isPlay) return;
	wallCollision();
	brickCollision();
	batCollision();
}

// 벽면 충돌 판정 확인
// 충돌 대상 : 사면의 벽, 사선 파이프
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
		else {
			ball->direction = ball->direction + wall[index]->normal * 1.5;
			ball->direction.normalizer();
		}
	}
}

// 벽돌 충돌 판정 확인 
void Object::brickCollision() {
	bool isCollision = false; // 충돌 여부
	int c, r, // 충돌 벽돌의 인덱스를 저장
		// 충돌 방향
		collision_point;
	float
		// 충돌 판정 최소 거리
		// 벽돌과 충돌 시, 공과 충돌한 벽돌의 거리를 저장
		// 다수의 벽돌과 충돌 시 거리가 가장 가까운 벽돌과 충돌
		min = 80,
		// 공의 중심과 벽돌간의 거리
		dis;
	//충돌 시 법선 벡터
	Vector2D nVec;

	//모든 벽돌의 위치와 충돌 여부 판정
	for (int i = 1; i < BRICK_COL - 1; i++) {
		for (int j = 1; j < BRICK_ROW - 1; j++) {

			//충돌 판정을 스킵하는 경우

			// 해당 좌표에 벽돌 없을 경우
			if (brick[i][j] == NULL) continue;
			// 벽돌과 공이 너무 멀 경우
			dis = (ball->center - brick[i][j]->center).scala();
			if (min < dis) continue;

			// 아이템일 경우 아이템 충돌 판정 호출
			if (brick[i][j]->type == BRICK_ITEM) {
				itemCollision(i, j);
				continue;
			}

			float
				cx = ball->center.x,
				cy = ball->center.y;

			// 충돌 범위 판점
			// 충돌 상자 범위 내부인가?
			if (cx >= fmin(brick[i][j]->bvtx[0].x, brick[i][j]->bvtx[1].x) &&
				cx <= fmax(brick[i][j]->bvtx[0].x, brick[i][j]->bvtx[1].x) &&
				cy >= fmin(brick[i][j]->bvtx[2].y, brick[i][j]->bvtx[1].y) &&
				cy <= fmax(brick[i][j]->bvtx[2].y, brick[i][j]->bvtx[1].y)) {
				c = i, r = j;
				min = dis;

				// 충돌 방향 판정
				// 윗 면 충돌
				if (cx >= fmin(brick[i][j]->vtx[0].x, brick[i][j]->vtx[1].x) &&
					cx <= fmax(brick[i][j]->vtx[0].x, brick[i][j]->vtx[1].x) &&
					cy > brick[i][j]->center.y) {
					isCollision = true;
					collision_point = BRICK_TOP;
					nVec = Vector2D(0, 1);
				}
				// 우측 면 충돌
				else if (cy >= fmin(brick[i][j]->vtx[1].y, brick[i][j]->vtx[2].y) &&
					cy <= fmax(brick[i][j]->vtx[1].y, brick[i][j]->vtx[2].y) &&
					cx > brick[i][j]->center.x) {
					isCollision = true;
					collision_point = BRICK_RIGHT;
					nVec = Vector2D(1, 0);
				}
				// 아랫 면 충돌
				else if (cx >= fmin(brick[i][j]->vtx[2].x, brick[i][j]->vtx[3].x) &&
					cx <= fmax(brick[i][j]->vtx[2].x, brick[i][j]->vtx[3].x) &&
					cy < brick[i][j]->center.y) {
					isCollision = true;
					collision_point = BRICK_BOTTOM;
					nVec = Vector2D(0, -1);
				}
				// 좌측 면 충돌
				else if (cy >= fmin(brick[i][j]->vtx[3].y, brick[i][j]->vtx[0].y) &&
					cy <= fmax(brick[i][j]->vtx[3].y, brick[i][j]->vtx[0].y) &&
					cx < brick[i][j]->center.x) {
					isCollision = true;
					collision_point = BRICK_LEFT;
					nVec = Vector2D(-1, 0);
				}
				// 모서리 충돌 판정
				else {
					// 좌 상단 모서리 충돌
					if (cx < brick[i][j]->center.x && cy > brick[i][j]->center.y
						&& RADIUS >= (ball->center - brick[i][j]->vtx[0]).scala()) {
						isCollision = true;
						collision_point = BRICK_LEFT_TOP;
						nVec = Vector2D(-1, 1);
						nVec.normalizer();
					}
					// 우 상단 모서리 충돌
					else if (cx > brick[i][j]->center.x && cy > brick[i][j]->center.y
						&& RADIUS >= (ball->center - brick[i][j]->vtx[1]).scala()) {
						isCollision = true;
						collision_point = BRICK_RIGHT_TOP;
						nVec = Vector2D(1, 1);
						nVec.normalizer();
					}
					// 우 하단 모서리 충돌
					else if (cx > brick[i][j]->center.x && cy < brick[i][j]->center.y
						&& RADIUS >= (ball->center - brick[i][j]->vtx[2]).scala()) {
						isCollision = true;
						collision_point = BRICK_RIGHT_BOTTOM;
						nVec = Vector2D(1, -1);
						nVec.normalizer();
					}
					// 좌 하단 모서리 충돌
					else if (cx < brick[i][j]->center.x && cy < brick[i][j]->center.y
						&& RADIUS >= (ball->center - brick[i][j]->vtx[3]).scala()) {
						isCollision = true;
						collision_point = BRICK_LFET_BOTTOM;
						nVec = Vector2D(-1, -1);
						nVec.normalizer();
					}
					//모서리 판정 실패 시
					else { min = 80; }
				}
			}
		}

		// 벽돌과 충돌 시
		if (isCollision) {
			// 기본 벽돌일 경우
			if (brick[c][r]->type == BRICK_NORMAL) {
				brick_num--;
				brick[c][r]->collision();
			}
			// 아이템 박스일 경우
			else if (brick[c][r]->type == BRICK_ITEMBOX) {
				if (collision_point == BRICK_BOTTOM) {
					brick[c][r]->collision();
				}
			}
			ball->direction = ball->direction + 1.5 * nVec;
			ball->direction.y = ball->direction.y + ball->direction.y > 0 ? 1 : -1;
			ball->direction.normalizer();
		}
	}
}

// 배트 충돌 판정 확인
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

// 아이템 충돌 판정 확인
void Object::itemCollision(int c, int r) {
	float
		cx = brick[c][r]->center.x,
		cy = brick[c][r]->center.y;
	if (cx >= bat->bvtx[0].x - 5 && cx <= bat->bvtx[1].x + 5 &&
		cy >= bat->bvtx[2].y - 20 && cy <= bat->bvtx[1].y + 5) {
		if (brick[c][r]->item == ITEM_MUSH) {
			life++;
		}
		delete[] brick[c][r];
	}
	else if (cy < 0) {
		delete[] brick[c][r];
	}
}


// 공과 벽의 예상 충돌 지정 / 벽돌은 해당되지 않는다.
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
