//
//  TransitionEnemyLost.cpp
//  GameFSM
//
//  Created by River Liu on 11/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#include "Blackboard.hpp"
#include "GameEntity.hpp"
#include "TransitionEnemyLost.hpp"

bool TransitionEnemyLost::isValid(const Blackboard* _blackboard) const
{
    GameMath::Vector3 forward = GameMath::Quaternion::rotate(_blackboard->m_pSelf->m_Rotation, GameMath::Vector3::unitZ());
    return _blackboard->m_pEnemy->m_Position.inViewOf(_blackboard->m_pSelf->m_Position, forward, _blackboard->m_fView) == false;
}