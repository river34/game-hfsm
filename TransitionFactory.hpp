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
#include "hfsm/Transition.hpp"
#include "demo/TransitionEnemySpotted.hpp"
#include "demo/TransitionEnemyLost.hpp"
#include "demo/TransitionTimeout.hpp"
#include "rapidxml/rapidxml.hpp"

namespace FSM
{
    class TransitionFactory
    {
    private:
        TransitionFactory(const TransitionFactory&) {}
        TransitionFactory& operator=(const TransitionFactory&) { return *this; }
        typedef std::map<std::string, Transition::createInstanceFn> FactoryMap;
        FactoryMap m_FactoryMap;
        
    public:
        TransitionFactory()
        {
            registerClass("EnemySpotted", &TransitionEnemySpotted::create);
            registerClass("EnemyLost", &TransitionEnemyLost::create);
            registerClass("Timeout", &TransitionTimeout::create);
        }
        ~TransitionFactory() { }
        void registerClass(const std::string& name, Transition::createInstanceFn pfnCreate)
        {
            m_FactoryMap[name] = pfnCreate;
        }
        Transition* createInstance(const rapidxml::xml_node<>* node)
        {
            FactoryMap::iterator it = m_FactoryMap.find(node->first_attribute("input")->value());
            if (it != m_FactoryMap.end())
            {
                return it->second(node->first_attribute("input")->value());
            }
            return nullptr;
        }
    };
}

#endif /* TransitionFactory_hpp */
