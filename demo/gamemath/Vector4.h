//
//  Vector4.h
//  GameMathLibrary
//
//  Created by River Liu on 9/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Vector4_h
#define Vector4_h

#include <cmath>
#include <cfloat>
#include <string>
#include <sstream>

namespace GameMath
{
    class Vector4
    {
    public:
        union {
            struct { float x, y, z, w; };
            float v[4];
        };
        
    public:
        inline Vector4(const float _x = 0.f, const float _y = 0.f, const float _z = 0.f, const float _w = 0.f) : x(_x), y(_y), z(_z), w(_w) { }
        inline Vector4(const Vector4& _vec) : x(_vec.x), y(_vec.y), z(_vec.z), w(_vec.w) { }
        inline Vector4(const Vector3& _vec3, const float _scalar) : x(_vec3.x), y(_vec3.y), z(_vec3.z), w(_scalar) { }
        
        inline static Vector4 zero() { return Vector4(0.f, 0.f, 0.f, 0.f); }
        inline static Vector4 unit() { return Vector4(1.f, 1.f, 1.f, 1.f); }
        inline static Vector4 unitX() { return Vector4(1.f, 0.f, 0.f, 0.f); }
        inline static Vector4 unitY() { return Vector4(0.f, 1.f, 0.f, 0.f); }
        inline static Vector4 unitZ() { return Vector4(0.f, 0.f, 1.f, 0.f); }
        inline static Vector4 unitW() { return Vector4(0.f, 0.f, 0.f, 1.f); }
        
        // array subscript operation
        inline float operator[](const unsigned int _which) const { assert(_which < 4); return v[_which]; }
        inline float& operator[](const unsigned int _which) { assert(_which < 4); return v[_which]; }
        
        // comparision operations
        inline bool operator==(const Vector4& _other) const { return x == _other.x && y == _other.y && z == _other.z && w == _other.w; }
        inline bool operator!=(const Vector4& _other) const { return x != _other.x || y != _other.y || z != _other.z || w != _other.w; }
        
        // assignment operations
        inline Vector4& operator=(const Vector4& _other) { x = _other.x; y = _other.y; z = _other.z; w = _other.w; return *this; }
        inline Vector4& operator+=(const Vector4& _other) { x += _other.x; y += _other.y; z += _other.z; w += _other.w; return *this; }
        inline Vector4& operator-=(const Vector4& _other) { x -= _other.x; y -= _other.y; z -= _other.z; w -= _other.w; return *this; }
        inline Vector4& operator*=(const float _scalar) { x *= _scalar; y *= _scalar; z *= _scalar; w *= _scalar; return *this; }
        inline Vector4& operator/=(const float _scalar) { x /= _scalar; y /= _scalar; z /= _scalar; w /= _scalar; return *this; }
        
        // arithmetic operations
        inline Vector4 operator+(const Vector4& _other) const { return Vector4(x + _other.x, y + _other.y, z + _other.z, w + _other.w); }
        inline Vector4 operator-(const Vector4& _other) const { return Vector4(x - _other.x, y - _other.y, z - _other.z, w - _other.w); }
        inline Vector4 operator*(const float _scalar) const { return Vector4(x * _scalar, y * _scalar, z * _scalar, w * _scalar); }
        inline Vector4 operator/(const float _scalar) const { return Vector4(x / _scalar, y / _scalar, z / _scalar, w / _scalar); }
        inline Vector4 operator-() { return Vector4(-x, -y, -z, -w); }
        
        // Vector4 specific functions
        inline Vector4 componentMul(const Vector4& _other) const { return Vector4(x * _other.x, y * _other.y, z * _other.z, w * _other.w); }
        inline float dot(const Vector4& _other) const { return x * _other.x + y * _other.y + z * _other.z + w * _other.w; }
        inline float sqMagnitude() const { return dot(*this); }
        inline float magnitude() const {  return sqrt(dot(*this)); }
        inline Vector4 normal() const { float scalar = magnitude(); if (scalar > FLT_EPSILON) return *this/scalar; return *this; }
        inline std::string toString() const { std::ostringstream os; os << '(' << x << "," << y << "," << z << "," << w << ')'; return os.str(); }
    };
}


#endif /* Vector4_h */
