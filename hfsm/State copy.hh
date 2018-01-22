//
//  State.hpp
//  GameFSM
//
//  Created by River Liu on 4/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
// 

#ifndef State_hpp
#define State_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

class Blackboard;
namespace FSM
{
    class State
    {
    protected:
        std::string m_sName;
        
    public:
        typedef State* (*createInstanceFn) (const std::string&);
        
    public:
        State(const std::string& _name) : m_sName(_name) { }
        virtual ~State() { }
        virtual void onEnter() = 0;
        virtual void onUpdate(const float _deltaTime, const Blackboard* _blackboard) = 0;
        virtual void onExit() = 0;
        inline bool operator==(const State& _rhs) const { return m_sName == _rhs.m_sName; }
        inline const std::string getName() const { return m_sName; }
    };
}

#endif /* State.hpp */

