//
//  TransitionTimeout.cpp
//  GameFSM
//
//  Created by River Liu on 11/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#include "Blackboard.hpp"
#include "GameEntity.hpp"
#include "TransitionTimeout.hpp"

bool TransitionTimeout::isValid(const Blackboard* _blackboard) const
{
    return true;
}