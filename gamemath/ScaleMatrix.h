//
//  ScaleMatrix.h
//  GameMathLibrary
//
//  Created by River Liu on 10/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef ScaleMatrix_h
#define ScaleMatrix_h

#include "Vector3.h"
#include "Matrix3x3.h"

namespace GameMath
{
    class ScaleMatrix : public Matrix3x3
    {
    public:
        inline ScaleMatrix(const Vector3& _scale)
        {
            setCol(0, Vector3::unitX() * _scale.x);
            setCol(1, Vector3::unitY() * _scale.y);
            setCol(2, Vector3::unitZ() * _scale.z);
        }
        inline ScaleMatrix(const float _scale)
        {
            setCol(0, Vector3::unitX() * _scale);
            setCol(1, Vector3::unitY() * _scale);
            setCol(2, Vector3::unitZ() * _scale);
        }
    };
}

#endif /* ScaleMatrix_h */
