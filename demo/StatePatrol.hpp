//
//  StatePatrol.hpp
//  GameFSM
//
//  Created by River Liu on 6/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef StatePatrol_hpp
#define StatePatrol_hpp

#include <stdio.h>
#include "../hfsm/State.hpp"

using namespace FSM;

class StatePatrol : public State
{
public:
    StatePatrol(const std::string& _name) : State(_name) { }
    virtual ~StatePatrol() { }
    void onEnter();
    void onUpdate(const float _deltaTime, const Blackboard* _blackboard);
    void onExit();
    inline static State* create(const std::string& _name) { return new StatePatrol(_name); }
};

#endif /* StatePatrol_hpp */