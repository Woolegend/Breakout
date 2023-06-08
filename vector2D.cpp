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

void Vector2D::operator=(const Vector2D& v) {
    x = v.x;
    y = v.y;
}
Vector2D operator+(const Vector2D& v1, const Vector2D& v2) {
    Vector2D tmp(v1.x + v2.x, v1.y + v2.y);
    return tmp;
}
Vector2D operator-(const Vector2D& v1, const Vector2D& v2) {
    Vector2D tmp(v1.x - v2.x, v1.y - v2.y);
    return tmp;
}
Vector2D operator*(const Vector2D& v1, const Vector2D& v2) {
    Vector2D tmp(v1.x * v2.x, v1.y * v2.y);
    return tmp;
}
Vector2D operator*(const Vector2D& v, const float num) {
    Vector2D tmp(v.x * num, v.y * num);
    return tmp;
}
Vector2D operator*(const float num, const Vector2D& v) {
    Vector2D tmp(num * v.x, num * v.y);
    return tmp;
}
Vector2D operator/(const Vector2D& v1, const Vector2D& v2) {
    Vector2D tmp(v1.x / v2.x, v1.y / v2.y);
    return tmp;
}
Vector2D operator/(const Vector2D& v, const float num) {
    Vector2D tmp(v.x / num, v.y / num);
    return tmp;
}

Vector2D operator/(const float num, const Vector2D& v) {
    Vector2D tmp(num / v.x, num / v.y);
    return tmp;
}

float Vector2D::scala() {
    return float(sqrt(pow(x, 2) + pow(y, 2)));
}

void Vector2D::normalizer() {
    float s = scala();
    x = x / s;
    y = y / s;
}


void Vector2D::getNormalVector(Vector2D v) {
    x = v.y;
    y = -v.x;
}


float Vector2D::innerProduct(Vector2D* v) {
    return this->x * v->x + this->y * v->y;
}


void Vector2D::crossProduct(Vector2D* v1, Vector2D* v2) {
    x = v1->y - v2->y;
    y = v1->x - v2->x;
}
