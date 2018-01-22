//
//  Matrix2x2.h
//  GameMathLibrary
//
//  Created by River Liu on 10/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Matrix2x2_h
#define Matrix2x2_h

#include <cmath>
#include <cfloat>
#include <cassert>
#include <string>
#include <sstream>
#include "Vector2.h"

namespace GameMath
{
    class Matrix2x2
    {
    public:
        class COLUMNS{};
        class ROWS{};
        
    private:
        Vector2 m_col[2];
        
    public:
        inline Matrix2x2(const Vector2& _col0, const Vector2& _col1, COLUMNS _c)
        {
            setCol(0, _col0);
            setCol(1, _col1);
        }
        
        inline Matrix2x2(const Vector2& _row0, const Vector2& _row1, ROWS _r)
        {
            setRow(0, _row0);
            setRow(1, _row1);
        }
        
        inline void setCol(unsigned int _which, const Vector2& _col)
        {
            assert(_which < 2);
            m_col[_which] = _col;
        }
        
        inline Vector2 getCol(unsigned int _which) const
        {
            assert(_which < 2);
            return m_col[_which];
        }
        
        inline void setRow(unsigned int _which, const Vector2& _row)
        {
            assert(_which < 2);
            m_col[0][_which] = _row[0];
            m_col[1][_which] = _row[1];
        }
        
        inline Vector2 getRow(unsigned int _which) const
        {
            assert(_which < 2);
            return Vector2(m_col[0][_which], m_col[1][_which]);
        }
        
        // Matrix2x2 specific functions
        inline float determinant() const { return m_col[0][0] * m_col[1][1] - m_col[1][0] * m_col[0][1]; }
        inline std::string toString() const { std::ostringstream os; os << '[' <<  getRow(0).toString() << "," << getRow(1).toString() << ']'; return os.str(); }
    };
}

#endif /* Matrix2x2_h */
