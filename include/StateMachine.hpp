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
        typedef std::tuple<Transition*, State*, int, StateMachine*> TransitionStatePair;
        typedef std::vector<TransitionStatePair> Transitions;
        typedef std::map<State*, Transitions> TransitionMap;
        typedef struct
        {
            Transition* transition = nullptr;
            State* state = nullptr;
            int level = 0;
            StateMachine* stateMachine = nullptr;
        } UpdateResult;
        
    public:
        TransitionMap m_Transitions;
        State* m_pInitState = nullptr;
        State* m_pCurrState = nullptr;
        
    public:
        inline StateMachine() { }
        inline virtual void setTransitionMap(const TransitionMap& _transitions, State* _initState)
        {
            m_Transitions = _transitions;
            if (_initState != nullptr)
                m_pInitState = _initState;
            else
                m_pInitState = _transitions.begin()->first;
        }
        virtual void onUpdate(const float _deltaTime, const Blackboard* _blackboard) { }
        virtual UpdateResult update(const float _deltaTime, const Blackboard* _blackboard)
        {
            // check if the state machine has a state
            if (m_pCurrState == nullptr)
            {
                m_pCurrState = m_pInitState;
                m_pCurrState->onEnter();
                return UpdateResult();
            }
            
            // try to find a valid transition for the current state
            TransitionStatePair* transitionPair = nullptr;
            auto it = m_Transitions.find(m_pCurrState);
            if (it != m_Transitions.end())
            {
                for (TransitionStatePair transPair : it->second)
                {
                    if (std::get<0>(transPair)->isValid(_blackboard))
                    {
                        transitionPair = &transPair;
                        break;
                    }
                }
            }
            
            UpdateResult result;
            
            // if a valid transition is found, make a result structure
            if (transitionPair != nullptr)
            {
                result = UpdateResult();
                result.transition = std::get<0>(*transitionPair);
                result.state = std::get<1>(*transitionPair);
                result.level = std::get<2>(*transitionPair);
                result.stateMachine = std::get<3>(*transitionPair);
            }
            
            // otherwise, recurse down
            else
            {
                StateMachine* sm = dynamic_cast<StateMachine*>(m_pCurrState);
                if (sm != nullptr)
                    result = sm->update(_deltaTime, _blackboard);
                m_pCurrState->onUpdate(_deltaTime, _blackboard);
            }
            
            // if a transition is pending
            if (result.transition != nullptr)
            {
                // if transititin is at the same level,
                // exit curr state, fire trans, enter next state, update normally
                if (result.level == 0)
                {
                    m_pCurrState->onExit();
                    result.transition->onTransition();
                    setState(result.state);
                    result.transition = nullptr;
                    result.state = nullptr;
                }
                
                // if transition is at a higher level,
                // exit curr, pass update up
                else if (result.level > 0)
                {
                    m_pCurrState->onExit();
                    m_pCurrState = nullptr;
                    result.level --;
                }
                
                // if transition is at a lower level,
                // exit curr, normal update, pass update down
                else
                {
                    result.transition->onTransition();
                    result.stateMachine->updateDown(result.state, -result.level);
                    result.transition = nullptr;
                }
            }
            
            // if no transition is pending, update normally
            else
            {
                onUpdate(_deltaTime, _blackboard);
            }
            
            return result;
        }
        virtual void setState(State* _state)
        {
            m_pCurrState = _state;
            m_pCurrState->onEnter();
        }
        void updateDown(State* state, int level)
        {
            // if not at the top level
            if (level > 0)
            {
                updateDown(state, level-1);
            }
            
            // exit curr state
            if (m_pCurrState != nullptr)
            {
                m_pCurrState->onExit();
                m_pCurrState = nullptr;
            }
            
            // go to next state
            setState(state);
        }
    };
}

#endif /* StateMachine_hpp */
