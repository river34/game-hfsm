//
//  main.cpp
//  GameFSM
//
//  Created by River Liu on 4/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "StateMachine.hpp"
#include "StateMachineLoader.hpp"
#include "State.hpp"
#include "Transition.hpp"
#include "Blackboard.hpp"
#include "GameEntity.hpp"

using namespace FSM;

int main(int argc, const char * argv[])
{
    // create FSM from file
    StateMachine stateMachine = StateMachine();
    vector<State*> statePool = vector<State*>(0);
    statePool.reserve(20);
    vector<Transition*> transitionPool = vector<Transition*>(0);
    transitionPool.reserve(20);
    StateMachineLoader::loadStateMachine("FSMTest1.xml", &stateMachine, statePool, transitionPool);
    
    // check FSM
    std::cout << "# of states: " << statePool.size() << std::endl;
    std::cout << "# of transition: " << transitionPool.size() << std::endl;
    for (auto it = statePool.begin(); it != statePool.end(); it++)
    {
        std::cout << "State: " << (*it)->getName() << std::endl;
    }
    for (auto it = transitionPool.begin(); it != transitionPool.end(); it++)
    {
        std::cout << "Transition: " << (*it)->getName() << std::endl;
    }
    
    // create GameEntities
    GameEntity enemy = GameEntity("Enemy", 10.f);
    enemy.m_Position = GameMath::Vector3(0, 0, 1);
    enemy.m_Rotation = GameMath::Quaternion::identity();
    
    GameEntity self = GameEntity("Self", 10.f);
    self.m_Position = GameMath::Vector3(0, 0, 0);
    self.m_Rotation = GameMath::Quaternion::identity();
    
    // create Blackboard
    Blackboard blackboard = Blackboard();
    blackboard.m_pSelf = &self;
    blackboard.m_pEnemy = &enemy;
    blackboard.m_fView = 1.f;
    
    // run FSM
    clock_t begin = clock();
    while (true)
    {
        stateMachine.update(double(clock() - begin) / CLOCKS_PER_SEC, &blackboard);
    }
    
    return 0;
}
