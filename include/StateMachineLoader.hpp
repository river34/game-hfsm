//
//  StateMachineLoader.hpp
//  GameFSM
//
//  Created by River Liu on 6/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef StateMachineLoader_hpp
#define StateMachineLoader_hpp

#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>
#include <sstream>
#include "rapidxml/rapidxml.hpp"
#include "StateMachine.hpp"
#include "State.hpp"
#include "MetaState.hpp"
#include "StateFactory.hpp"
#include "TransitionFactory.hpp"
#include "StateMachineLoader.hpp"
using namespace rapidxml;

namespace FSM
{
    class StateMachineLoader
    {
    private:
        static void createStateMachine(xml_node<>* _root_node, StateMachine* _stateMachine, std::vector<State*>& _statePool, std::vector<Transition*>& _transitionPool)
        {
            State* initState = nullptr;
            // iterate over states
            StateMachine::TransitionMap transitionMap = StateMachine::TransitionMap();
            for (xml_node<>* state_node = _root_node->first_node("state"); state_node; state_node = state_node->next_sibling("state"))
            {
                // create state
                auto newState = StateFactory::createInstance(state_node->first_attribute("name")->value());
                assert(newState);
                auto itState = _statePool.end();
                for (auto it = _statePool.begin(); it != _statePool.end(); it++)
                {
                    if (*newState == *(*it))
                    {
                        itState = it;
                        break;
                    }
                }
                if (itState == _statePool.end())
                {
                    _statePool.push_back(newState);
                    itState = _statePool.end()-1;
                }
                
                // if the state is a metastate, create a sub state machine
                if (state_node->first_attribute("meta"))
                {
                    MetaState* metaState = dynamic_cast<MetaState*>(*itState);
                    StateMachine* stateMachine = dynamic_cast<StateMachine*>(metaState);
                    createStateMachine(state_node, stateMachine, _statePool, _transitionPool);
                }
                
                // if the state is an initial state
                if (state_node->first_attribute("initial"))
                {
                    initState = *itState;
                }
                
                // interate over transitions
                StateMachine::Transitions transitions = StateMachine::Transitions();
                for(xml_node<> * transition_node = state_node->first_node("transition"); transition_node; transition_node = transition_node->next_sibling("transition"))
                {
                    StateMachine::TransitionStatePair transitionStatePair;
                    Transition* transition;
                    State* next;
                    int level;
                    auto newTransition = TransitionFactory::createInstance(transition_node->first_attribute("input")->value());
                    assert (newTransition);
                    auto itTrans = _transitionPool.end();
                    for (auto it = _transitionPool.begin(); it != _transitionPool.end(); it++)
                    {
                        if (*newTransition == *(*it))
                        {
                            itTrans = it;
                            break;
                        }
                    }
                    if (itTrans == _transitionPool.end())
                    {
                        _transitionPool.push_back(newTransition);
                        itTrans = _transitionPool.end()-1;
                        transition = _transitionPool.back();
                    }
                    else
                    {
                        transition = *itTrans;
                    }
                    
                    auto newNext = StateFactory::createInstance(transition_node->first_attribute("next")->value());
                    assert(newNext);
                    auto itNext = _statePool.end();
                    for (auto it = _statePool.begin(); it != _statePool.end(); it++)
                    {
                        if (*newNext == *(*it))
                        {
                            itNext = it;
                            break;
                        }
                    }
                    if (itNext == _statePool.end())
                    {
                        _statePool.push_back(newNext);
                        next = _statePool.back();
                    }
                    else
                    {
                        next = *itNext;
                    }
                    if (!(std::istringstream(transition_node->first_attribute("level")->value()) >> level)) level = 0;
                    transitionStatePair = std::make_tuple(transition, next, level, _stateMachine);
                    transitions.push_back(transitionStatePair);
                }
                
                transitionMap.insert(std::pair<State*, StateMachine::Transitions>(*itState, transitions));
            }
            
            _stateMachine->setTransitionMap(transitionMap, initState);
        }
        
    public:
        static void loadStateMachine(const std::string& _filepath, StateMachine* _stateMachine, std::vector<State*>& _statePool, std::vector<Transition*>& _transitionPool)
        {
            std::ifstream theFile (_filepath);
            std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
            buffer.push_back('\0');
            
            // parse the buffer using the xml file parsing library into doc
            xml_document<> doc;
            doc.parse<0>(&buffer[0]);
            
            // find the root node
            xml_node<>* root_node = doc.first_node("fsm");
            
            createStateMachine(root_node, _stateMachine, _statePool, _transitionPool);
        }
    };
}

#endif /* StateMachineLoader_hpp */