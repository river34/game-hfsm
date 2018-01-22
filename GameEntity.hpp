//
//  GameEntity.hpp
//  GameFSM
//
//  Created by River Liu on 6/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef GameEntity_hpp
#define GameEntity_hpp

#include <stdio.h>
#include <string>
#include "gamemath/Vector3.h"
#include "gamemath/Quaternion.h"
using namespace std;

#endif /* GameEntity_hpp */

class GameEntity
{
private:
    string m_sName;
    float m_fHealth = 10.f;
    
public:
    GameMath::Vector3 m_Position;
    GameMath::Quaternion m_Rotation;
    
public:
    inline GameEntity(string _name, float _health) : m_sName(_name), m_fHealth(_health) {}
    inline bool isDead() const { return m_fHealth <= 0.f; }
};