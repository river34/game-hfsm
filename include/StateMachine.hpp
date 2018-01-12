//
//  StateMachine.hpp
//  GameFSM
//
//  Created by River Liu on 4/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef StateMachine_hpp
#define StateMachine_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "State.hpp"
#include "Transition.hpp"

class Blackboard;
namespace FSM
{
    //class State;
    //class Transition;
    class StateMachine
    {
    public:
        typedef std::pair<Transition*, State*> TransitionStatePair;
        typedef std::vector<TransitionStatePair> Transitions;
        typedef std::map<State*, Transitions> TransitionMap;
        
    public:
        TransitionMap m_Transitions;
        State* m_pInitState = nullptr;
        State* m_pCurrState = nullptr;
        
    public:
        inline StateMachine() { }
        inline virtual void setTransitionMap(const TransitionMap& _transitions)
        {
            m_Transitions = _transitions;
            m_pInitState = m_Transitions.begin()->first;
        }
        virtual void update(const float _deltaTime, const Blackboard* _blackboard)
        {
            // check if the state machine has a state
            if (m_pCurrState == nullptr)
            {
                m_pCurrState = m_pInitState;
                m_pCurrState->onEnter();
                return;
            }
            
            // try to find a valid transition for the current state
            TransitionStatePair* transitionPair = nullptr;
            auto it = m_Transitions.find(m_pCurrState);
            if (it != m_Transitions.end())
            {
                for (TransitionStatePair transPair : it->second)
                {
                    if (transPair.first->isValid(_blackboard))
                    {
                        transitionPair = &transPair;
                        break;
                    }
                }
            }
            
            // if a valid transition is found, exit current state and fire transition
            if (transitionPair != nullptr)
            {
                m_pCurrState->onExit();
                transitionPair->first->onTransition();
                setState(transitionPair->second);
            }
            
            // otherwise, resursively update current state
            else
            {
                m_pCurrState->onUpdate(_deltaTime, _blackboard);
            }
        }
        virtual void setState(State* _state)
        {
            m_pCurrState = _state;
            m_pCurrState->onEnter();
        }
    };
}

#endif /* StateMachine_hpp */
