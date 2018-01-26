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
#include <string>
#include "hfsm/State.hpp"
#include "rapidxml/rapidxml.hpp"

namespace FSM
{
    class StateFactory
    {
    private:
        StateFactory(const StateFactory&) {}
        StateFactory& operator=(const StateFactory&) { return *this; }
        typedef std::map<std::string, State::createInstanceFn> FactoryMap;
        FactoryMap m_FactoryMap;
        
    public:
		StateFactory() { }
        ~StateFactory() { }
        void registerClass(const std::string& name, State::createInstanceFn pfnCreate)
        {
            m_FactoryMap[name] = pfnCreate;
        }
        State* createInstance(const rapidxml::xml_node<>* node)
        {
            FactoryMap::iterator it = m_FactoryMap.find(node->first_attribute("name")->value());
            
            if (it != m_FactoryMap.end())
            {
                return it->second(node->first_attribute("name")->value());
            }
            return nullptr;
        }
    };
}

#endif /* StateFactory_hpp */