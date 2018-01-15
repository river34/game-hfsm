//
//  TransitionEnemyLost.hpp
//  GameFSM
//
//  Created by River Liu on 11/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef TransitionEnemyLost_hpp
#define TransitionEnemyLost_hpp

#include <stdio.h>
#include <iostream>
#include "Transition.hpp"
using namespace FSM;

class TransitionEnemyLost : public Transition
{
public:
    TransitionEnemyLost(const std::string& _name) : Transition(_name) { };
    bool isValid(const Blackboard* _blackboard) const;
    void onTransition() const { std::cout << "transition EnemyLost" << std::endl; };
};

#endif /* TransitionEnemyLost_hpp */
