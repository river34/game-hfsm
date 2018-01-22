//
//  SQT.h
//  GameMathLibrary
//
//  Created by River Liu on 10/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef SQT_h
#define SQT_h

#include "Quaternion.h"
#include "Vector3.h"

namespace GameMath
{
    /* non-uniform scale */
    class SQT12
    {
        Vector3 scale;
        Quaternion rotation;
        Vector3 translation;
    };
    
    /* uniform scale */
    class SQT10
    {
        float scale;
        Quaternion rotation;
        Vector3 translation;
    };
}

#endif /* SQT_h */
