//
//  TRSMatrix.h
//  GameMathLibrary
//
//  Created by River Liu on 10/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef RTMatrix_h
#define RTMatrix_h

#include "Vector3.h"
#include "RotationMatrix.h"
#include "ScaleMatrix.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

namespace GameMath
{
    class TRSMatrix : public Matrix4x4
    {
    public:
        TRSMatrix(const Vector3& _translation, const RotationMatrix& _rotation, const ScaleMatrix& _scale)
        {
            Matrix3x3 upper = Matrix3x3::concat(_rotation, _scale);
            setCol(0, Vector4(upper(0,0), upper(0,1), upper(0,2), _translation.x));
            setCol(1, Vector4(upper(1,0), upper(1,1), upper(1,2), _translation.x));
            setCol(2, Vector4(upper(2,0), upper(2,1), upper(2,2), _translation.x));
            setCol(3, Vector4::unitW());
        }
        TRSMatrix(const Vector3& _translation, const RotationMatrix& _rotation, const Vector3& _scale)
        {
            TRSMatrix(_translation, _rotation, ScaleMatrix(_scale));
        }
        TRSMatrix(const Vector3& _translation, const RotationMatrix& _rotation, const float _scale)
        {
            TRSMatrix(_translation, _rotation, ScaleMatrix(_scale));
        }
    };
}

#endif /* RTMatrix_h */
