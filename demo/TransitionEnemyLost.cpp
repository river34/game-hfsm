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
    GameEntity* self = (GameEntity*)(_blackboard->getEntry("self"));
    float view = *(float*)(_blackboard->getEntry("view"));
    GameMath::Vector3 forward = GameMath::Quaternion::rotate(self->m_Rotation, GameMath::Vector3::unitZ());
    GameEntity* enemy = (GameEntity*)(_blackboard->getEntry("enemy"));
    return enemy->m_Position.inViewOf(self->m_Position, forward, view) == false;
}