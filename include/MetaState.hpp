//
//  MetaState.hpp
//  GameFSM
//
//  Created by River Liu on 6/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef MetaState_hpp
#define MetaState_hpp

#include <stdio.h>
#include <iostream>
#include "State.hpp"
#include "StateMachine.hpp"

namespace FSM
{
    class MetaState : public State, public StateMachine
    {
    public:
        inline MetaState(const std::string& _name) : State(_name) { }
        inline void onEnter() { }
        inline void onUpdate(const float _deltaTime, const Blackboard* _blackboard) { update(_deltaTime, _blackboard); }
        inline void onExit() { }
        inline virtual void setTransitionMap(const TransitionMap& _transitions) { m_Transitions = _transitions; m_pInitState = m_Transitions.begin()->first; }
    };
}

#endif /* MetaState_hpp */