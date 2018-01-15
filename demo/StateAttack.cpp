//
//  StateAttack.cpp
//  GameFSM
//
//  Created by River Liu on 11/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#include <iostream>
#include "StateAttack.hpp"
using namespace FSM;

void StateAttack::onEnter()
{
    std::cout << "enter Attack\n";
}

void StateAttack::onUpdate(const float _deltaTime, const Blackboard* _blackboard)
{
    std::cout << "update Attack\n";
}

void StateAttack::onExit()
{
    std::cout << "exit Attack\n";
}