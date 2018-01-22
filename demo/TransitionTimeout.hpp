//
//  TransitionTimeout.hpp
//  GameFSM
//
//  Created by River Liu on 11/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef TransitionTimeout_hpp
#define TransitionTimeout_hpp

#include <stdio.h>
#include <iostream>
#include "../hfsm/Transition.hpp"

using namespace FSM;

class TransitionTimeout : public Transition
{
public:
    TransitionTimeout(const std::string& _name) : Transition(_name) { }
    virtual ~TransitionTimeout() { }
    bool isValid(const Blackboard* _blackboard) const;
    void onTransition() const { std::cout << "transition Timeout" << std::endl; }
    inline static Transition* create(const std::string& _name) { return new TransitionTimeout(_name); }
};

#endif /* TransitionTimeout_hpp */
