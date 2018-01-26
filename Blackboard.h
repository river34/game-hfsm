//
//  Blackboard.h
//  GameFSM
//
//  Created by River Liu on 6/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Blackboard_h
#define Blackboard_h

#include <stdio.h>
#include <string>
#include <map>
#include "gamemath/Vector3.h"

class GameEntity;
class Blackboard
{
private:
    typedef std::map<std::string, void *> EntryMap;
    EntryMap m_EntryMap;
    
public:
    Blackboard() { m_EntryMap = std::map<std::string, void *>(); }
    ~Blackboard() { m_EntryMap.clear(); }
    
    inline void registerEntry(const std::string& _key, void* _pEntry) { m_EntryMap[_key] = _pEntry; }
    inline void * getEntry(const std::string& _key) const
    {
        auto it = m_EntryMap.find(_key);
        if (it != m_EntryMap.end()) return it->second;
        return nullptr;
    }
};

#endif /* Blackboard_h */