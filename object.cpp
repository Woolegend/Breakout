#include "object.h"



Object::Object() {
	initObject();
}

void Object::initObject() {
	ball = new Ball(400, 400);
	wall[0] = new Wall(0, 0, 0, 900);
	wall[1] = new Wall(0, 900, 600, 900);
	wall[2] = new Wall(600, 900, 600, 0);
	wall[3] = new Wall(600, 0, 0, 0);
}

void Object::drawObject() {
	ball->drawBall();
	ball->drawDirection();
	ball->update();
	for (int i = 0; i < NUMOFWALL; i++) {
		wall[i]->drawWall();
		wall[i]->drawNormal();
	}
}

void Object::checkCollision() {
	for (int i = 0; i < NUMOFWALL; i++) {
		collision(wall[i]);
	}
}

void Object::collision(Wall* wall) {

}