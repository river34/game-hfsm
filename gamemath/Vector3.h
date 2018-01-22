//
//  Vector3.h
//  GameMathLibrary
//
//  Created by River Liu on 9/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Vector3_h
#define Vector3_h

#include <cmath>
#include <cfloat>
#include <cassert>
#include <string>
#include <sstream>

namespace GameMath
{
    class Vector3
    {
    public:
        union {
            struct { float x, y, z; };
            float v[3];
        };
        
    public:
        inline Vector3(const float _x = 0.f, const float _y = 0.f, const float _z = 0.f) : x(_x), y(_y), z(_z) { }
        inline Vector3(const Vector3& _vec) : x(_vec.x), y(_vec.y), z(_vec.z) { }
        
        inline static Vector3 zero() { return Vector3(0.f, 0.f, 0.f); }
        inline static Vector3 unit() { return Vector3(1.f, 1.f, 1.f); }
        inline static Vector3 unitX() { return Vector3(1.f, 0.f, 0.f); }
        inline static Vector3 unitY() { return Vector3(0.f, 1.f, 0.f); }
        inline static Vector3 unitZ() { return Vector3(0.f, 0.f, 1.f); }
        
        // array subscript operation
        inline float operator[](const unsigned int _which) const { assert(_which < 3); return v[_which]; }
        inline float& operator[](const unsigned int _which) { assert(_which < 3); return v[_which]; }
        
        // comparision operations
        inline bool operator==(const Vector3& _other) const { return x == _other.x && y == _other.y && z == _other.z; }
        inline bool operator!=(const Vector3& _other) const { return x != _other.x || y != _other.y || z != _other.z; }
        
        // assignment operations
        inline Vector3& operator=(const Vector3& _other) { x = _other.x; y = _other.y; z = _other.z; return *this; }
        inline Vector3& operator+=(const Vector3& _other) { x += _other.x; y += _other.y; z += _other.z; return *this; }
        inline Vector3& operator-=(const Vector3& _other) { x -= _other.x; y -= _other.y; z -= _other.z; return *this; }
        inline Vector3& operator*=(const float _scalar) { x *= _scalar; y *= _scalar; z *= _scalar; return *this; }
        inline Vector3& operator/=(const float _scalar) { x /= _scalar; y /= _scalar; z /= _scalar; return *this; }
        
        // arithmetic operations
        inline Vector3 operator+(const Vector3& _other) const { return Vector3(x + _other.x, y + _other.y, z + _other.z); }
        inline Vector3 operator-(const Vector3& _other) const { return Vector3(x - _other.x, y - _other.y, z - _other.z); }
        inline Vector3 operator*(const float _scalar) const { return Vector3(x * _scalar, y * _scalar, z * _scalar); }
        inline Vector3 operator/(const float _scalar) const { return Vector3(x / _scalar, y / _scalar, z / _scalar); }
        inline Vector3 operator-() { return Vector3(-x, -y, -z); }
        
        // Vector3 specific functions
        inline Vector3 componentMul(const Vector3& _other) const { return Vector3(x * _other.x, y * _other.y, z * _other.z); }
        inline float dot(const Vector3& _other) const { return x * _other.x + y * _other.y + z * _other.z; }
        inline Vector3 cross(const Vector3& _other) const { return Vector3(y * _other.z - z * _other.y, z * _other.x - x * _other.z, x * _other.y - y * _other.x); }
        inline float sqMagnitude() const { return dot(*this); }
        inline float magnitude() const {  return sqrt(dot(*this)); }
        inline Vector3 normal() const { float scalar = magnitude(); if (scalar > FLT_EPSILON) return *this/scalar; return *this; }
        inline std::string toString() const { std::ostringstream os; os << '(' << x << "," << y << "," << z << ')'; return os.str(); }
        inline static Vector3 lerp(const Vector3& _vec1, const Vector3& _vec2, const float _beta) { assert(_beta <= 1.f); return _vec1 * (1 - _beta) + _vec2 * _beta; }
        inline float projection(const Vector3& _dir) const { Vector3 unit = _dir.normal(); return (*this).dot(unit); }
        inline Vector3 reflection(const Vector3& _normal) const { Vector3 unit = _normal.normal(); return unit*((*this).dot(unit)*2) - (*this); }
        
        // Direction specific functions
        inline bool inFrontOf(const Vector3& _point, const Vector3& _fwd) const { Vector3 dir = (*this) - _point; return dir.dot(_fwd) > 0; }
        inline bool inViewOf(const Vector3& _point, const Vector3& _fwd, const float _radian) const { Vector3 dir = (*this) - _point; Vector3 unit = _fwd.normal(); return angle(dir, unit) <= _radian; }
        inline float heightToPlane(const Vector3& _point, const Vector3& _normal) const { Vector3 unit = _normal.normal(); Vector3 dir = (*this) - _point; return dir.dot(unit); }
        inline static float angle(const Vector3& _lhs, const Vector3& _rhs) { return acos((_lhs).dot(_rhs)/((_lhs).magnitude()*_rhs.magnitude())); }
        inline static float crossMagnitude(const Vector3& _lhs, const Vector3& _rhs) { return _lhs.magnitude() * _rhs.magnitude() * sin((double)(angle(_lhs, _rhs))); }
        inline static float trianlgeArea(const Vector3& _lhs, const Vector3& _rhs) { return crossMagnitude(_lhs, _rhs) * 0.5; }
    };
}
#endif /* Vector3_h */
