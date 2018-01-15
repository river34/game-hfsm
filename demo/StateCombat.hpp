//
//  StateCombat.hpp
//  GameFSM
//
//  Created by River Liu on 6/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef StateCombat_hpp
#define StateCombat_hpp

#include <stdio.h>
#include "MetaState.hpp"
using namespace FSM;

class StateCombat : public MetaState
{
public:
    StateCombat(const std::string& _name) : MetaState(_name) { }
    void onEnter();
    void onUpdate(const float _deltaTime, const Blackboard* _blackboard);
    void onExit();
};

#endif /* StateCombat_hpp */