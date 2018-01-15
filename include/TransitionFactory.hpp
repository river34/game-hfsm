//
//  FSMTransitionFactory.hpp
//  GameFSM
//
//  Created by River Liu on 7/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef TransitionFactory_hpp
#define TransitionFactory_hpp

#include <stdio.h>
#include <map>
#include "Transition.hpp"
#include "TransitionEnemySpotted.hpp"
#include "TransitionEnemyLost.hpp"
#include "TransitionTimeout.hpp"

namespace FSM
{
    class TransitionFactory
    {
    public:
        static Transition* createInstance(const std::string& _name)
        {
            Transition* instance = nullptr;
            if (_name == "EnemySpotted")
                instance = new TransitionEnemySpotted(_name);
            else if (_name == "EnemyLost")
                instance = new TransitionEnemyLost(_name);
            else if (_name == "Timeout")
                instance = new TransitionTimeout(_name);
            
            return instance;
        }
    };
}

#endif /* TransitionFactory_hpp */
