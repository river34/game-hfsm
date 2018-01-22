//
//  TransitionEnemySpotted.hpp
//  GameFSM
//
//  Created by River Liu on 6/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef TransitionEnemySpotted_hpp
#define TransitionEnemySpotted_hpp

#include <stdio.h>
#include <iostream>
#include "../hfsm/Transition.hpp"

using namespace FSM;

class TransitionEnemySpotted : public Transition
{
public:
    TransitionEnemySpotted(const std::string& _name) : Transition(_name) { }
    virtual ~TransitionEnemySpotted() { }
    bool isValid(const Blackboard* _blackboard) const;
    void onTransition() const { std::cout << "transition EnemySpotted" << std::endl; }
    inline static Transition* create(const std::string& _name) { return new TransitionEnemySpotted(_name); }
};

#endif /* TransitionEnemySpotted_hpp */