//
//  Blackboard.hpp
//  GameFSM
//
//  Created by River Liu on 6/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Blackboard_hpp
#define Blackboard_hpp

#include <stdio.h>
#include "gamemath/Vector3.h"

#endif /* Blackboard_hpp */

class GameEntity;
class Blackboard
{
public:
    GameEntity* m_pSelf;
    GameEntity* m_pEnemy;
    GameMath::Vector3 m_LastKnownPosition;
    float m_fView;

};