//
//  StateFactory.hpp
//  GameFSM
//
//  Created by River Liu on 7/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef StateFactory_hpp
#define StateFactory_hpp

#include <stdio.h>
#include <map>
#include "State.hpp"
#include "StatePatrol.hpp"
#include "StateCombat.hpp"
#include "StateAlert.hpp"
#include "StateAttack.hpp"
#include "StateSearch.hpp"

namespace FSM
{
    class StateFactory
    {
    public:
        static State* createInstance(const std::string& _name)
        {
            State* instance = nullptr;
            if (_name == "Patrol")
                instance = new StatePatrol(_name);
            if (_name == "Search")
                instance = new StateSearch(_name);
            if (_name == "Combat")
                instance = new StateCombat(_name);
            if (_name == "Alert")
                instance = new StateAlert(_name);
            if (_name == "Attack")
                instance = new StateAttack(_name);
            
            return instance;
        }
    };
}

#endif /* StateFactory_hpp */