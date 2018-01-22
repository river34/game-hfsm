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
#include "../hfsm/MetaState.hpp"

using namespace FSM;

class StateCombat : public MetaState
{
public:
    StateCombat(const std::string& _name) : MetaState(_name) { }
    virtual ~StateCombat() { }
    void onEnter();
    void onUpdate(const float _deltaTime, const Blackboard* _blackboard);
    void onExit();
    inline static State* create(const std::string& _name) { return new StateCombat(_name); }
};

#endif /* StateCombat_hpp */