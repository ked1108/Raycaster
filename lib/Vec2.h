#pragma once

#include <cmath>

struct Vec2 {
    float x, y;

    Vec2(float x, float y) : x(x), y(y) {}
    Vec2() : x(0), y(0) {}
    
    Vec2 operator+(const Vec2& other) const {
        return {x + other.x, y + other.y};
    }

    Vec2 operator-(const Vec2& other) const {
        return {x - other.x, y - other.y};
    }

    Vec2 operator*(float scalar) const {
        return {x * scalar, y * scalar};
    }

    Vec2 operator/(float scalar) const {
        return {x / scalar, y / scalar};
    }

    float dot(const Vec2& other) const {
        return x * other.x + y * other.y;
    }

    float length() const {
        return std::sqrt(x * x + y * y);
    }

    Vec2 normalized() const {
        float len = length();
        return len > 0 ? (*this) / len : Vec2{0, 0};
    }
};
