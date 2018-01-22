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
#include "hfsm/StateMachine.hpp"
#include "hfsm/State.hpp"
#include "hfsm/MetaState.hpp"
#include "StateFactory.hpp"
#include "TransitionFactory.hpp"

using namespace rapidxml;

namespace FSM
{
    class StateMachineLoader
    {
    private:
        void createStateMachine(xml_node<>* _root_node, StateMachine* _stateMachine, std::vector<State*>& _statePool, std::vector<Transition*>& _transitionPool, StateFactory* _stateFactory, TransitionFactory* _transitionFactory)
        {
            State* initState = nullptr;
            // iterate over states
            StateMachine::TransitionMap transitionMap = StateMachine::TransitionMap();
            for (xml_node<>* state_node = _root_node->first_node("state"); state_node; state_node = state_node->next_sibling("state"))
            {
                // create state
                auto newState = _stateFactory->createInstance(state_node);
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
                    createStateMachine(state_node, stateMachine, _statePool, _transitionPool, _stateFactory, _transitionFactory);
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
                    auto newTransition = _transitionFactory->createInstance(transition_node);
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
                    
                    auto newNext = _stateFactory->createInstance(transition_node);
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
            
            std::cout << transitionMap.size() << std::endl;
            std::cout << initState->getName() << std::endl;
            
            _stateMachine->setTransitionMap(transitionMap, initState);
        }
        
    public:
        void loadStateMachine(const std::string& _filepath, StateMachine* _stateMachine, std::vector<State*>& _statePool, std::vector<Transition*>& _transitionPool)
        {
            std::ifstream theFile (_filepath);
            std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
            buffer.push_back('\0');
            
            // parse the buffer using the xml file parsing library into doc
            xml_document<> doc;
            doc.parse<0>(&buffer[0]);
            
            // find the root node
            xml_node<>* root_node = doc.first_node("fsm");
            
            // create factory
            StateFactory* stateFactory = new StateFactory;
            TransitionFactory* transitionFactory = new TransitionFactory;
            
            createStateMachine(root_node, _stateMachine, _statePool, _transitionPool, stateFactory, transitionFactory);
        }
    };
}

#endif /* StateMachineLoader_hpp */