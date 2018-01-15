//
//  Vector2.h
//  GameMathLibrary
//
//  Created by River Liu on 9/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Vector2_h
#define Vector2_h

#include <cmath>
#include <cfloat>
#include <cassert>
#include <string>
#include <sstream>

namespace GameMath
{
    class Vector2
    {
    public:
        union {
            struct { float x, y; };
            float v[2];
        };
        
    public:
        inline Vector2(const float _x = 0.f, const float _y = 0.f) : x(_x), y(_y) { }
        inline Vector2(const Vector2& _vec) : x(_vec.x), y(_vec.y) { }
        
        inline static Vector2 zero() { return Vector2(0.f, 0.f); }
        inline static Vector2 unit() { return Vector2(1.f, 1.f); }
        inline static Vector2 unitX() { return Vector2(1.f, 0.f); }
        inline static Vector2 unitY() { return Vector2(0.f, 1.f); }
        
        // array subscript operation
        inline float operator[](const unsigned int _which) const { assert(_which < 2); return v[_which]; }
        inline float& operator[](const unsigned int _which) { assert(_which < 2); return v[_which]; }
        
        // comparision operations
        inline bool operator==(const Vector2& _other) const { return x == _other.x && y == _other.y; }
        inline bool operator!=(const Vector2& _other) const { return x != _other.x || y != _other.y; }
        
        // assignment operations
        inline Vector2& operator=(const Vector2& _other) { x = _other.x; y = _other.y; return *this; }
        inline Vector2& operator+=(const Vector2& _other) { x += _other.x; y += _other.y; return *this; }
        inline Vector2& operator-=(const Vector2& _other) { x -= _other.x; y -= _other.y; return *this; }
        inline Vector2& operator*=(const float _scalar) { x *= _scalar; y *= _scalar; return *this; }
        inline Vector2& operator/=(const float _scalar) { x /= _scalar; y /= _scalar; return *this; }
        
        // arithmetic operations
        inline Vector2 operator+(const Vector2& _other) const { return Vector2(x + _other.x, y + _other.y); }
        inline Vector2 operator-(const Vector2& _other) const { return Vector2(x - _other.x, y - _other.y); }
        inline Vector2 operator*(const float _scalar) const { return Vector2(x * _scalar, y * _scalar); }
        inline Vector2 operator/(const float _scalar) const { return Vector2(x / _scalar, y / _scalar); }
        inline Vector2 operator-() { return Vector2(-x, -y); }
        
        // Vector2 specific functions
        inline Vector2 componentMul(const Vector2& _other) const { return Vector2(x * _other.x, y * _other.y); }
        inline float dot(const Vector2& _other) const { return x * _other.x + y * _other.y; }
        inline float sqMagnitude() const { return dot(*this); }
        inline float magnitude() const {  return sqrt(dot(*this)); }
        inline Vector2 normal() const { float scalar = magnitude(); if (scalar > FLT_EPSILON) return *this/scalar; return *this; }
        inline std::string toString() const { std::ostringstream os; os << '(' << x << "," << y << ')'; return os.str(); }
    };
}

#endif /* Vector2_h */