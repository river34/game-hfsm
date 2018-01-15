//
//  StateSearch.hpp
//  GameFSM
//
//  Created by River Liu on 11/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef StateSearch_hpp
#define StateSearch_hpp

#include <stdio.h>
#include "State.hpp"
using namespace FSM;

class StateSearch : public State
{
public:
    StateSearch(const std::string& _name) : State(_name) { }
    void onEnter();
    void onUpdate(const float _deltaTime, const Blackboard* _blackboard);
    void onExit();
};

#endif /* StateSearch_hpp */
