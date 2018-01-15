//
//  StateSearch.cpp
//  GameFSM
//
//  Created by River Liu on 11/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#include <iostream>
#include "StateSearch.hpp"
using namespace FSM;

void StateSearch::onEnter()
{
    std::cout << "enter Search\n";
}

void StateSearch::onUpdate(const float _deltaTime, const Blackboard* _blackboard)
{
    std::cout << "update Search\n";
}

void StateSearch::onExit()
{
    std::cout << "exit Search\n";
}