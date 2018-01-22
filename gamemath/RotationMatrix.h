//
//  RotationMatrix.h
//  GameMathLibrary
//
//  Created by River Liu on 10/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef RotationMatrix_h
#define RotationMatrix_h

#include "Matrix3x3.h"

namespace GameMath
{
    class RotationMatrix : public Matrix3x3
    {
    public:
        class X{};
        class Y{};
        class Z{};
        
    public:
        inline RotationMatrix(const Vector3& _col0, const Vector3& _col1, const Vector3& _col2, COLUMNS _c) : Matrix3x3(_col0, _col1, _col2, _c) { }
        inline RotationMatrix(const float _theta, const X _x)
        {
            setCol(0, Vector3::unitX());
            setCol(1, Vector3(0, cos(_theta), sin(_theta)));
            setCol(2, Vector3(0, -sin(_theta), cos(_theta)));
        }
        inline RotationMatrix(const float _theta, const Y _y)
        {
            setCol(0, Vector3(cos(_theta), 0, -sin(_theta)));
            setCol(1, Vector3::unitY());
            setCol(2, Vector3(sin(_theta), 0, cos(_theta)));
        }
        inline RotationMatrix(const float _theta, const Z _z)
        {
            setCol(0, Vector3(cos(_theta), sin(_theta), 0));
            setCol(1, Vector3(-sin(_theta), cos(_theta), 0));
            setCol(2, Vector3::unitZ());
        }
    };
}

#endif /* RotationMatrix_h */
