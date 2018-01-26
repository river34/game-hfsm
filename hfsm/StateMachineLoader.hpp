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
#include "../rapidxml/rapidxml.hpp"
#include "StateMachine.hpp"
#include "State.hpp"
#include "MetaState.hpp"
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
			std::cout << "Creating state machine ............" << std::endl;
            State* initState = nullptr;
            // iterate over states
			std::cout << "Iterate over states" << std::endl;
            StateMachine::TransitionMap transitionMap = StateMachine::TransitionMap();
			std::cout << "_root_node: " << _root_node << std::endl;
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
					std::cout << "Add new state: " << newState->getName() << std::endl;
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
					std::cout << "initState: " << initState->getName() << std::endl;
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
						std::cout << "Add new transition: " << newTransition->getName() << std::endl;
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
						std::cout << "Add new state: " << newState->getName() << std::endl;
                    }
                    else
                    {
                        next = *itNext;
                    }
                    if (!(std::istringstream(transition_node->first_attribute("level")->value()) >> level)) level = 0;
                    transitionStatePair = std::make_tuple(transition, next, level, _stateMachine);
                    transitions.push_back(transitionStatePair);
					std::cout << "Add new transition-state pair: " << transition->getName() << "-" << next->getName() << "-" << level << std::endl;
                }
                
                transitionMap.insert(std::pair<State*, StateMachine::Transitions>(*itState, transitions));
            }
            
            std::cout << transitionMap.size() << std::endl;
            std::cout << initState->getName() << std::endl;
            
            _stateMachine->setTransitionMap(transitionMap, initState);
        }
        
    public:
        void loadStateMachine(const std::string& _file, StateMachine* _stateMachine, std::vector<State*>& _statePool, std::vector<Transition*>& _transitionPool, StateFactory* _stateFactory, TransitionFactory* _transitionFactory, bool _isFilepath)
        {
			std::vector<char> buffer;

			if (_isFilepath == true)
			{
				std::ifstream theFile(_file);
				buffer = std::vector<char>((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
				std::cout << "Read filepath" << std::endl;
			}
			else
			{
				buffer = std::vector<char>(_file.begin(), _file.end());
				std::cout << "Read file as string" << std::endl;
			}

			buffer.push_back('\0');

			std::cout << "Loaded file size: " << buffer.size() << std::endl;

			if (buffer.size() <= 1) return;
            
            // parse the buffer using the xml file parsing library into doc
            xml_document<> doc;
            doc.parse<0>(&buffer[0]);

			std::cout << "Parsed the buffer using the xml file parsing library" << std::endl;
            
            // find the root node
            xml_node<>* root_node = doc.first_node("fsm");

			std::cout << "root_node: " << root_node << std::endl;
            
            createStateMachine(root_node, _stateMachine, _statePool, _transitionPool, _stateFactory, _transitionFactory);
        }
    };
}

#endif /* StateMachineLoader_hpp */