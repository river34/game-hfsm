//
//  Matrix4x4.h
//  GameMathLibrary
//
//  Created by River Liu on 10/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Matrix4x4_h
#define Matrix4x4_h

#include <cmath>
#include <cfloat>
#include <cassert>
#include <string>
#include <sstream>
#include "Vector4.h"

namespace GameMath
{
    class Matrix4x4
    {
    public:
        class COLUMNS{};
        class ROWS{};
        
    private:
        Vector4 m_col[4];
        
    public:
        inline Matrix4x4()
        {
            setCol(0, Vector4::zero());
            setCol(1, Vector4::zero());
            setCol(2, Vector4::zero());
            setCol(3, Vector4::zero());
        }
        
        inline Matrix4x4(const Vector4& _col0, const Vector4& _col1, const Vector4& _col2, const Vector4& _col3, COLUMNS _c)
        {
            setCol(0, _col0);
            setCol(1, _col1);
            setCol(2, _col2);
            setCol(3, _col3);
        }
        
        inline Matrix4x4(const Vector4& _row0, const Vector4& _row1, const Vector4& _row2, const Vector4& _row3,ROWS _r)
        {
            setRow(0, _row0);
            setRow(1, _row1);
            setRow(2, _row2);
            setRow(3, _row3);
        }
        
        inline static Matrix4x4 zero()
        {
            return Matrix4x4 (
                              Vector4::zero(),
                              Vector4::zero(),
                              Vector4::zero(),
                              Vector4::zero(),
                              COLUMNS()
                              );
        }
        
        inline static Matrix4x4 identity()
        {
            return Matrix4x4 (
                              Vector4::unitX(),
                              Vector4::unitY(),
                              Vector4::unitZ(),
                              Vector4::unitW(),
                              COLUMNS()
                              );
        }
        
        inline void setCol(unsigned int _which, const Vector4& _col)
        {
            assert(_which < 4);
            m_col[_which] = _col;
        }
        
        inline Vector4 getCol(unsigned int _which) const
        {
            assert(_which < 4);
            return m_col[_which];
        }
        
        inline void setRow(unsigned int _which, const Vector4& _row)
        {
            assert(_which < 4);
            m_col[0][_which] = _row[0];
            m_col[1][_which] = _row[1];
            m_col[2][_which] = _row[2];
            m_col[3][_which] = _row[3];
        }
        
        inline Vector4 getRow(unsigned int _which) const
        {
            assert(_which < 4);
            return Vector4(m_col[0][_which], m_col[1][_which], m_col[2][_which], m_col[3][_which]);
        }
        
        float& operator() (unsigned int _row, unsigned int _column) { assert(_row < 4 && _column < 4); return m_col[_column][_row]; }
        float operator() (unsigned int _row, unsigned int _column) const { assert(_row < 4 && _column < 4); return m_col[_column][_row]; }
        
        // comparision operations
        inline bool operator==(const Matrix4x4& _other) const { return m_col[0] == _other.getCol(0) && m_col[1] == _other.getCol(0) && m_col[2] == _other.getCol(2) && m_col[3] == _other.getCol(3); }
        inline bool operator!=(const Matrix4x4& _other) const { return m_col[0] != _other.getCol(0) || m_col[1] != _other.getCol(0) || m_col[2] != _other.getCol(2) || m_col[3] != _other.getCol(3); }
        
        // assignment operations
        inline Matrix4x4& operator+=(const Matrix4x4& _other) { m_col[0] += _other.getCol(0); m_col[1] += _other.getCol(1); m_col[2] += _other.getCol(2);m_col[3] += _other.getCol(3); return *this; }
        inline Matrix4x4& operator-=(const Matrix4x4& _other) { m_col[0] -= _other.getCol(0); m_col[1] -= _other.getCol(1); m_col[2] -= _other.getCol(2); m_col[3] -= _other.getCol(3); return *this; }
        inline Matrix4x4& operator*=(const float _scalar) { m_col[0] *= _scalar; m_col[1] *= _scalar; m_col[2] *= _scalar; m_col[3] *= _scalar; return *this; }
        inline Matrix4x4& operator/=(const float _scalar) { m_col[0] /= _scalar; m_col[1] /= _scalar; m_col[2] /= _scalar; m_col[3] /= _scalar; return *this; }
        
        // arithmetic operations
        inline Matrix4x4 operator+(const Matrix4x4& _other) const { return Matrix4x4(m_col[0] + _other.getCol(0), m_col[1] + _other.getCol(1), m_col[2] + _other.getCol(2), m_col[3] + _other.getCol(3), COLUMNS()); }
        inline Matrix4x4 operator-(const Matrix4x4& _other) const { return Matrix4x4(m_col[0] - _other.getCol(0), m_col[1] - _other.getCol(1), m_col[2] - _other.getCol(2), m_col[3] - _other.getCol(3), COLUMNS()); }
        inline Matrix4x4 operator*(const float _scalar) const { return Matrix4x4(m_col[0] * _scalar, m_col[1] * _scalar, m_col[2] * _scalar,  m_col[3] * _scalar, COLUMNS()); }
        inline Matrix4x4 operator/(const float _scalar) const { return Matrix4x4(m_col[0] / _scalar, m_col[1] / _scalar, m_col[2] / _scalar, m_col[3] / _scalar, COLUMNS()); }
        Matrix4x4 operator*(Matrix4x4& _other) {
            Vector4 row0 = getRow(0);
            Vector4 row1 = getRow(1);
            Vector4 row2 = getRow(2);
            Vector4 row3 = getRow(3);
            Vector4 oCol0 = _other.getCol(0);
            Vector4 oCol1 = _other.getCol(1);
            Vector4 oCol2 = _other.getCol(2);
            Vector4 oCol3 = _other.getCol(3);
            return Matrix4x4(
                             Vector4(row0.dot(oCol0), row0.dot(oCol1), row0.dot(oCol2), row0.dot(oCol3)),
                             Vector4(row1.dot(oCol0), row1.dot(oCol1), row1.dot(oCol2), row1.dot(oCol3)),
                             Vector4(row2.dot(oCol0), row2.dot(oCol1), row2.dot(oCol2), row2.dot(oCol3)),
                             Vector4(row3.dot(oCol0), row3.dot(oCol1), row3.dot(oCol2), row3.dot(oCol3)),
                             ROWS()); }
        inline Vector4 operator*(Vector4& _other) { return Vector4(getRow(0).dot(_other), getRow(1).dot(_other), getRow(2).dot(_other), getRow(3).dot(_other)); }

        // Matrix4x4 specific functions
        inline Matrix4x4 transpose() const { return Matrix4x4(m_col[0], m_col[1], m_col[2], m_col[3], ROWS()); }
        inline std::string toString() const { std::ostringstream os; os << '[' <<  getRow(0).toString() << "," << getRow(1).toString() << "," << getRow(2).toString() << "," << getRow(3).toString() << ']'; return os.str(); }
        
        float determinant() const
        {
            /* Intel's optimized SSE matrix inverse routine ftp://download.intel.com/design/pentiumiii/sml/24504301.pdf */
            float mat[16];
            float dst[16];
            
            int counter = 0;
            for (int i=0; i<4; i++) {
                for (int j=0; j<4; j++) {
                    mat[counter] = m_col[j][i];
                    counter++;
                }
            }
            
            float tmp[12]; /* temp array for pairs */
            float src[16]; /* array of transpose source matrix */
            float det; /* determinant */
            /* transpose matrix */
            for (int i = 0; i < 4; i++) {
                src[i] = mat[i*4];
                src[i + 4] = mat[i*4 + 1];
                src[i + 8] = mat[i*4 + 2];
                src[i + 12] = mat[i*4 + 3];
            }
            /* calculate pairs for first 8 elements (cofactors) */
            tmp[0] = src[10] * src[15];
            tmp[1] = src[11] * src[14];
            tmp[2] = src[9] * src[15];
            tmp[3] = src[11] * src[13];
            tmp[4] = src[9] * src[14];
            tmp[5] = src[10] * src[13];
            tmp[6] = src[8] * src[15];
            tmp[7] = src[11] * src[12];
            tmp[8] = src[8] * src[14];
            tmp[9] = src[10] * src[12];
            tmp[10] = src[8] * src[13];
            tmp[11] = src[9] * src[12];
            /* calculate first 8 elements (cofactors) */
            dst[0] = tmp[0]*src[5] + tmp[3]*src[6] + tmp[4]*src[7];
            dst[0] -= tmp[1]*src[5] + tmp[2]*src[6] + tmp[5]*src[7];
            dst[1] = tmp[1]*src[4] + tmp[6]*src[6] + tmp[9]*src[7];
            dst[1] -= tmp[0]*src[4] + tmp[7]*src[6] + tmp[8]*src[7];
            dst[2] = tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
            dst[2] -= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];
            dst[3] = tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
            dst[3] -= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];
            /* calculate determinant */
            det=src[0]*dst[0]+src[1]*dst[1]+src[2]*dst[2]+src[3]*dst[3];
            if (det <= FLT_EPSILON) return 0.f;
            
            return det;
        }
        
        Matrix4x4 inverse() const
        {
            Matrix4x4 inverted = Matrix4x4::zero();
            
            /* Intel's optimized SSE matrix inverse routine ftp://download.intel.com/design/pentiumiii/sml/24504301.pdf */
            float mat[16];
            float dst[16];
            
            int counter = 0;
            for (int i=0; i<4; i++) {
                for (int j=0; j<4; j++) {
                    mat[counter] = m_col[j][i];
                    counter++;
                }
            }
            
            float tmp[12]; /* temp array for pairs */
            float src[16]; /* array of transpose source matrix */
            float det; /* determinant */
            /* transpose matrix */
            for (int i = 0; i < 4; i++) {
                src[i] = mat[i*4];
                src[i + 4] = mat[i*4 + 1];
                src[i + 8] = mat[i*4 + 2];
                src[i + 12] = mat[i*4 + 3];
            }
            /* calculate pairs for first 8 elements (cofactors) */
            tmp[0] = src[10] * src[15];
            tmp[1] = src[11] * src[14];
            tmp[2] = src[9] * src[15];
            tmp[3] = src[11] * src[13];
            tmp[4] = src[9] * src[14];
            tmp[5] = src[10] * src[13];
            tmp[6] = src[8] * src[15];
            tmp[7] = src[11] * src[12];
            tmp[8] = src[8] * src[14];
            tmp[9] = src[10] * src[12];
            tmp[10] = src[8] * src[13];
            tmp[11] = src[9] * src[12];
            /* calculate first 8 elements (cofactors) */
            dst[0] = tmp[0]*src[5] + tmp[3]*src[6] + tmp[4]*src[7];
            dst[0] -= tmp[1]*src[5] + tmp[2]*src[6] + tmp[5]*src[7];
            dst[1] = tmp[1]*src[4] + tmp[6]*src[6] + tmp[9]*src[7];
            dst[1] -= tmp[0]*src[4] + tmp[7]*src[6] + tmp[8]*src[7];
            dst[2] = tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
            dst[2] -= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];
            dst[3] = tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
            dst[3] -= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];
            dst[4] = tmp[1]*src[1] + tmp[2]*src[2] + tmp[5]*src[3];
            dst[4] -= tmp[0]*src[1] + tmp[3]*src[2] + tmp[4]*src[3];
            dst[5] = tmp[0]*src[0] + tmp[7]*src[2] + tmp[8]*src[3];
            dst[5] -= tmp[1]*src[0] + tmp[6]*src[2] + tmp[9]*src[3];
            dst[6] = tmp[3]*src[0] + tmp[6]*src[1] + tmp[11]*src[3];
            dst[6] -= tmp[2]*src[0] + tmp[7]*src[1] + tmp[10]*src[3];
            dst[7] = tmp[4]*src[0] + tmp[9]*src[1] + tmp[10]*src[2];
            dst[7] -= tmp[5]*src[0] + tmp[8]*src[1] + tmp[11]*src[2];
            /* calculate pairs for second 8 elements (cofactors) */
            tmp[0] = src[2]*src[7];
            tmp[1] = src[3]*src[6];
            tmp[2] = src[1]*src[7];
            tmp[3] = src[3]*src[5];
            tmp[4] = src[1]*src[6];
            tmp[5] = src[2]*src[5];
            tmp[6] = src[0]*src[7];
            tmp[7] = src[3]*src[4];
            tmp[8] = src[0]*src[6];
            tmp[9] = src[2]*src[4];
            tmp[10] = src[0]*src[5];
            tmp[11] = src[1]*src[4];
            /* calculate second 8 elements (cofactors) */
            dst[8] = tmp[0]*src[13] + tmp[3]*src[14] + tmp[4]*src[15];
            dst[8] -= tmp[1]*src[13] + tmp[2]*src[14] + tmp[5]*src[15];
            dst[9] = tmp[1]*src[12] + tmp[6]*src[14] + tmp[9]*src[15];
            dst[9] -= tmp[0]*src[12] + tmp[7]*src[14] + tmp[8]*src[15];
            dst[10] = tmp[2]*src[12] + tmp[7]*src[13] + tmp[10]*src[15];
            dst[10] -= tmp[3]*src[12] + tmp[6]*src[13] + tmp[11]*src[15];
            dst[11] = tmp[5]*src[12] + tmp[8]*src[13] + tmp[11]*src[14];
            dst[11] -= tmp[4]*src[12] + tmp[9]*src[13] + tmp[10]*src[14];
            dst[12] = tmp[2]*src[10] + tmp[5]*src[11] + tmp[1]*src[9];
            dst[12] -= tmp[4]*src[11] + tmp[0]*src[9] + tmp[3]*src[10];
            dst[13] = tmp[8]*src[11] + tmp[0]*src[8] + tmp[7]*src[10];
            dst[13] -= tmp[6]*src[10] + tmp[9]*src[11] + tmp[1]*src[8];
            dst[14] = tmp[6]*src[9] + tmp[11]*src[11] + tmp[3]*src[8];
            dst[14] -= tmp[10]*src[11] + tmp[2]*src[8] + tmp[7]*src[9];
            dst[15] = tmp[10]*src[10] + tmp[4]*src[8] + tmp[9]*src[9];
            dst[15] -= tmp[8]*src[9] + tmp[11]*src[10] + tmp[5]*src[8];
            /* calculate determinant */
            det=src[0]*dst[0]+src[1]*dst[1]+src[2]*dst[2]+src[3]*dst[3];
            if (det <= FLT_EPSILON) return inverted;
            
            /* calculate matrix inverse */
            det = 1 / det;
            for (int j = 0; j < 16; j++)
                dst[j] *= det;
            
            counter = 0;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    inverted(i, j) = dst[counter];
                    counter++;
                }
            }
            
            return inverted;
        }
    };
}

#endif /* Matrix4x4_h */
