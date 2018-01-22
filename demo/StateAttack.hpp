//
//  StateAttack.hpp
//  GameFSM
//
//  Created by River Liu on 11/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef StateAttack_hpp
#define StateAttack_hpp

#include <stdio.h>
#include "../hfsm/State.hpp"

using namespace FSM;

class StateAttack : public State
{
public:
    StateAttack(const std::string& _name) : State(_name) { }
    virtual ~StateAttack() { }
    void onEnter();
    void onUpdate(const float _deltaTime, const Blackboard* _blackboard);
    void onExit();
    inline static State* create(const std::string& _name) { return new StateAttack(_name); }
};


#endif /* StateAttack_hpp */
