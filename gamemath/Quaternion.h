//
//  Quaternion.h
//  GameMathLibrary
//
//  Created by River Liu on 10/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Quaternion_h
#define Quaternion_h

#include <math.h>
#include "Vector3.h"
#include "Vector4.h"
#include "RotationMatrix.h"

namespace GameMath
{
    class Quaternion : public Vector4
    {
    public:
        inline Quaternion(const float _x = 0.f, const float _y = 0.f, const float _z = 0.f, const float _w = 1.f) : Vector4(_x, _y, _z, _w) { }
        inline Quaternion(const Vector4& _vec) : Vector4(_vec) { }
        inline Quaternion(const Quaternion& _q) : Vector4(_q.x, _q.y, _q.z, _q.w) { }
        inline Quaternion(const Vector3& _vec) : Vector4(_vec.x, _vec.y, _vec.z, 1.f) { }
        inline Quaternion(const Vector3& _axis, const float _theta) : Vector4(_axis.x * sin(_theta/2), _axis.y * sin(_theta/2), _axis.z * sin(_theta/2), sin(_theta/2)) { }
        inline Quaternion(const RotationMatrix& _rotation) { fromRotationMatrix(*this, _rotation); }
        
        inline static Quaternion identity() { return Quaternion(0.f, 0.f, 0.f, 1.f); }
        inline Vector3 vector() const { return Vector3(x, y, z); }
        inline float scalar() const { return w; }
        
        // arithmetic operations
        /* Grassman product */
        inline Quaternion operator*(const Quaternion& _other) const {
            Vector3 v = _other.vector() * scalar() + vector() * _other.scalar() + vector().cross(_other.vector());
            float s = scalar() * _other.scalar() - vector().dot(_other.vector());
            return Quaternion(v.x, v.y, v.z, s); }
        
        // Quaternion specific functions
        inline Quaternion conjugate() const { return Quaternion(-x, -y, -z, w); }
        inline Quaternion inverse() const { return conjugate() /* /(*this).dot(*this) */ ; }
        RotationMatrix toRotationMatrix()
        {
            return RotationMatrix(
                                  Vector3(1 - 2*y*y - 2*z*z, 2*x*y + 2*z*w, 2*x*z - 2*y*w),
                                  Vector3(2*x*y - 2*z*w, 1 - 2*x*x - 2*z*z, 2*y*z + 2*x*w),
                                  Vector3(2*x*z + 2*y*w, 2*y*z - 2*x*w, 1 - 2*x*x - 2*y*y),
                                  RotationMatrix::COLUMNS());
        }
        static void fromRotationMatrix(Quaternion& _q, const RotationMatrix& _rotation)
        {
            /* Shoemake SIGGRAPH 1987 http://www.cs.ucr.edu/~vbz/resources/quatut.pdf */
            float fTrace = _rotation(0,0)+_rotation(1,1)+_rotation(2,2);
            float fRoot;
            if ( fTrace > 0.0 )
            {
                fRoot = sqrt(fTrace + 1.0f);
                _q.w = 0.5f*fRoot;
                fRoot = 0.5f/fRoot;
                _q.x = (_rotation(2,1)-_rotation(1,2))*fRoot;
                _q.y = (_rotation(0,2)-_rotation(2,0))*fRoot;
                _q.z = (_rotation(1,0)-_rotation(0,1))*fRoot;
            }
            else
            {
                static unsigned int s_iNext[3] = { 1, 2, 0 };
                unsigned int i = 0;
                if ( _rotation(1,1) > _rotation(0,0) )
                    i = 1;
                if ( _rotation(2,2) > _rotation(i,i) )
                    i = 2;
                unsigned int j = s_iNext[i];
                unsigned int k = s_iNext[j];
                fRoot = sqrt(_rotation(i,i)-_rotation(j,j)-_rotation(k,k) + 1.0f);
                float* apkQuat[3] = { &_q.x, &_q.y, &_q.z };
                *apkQuat[i] = 0.5f*fRoot;
                fRoot = 0.5f/fRoot;
                _q.w = (_rotation(k,j)-_rotation(j,k))*fRoot;
                *apkQuat[j] = (_rotation(j,i)+_rotation(i,j))*fRoot;
                *apkQuat[k] = (_rotation(k,i)+_rotation(i,k))*fRoot;
            }
        }
        inline Vector3 toVector3() { return Vector3(x, y, z); }
        static Quaternion fromToRotation(const Vector3& _from, const Vector3& _to, const Vector3& fallbackAxis = Vector3::zero())
        {
            /* Stan Melax's article in Game Programming Gems */
            Quaternion q;
            // Copy, since cannot modify local
            Vector3 v0 = _from.normal();
            Vector3 v1 = _to.normal();
            
            float d = v0.dot(v1);
            // If dot == 1, vectors are the same
            if (d >= 1.0f)
            {
                return identity();
            }
            if (d < (FLT_EPSILON - 1.0f))
            {
                if (fallbackAxis != Vector3::zero())
                {
                    // rotate 180 degrees about the fallback axis
                    q = Quaternion(fallbackAxis, M_PI);
                }
                else
                {
                    // Generate an axis
                    Vector3 axis = Vector3::unitX().cross(v0);
                    if (axis.magnitude() < FLT_EPSILON) // pick another if colinear
                        axis = Vector3::unitY().cross(v0);
                    axis = axis.normal();
                    q = Quaternion(axis, M_PI);
                }
            }
            else
            {
                float s = std::sqrt((1+d)*2);
                float invs = 1 / s;
                
                Vector3 c = v0.cross(v1);
                
                q.x = c.x * invs;
                q.y = c.y * invs;
                q.z = c.z * invs;
                q.w = s * 0.5f;
                q = q.normal();
            }
            return q;
        }
        inline static Quaternion lerp(const Quaternion& _q1, const Quaternion& _q2, const float _beta) { return _q1 * (1-_beta) + _q2 * _beta; }
        inline static Quaternion slerp(const Quaternion& _q1, const Quaternion& _q2, const float _beta) { float theta = acos(_q1.dot(_q2)); float w1 = sin(1-_beta) * theta / sin(theta); float w2 = sin(_beta*theta)/sin(theta); return _q1 * w1 + _q2 * w2; }
        inline static Vector3 rotate(const Quaternion& _q, const Vector3& _vec) { return (_q * Quaternion(_vec) * _q.inverse()).toVector3(); }
    };
}

#endif /* Quaternion_h */
