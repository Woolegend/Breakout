#include "vector2D.h"

Vector2D::Vector2D() {
    x = 0.0f;
    y = 0.0f;
}

Vector2D::Vector2D(float xx, float yy) {
    this->x = xx;
    this->y = yy;
}

Vector2D::Vector2D(const float* v) {
    this->x = v[0];
    this->y = v[1];
}

Vector2D::Vector2D(const float* s, const float* e) {
    this->x = e[0] - s[0];
    this->y = e[1] - s[1];
}

void Vector2D::setVector(float xx, float yy, float zz) {
    x = xx;
    y = yy;
}

void Vector2D::setVector(const float* v) {
    x = v[0];
    y = v[1];
}

void Vector2D::setVector(const Vector2D* v) {
    x = v->x;
    y = v->y;
}

void Vector2D::setVector(const Vector2D* v1, const Vector2D* v2) {
    x = v2->x - v1->x;
    y = v2->y - v1->y;
}

void Vector2D::addVector(const Vector2D* v, float scala) {
    x = x + scala * v->x;
    y = y + scala * v->y;
}

float Vector2D::scala() {
    return float(sqrt(pow(x, 2) + pow(y, 2)));
}

void Vector2D::normalizer() {
    float s = scala();
    x = x / s;
    y = y / s;
}


void Vector2D::getNormalVector(Vector2D* v) {
    x = v->y;
    y = -v->x;
}


float Vector2D::innerProduct(Vector2D* v) {
    return this->x * v->x + this->y * v->y;
}


void Vector2D::crossProduct(Vector2D* v1, Vector2D* v2) {
    x = v1->y - v2->y;
    y = v1->x - v2->x;
}


float Vector2D::getCos(Vector2D* v) {
    float scala_1 = scala();
    float scala_2 = v->scala();
    float inner = innerProduct(v);
    float cos = inner / (scala_1 * scala_2);
    return cos;
}

float Vector2D::getSin(Vector2D* v) {
    float cos = getCos(v);
    float sin = sqrt(1 - (cos * cos));
    return sin;
}

float Vector2D::getTan(Vector2D* v) {
    float cos = getCos(v);
    float sin = getSin(v);
    float tan = sin / cos;
    return tan;
}


float Vector2D::getAngle(Vector2D* v) {
    float tan = getTan(v);
    float angle = atan(tan);
    return angle;
}