//
//  StatePatrol.cpp
//  GameFSM
//
//  Created by River Liu on 6/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#include <iostream>
#include "StatePatrol.hpp"
using namespace FSM;

void StatePatrol::onEnter()
{
    std::cout << "enter Patrol\n";
}

void StatePatrol::onUpdate(const float _deltaTime, const Blackboard* _blackboard)
{
    std::cout << "update Patrol\n";
}

void StatePatrol::onExit()
{
    std::cout << "exit Patrol\n";
}