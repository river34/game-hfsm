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
        MetaState(const std::string& _name) : State(_name) { }
        virtual ~MetaState() { }
        inline void onUpdate(const float _deltaTime, const Blackboard* _blackboard) { }
		inline virtual void setTransitionMap(const TransitionMap& _transitions, State* _initState) { m_Transitions = _transitions; m_pInitState = _initState; }
    };
}

#endif /* MetaState_hpp */