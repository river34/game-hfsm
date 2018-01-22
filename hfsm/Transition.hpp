//
//  Transition.hpp
//  GameFSM
//
//  Created by River Liu on 4/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
// Each transition extends from FSMTransition.
//

#ifndef Transition_hpp
#define Transition_hpp

#include <stdio.h>
#include <string>

class Blackboard;
namespace FSM
{
    class Transition
    {
    protected:
        std::string m_sName;
        
    public:
        typedef Transition* (*createInstanceFn) (const std::string&);
        
    public:
        Transition(const std::string& _name) : m_sName(_name) { }
        virtual ~Transition() { }
        virtual bool isValid(const Blackboard* _blackboard) const { return true; }
        virtual void onTransition() { }
        inline bool operator==(const Transition& _rhs) const { return m_sName == _rhs.m_sName; }
        inline const std::string getName() const { return m_sName; }
    };
}

#endif /* Transition.hpp */
