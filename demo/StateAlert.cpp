//
//  StateAlert.cpp
//  GameFSM
//
//  Created by River Liu on 11/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#include <iostream>
#include "StateAlert.hpp"
using namespace FSM;

void StateAlert::onEnter()
{
    std::cout << "enter Alert\n";
}

void StateAlert::onUpdate(const float _deltaTime, const Blackboard* _blackboard)
{
    std::cout << "update Alert\n";
}

void StateAlert::onExit()
{
    std::cout << "exit Alert\n";
}