#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>

class Vector
{
  public:
    float x, y;
    float unit_x, unit_y;
    Vector()
    {
        x = 0;
        y = 0;
    };

    Vector(const Vector &other) : x(other.x), y(other.y), unit_x(other.unit_x), unit_y(other.unit_y){};

    Vector(float p_x, float p_y) : x(p_x), y(p_y)
    {
        unit_x = x / length();
        unit_y = y / length();
    }

    // 計算向量的長度
    float length() const
    {
        return std::sqrt(x * x + y * y);
    }

    // 將向量歸一化（讓它的長度變為1，保持方向）
};

#endif // VECTOR_H