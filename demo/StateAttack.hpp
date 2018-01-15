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
#include "State.hpp"
using namespace FSM;

class StateAttack : public State
{
public:
    StateAttack(const std::string& _name) : State(_name) { }
    void onEnter();
    void onUpdate(const float _deltaTime, const Blackboard* _blackboard);
    void onExit();
};


#endif /* StateAttack_hpp */
