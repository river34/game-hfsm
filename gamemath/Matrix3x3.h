//
//  Matrix3x3.h
//  GameMathLibrary
//
//  Created by River Liu on 10/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Matrix3x3_h
#define Matrix3x3_h

#include <cmath>
#include <cfloat>
#include <cassert>
#include <string>
#include <sstream>
#include "Vector3.h"
#include "Matrix2x2.h"

namespace GameMath
{
    class Matrix3x3
    {
    public:
        class COLUMNS{};
        class ROWS{};
        
    private:
        Vector3 m_col[3];
        
    public:
        inline Matrix3x3()
        {
            setCol(0, Vector3::zero());
            setCol(1, Vector3::zero());
            setCol(2, Vector3::zero());
        }
        
        inline Matrix3x3(const Vector3& _col0, const Vector3& _col1, const Vector3& _col2, COLUMNS _c)
        {
            setCol(0, _col0);
            setCol(1, _col1);
            setCol(2, _col2);
        }
        
        inline Matrix3x3(const Vector3& _row0, const Vector3& _row1, const Vector3& _row2, ROWS _r)
        {
            setRow(0, _row0);
            setRow(1, _row1);
            setRow(2, _row2);
        }
        
        inline static Matrix3x3 zero()
        {
            return Matrix3x3 (
                              Vector3::zero(),
                              Vector3::zero(),
                              Vector3::zero(),
                              COLUMNS()
                              );
        }
        
        inline static Matrix3x3 identity()
        {
            return Matrix3x3 (
                              Vector3::unitX(),
                              Vector3::unitY(),
                              Vector3::unitZ(),
                              COLUMNS()
                              );
        }
        
        inline void setCol(unsigned int _which, const Vector3& _col)
        {
            assert(_which < 3);
            m_col[_which] = _col;
        }
        
        inline Vector3 getCol(unsigned int _which) const
        {
            assert(_which < 3);
            return m_col[_which];
        }
        
        inline void setRow(unsigned int _which, const Vector3& _row)
        {
            assert(_which < 3);
            m_col[0][_which] = _row[0];
            m_col[1][_which] = _row[1];
            m_col[2][_which] = _row[2];
        }
        
        inline Vector3 getRow(unsigned int _which) const
        {
            assert(_which < 3);
            return Vector3(m_col[0][_which], m_col[1][_which], m_col[2][_which]);
        }
        
        float& operator() (unsigned int _row, unsigned int _column) { assert(_row < 3 && _column < 3); return m_col[_column][_row]; }
        float operator() (unsigned int _row, unsigned int _column) const { assert(_row < 3 && _column < 3); return m_col[_column][_row]; }
        
        // comparision operations
        inline bool operator==(const Matrix3x3& _other) const { return m_col[0] == _other.getCol(0) && m_col[1] == _other.getCol(0) && m_col[2] == _other.getCol(2); }
        inline bool operator!=(const Matrix3x3& _other) const { return m_col[0] != _other.getCol(0) || m_col[1] != _other.getCol(0) || m_col[2] != _other.getCol(2); }
        
        // assignment operations
        inline Matrix3x3& operator+=(const Matrix3x3& _other) { m_col[0] += _other.getCol(0); m_col[1] += _other.getCol(1); m_col[2] += _other.getCol(2); return *this; }
        inline Matrix3x3& operator-=(const Matrix3x3& _other) { m_col[0] -= _other.getCol(0); m_col[1] -= _other.getCol(1); m_col[2] -= _other.getCol(2); return *this; }
        inline Matrix3x3& operator*=(const float _scalar) { m_col[0] *= _scalar; m_col[1] *= _scalar; m_col[2] *= _scalar; return *this; }
        inline Matrix3x3& operator/=(const float _scalar) { m_col[0] /= _scalar; m_col[1] /= _scalar; m_col[2] /= _scalar; return *this; }

        // arithmetic operations
        inline Matrix3x3 operator+(const Matrix3x3& _other) const { return Matrix3x3(m_col[0] + _other.getCol(0), m_col[1] + _other.getCol(1), m_col[2] + _other.getCol(2), COLUMNS()); }
        inline Matrix3x3 operator-(const Matrix3x3& _other) const { return Matrix3x3(m_col[0] - _other.getCol(0), m_col[1] - _other.getCol(1), m_col[2] - _other.getCol(2), COLUMNS()); }
        inline Matrix3x3 operator*(const float _scalar) const { return Matrix3x3(m_col[0] * _scalar, m_col[1] * _scalar, m_col[2] * _scalar, COLUMNS()); }
        inline Matrix3x3 operator/(const float _scalar) const { return Matrix3x3(m_col[0] / _scalar, m_col[1] / _scalar, m_col[2] / _scalar, COLUMNS()); }
        inline Matrix3x3 operator*(const Matrix3x3& _other) const
        {
            Vector3 row0 = getRow(0);
            Vector3 row1 = getRow(1);
            Vector3 row2 = getRow(2);
            Vector3 oCol0 = _other.getCol(0);
            Vector3 oCol1 = _other.getCol(1);
            Vector3 oCol2 = _other.getCol(2);
            
            return Matrix3x3(Vector3(row0.dot(oCol0), row0.dot(oCol1), row0.dot(oCol2)),
                             Vector3(row1.dot(oCol0), row1.dot(oCol1), row1.dot(oCol2)),
                             Vector3(row2.dot(oCol0), row2.dot(oCol1), row2.dot(oCol2)),
                             ROWS());
        }
        
        // Matrix3x3 specific functions
        Matrix3x3 componentMul(const Matrix3x3& _other) const
        {
            Matrix3x3 mul = Matrix3x3::zero();
            for (unsigned int i = 0; i < 4; i++)
                for (unsigned int j = 0; j < 4; j++)
                    mul(i,j) = (*this)(i,j) * _other(i,j);
            return mul;
        }
        inline static Matrix3x3 concat(const Matrix3x3& _lhs, const Matrix3x3& _rhs) { return _lhs * _rhs; }
        inline Matrix3x3 transpose() const { return Matrix3x3(m_col[0], m_col[1], m_col[2], ROWS()); }
        inline std::string toString() const { std::ostringstream os; os << '[' <<  getRow(0).toString() << "," << getRow(1).toString() << "," << getRow(2).toString() << ']'; return os.str(); }
        
        inline float determinant() const
        {
            Matrix2x2 m0 = Matrix2x2(Vector2(m_col[1][1], m_col[1][2]), Vector2(m_col[2][1], m_col[2][2]), Matrix2x2::COLUMNS());
            Matrix2x2 m1 = Matrix2x2(Vector2(m_col[0][1], m_col[0][2]), Vector2(m_col[2][1], m_col[2][2]), Matrix2x2::COLUMNS());
            Matrix2x2 m2 = Matrix2x2(Vector2(m_col[0][1], m_col[0][2]), Vector2(m_col[1][1], m_col[1][2]), Matrix2x2::COLUMNS());
            return m_col[0][0] * m0.determinant() - m_col[1][0] * m1.determinant() + m_col[2][0] * m2.determinant();
        }
        
        Matrix3x3 inverse() const
        {
            Matrix3x3 inverted = Matrix3x3::zero();
            inverted.setRow(0, Vector3(
                                        (*this)(1,1)*(*this)(2,2) - (*this)(1,2)*(*this)(2,1),
                                        (*this)(0,2)*(*this)(2,1) - (*this)(0,1)*(*this)(2,2),
                                        (*this)(0,1)*(*this)(1,2) - (*this)(0,2)*(*this)(1,1)));
            inverted.setRow(1, Vector3(
                                        (*this)(1,2)*(*this)(2,0) - (*this)(1,0)*(*this)(2,2),
                                        (*this)(0,0)*(*this)(2,2) - (*this)(0,2)*(*this)(2,0),
                                        (*this)(0,2)*(*this)(1,0) - (*this)(0,0)*(*this)(1,2)));
            inverted.setRow(2, Vector3(
                                        (*this)(1,0)*(*this)(2,1) - (*this)(1,1)*(*this)(2,0),
                                        (*this)(0,1)*(*this)(2,0) - (*this)(0,0)*(*this)(2,1),
                                        (*this)(0,0)*(*this)(1,1) - (*this)(0,1)*(*this)(1,0)));
            
            float fDet =
            (*this)(0, 0) * inverted(0, 0) +
            (*this)(0, 1) * inverted(1, 0) +
            (*this)(0, 2) * inverted(2, 0);
            
            float fInvDet = 1.f / fDet;
            for (unsigned int iRow = 0; iRow < 3; iRow++)
                for (unsigned int iCol = 0; iCol < 3; iCol++)
                    inverted(iRow, iCol) *= fInvDet;
            
            return inverted;
        }
    };
}

#endif /* Matrix3x3_h */
