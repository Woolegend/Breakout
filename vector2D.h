#pragma once

#ifndef __MATH_H_
#define __MATH_H_
#include <math.h>
#endif

class Vector2D {
public:
    float x, y;
    Vector2D();
    Vector2D(float xx, float yy);
    Vector2D(const float* v);
    Vector2D(const float* s, const float* e);

    void operator=(const Vector2D& v);
    friend Vector2D operator+(const Vector2D& v1, const Vector2D& v2);
    friend Vector2D operator-(const Vector2D& v1, const Vector2D& v2);
    friend Vector2D operator*(const Vector2D& v1, const Vector2D& v2);
    friend Vector2D operator*(const Vector2D& v, const float num);
    friend Vector2D operator*(const float num, const Vector2D& v);
    friend Vector2D operator/(const Vector2D& v1, const Vector2D& v2);
    friend Vector2D operator/(const Vector2D& v, const float num);
    friend Vector2D operator/(const float num, const Vector2D&);


    float scala();
    void normalizer();
    void getNormalVector(Vector2D v);
    float innerProduct(Vector2D* v);
    void crossProduct(Vector2D* v1, Vector2D* v2);
    float getCos(Vector2D* v);
    float getSin(Vector2D* v);
    float getTan(Vector2D* v);
    float getAngle(Vector2D* v);
};
