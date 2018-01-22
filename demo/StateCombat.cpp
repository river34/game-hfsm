//
//  StateCombat.cpp
//  GameFSM
//
//  Created by River Liu on 6/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#include <iostream>
#include "StateCombat.hpp"

using namespace FSM;

void StateCombat::onEnter()
{
    std::cout << "enter Combat\n";
}

void StateCombat::onUpdate(const float _deltaTime, const Blackboard* _blackboard)
{
    std::cout << "update Combat\n";
    MetaState::onUpdate(_deltaTime, _blackboard);
}

void StateCombat::onExit()
{
    std::cout << "exit Combat\n";
}