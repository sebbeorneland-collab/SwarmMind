#include "Simulation.h"
#include <iostream>

Simulation::Simulation()
{
    //std::cout << "SIMULATION CONSTRUCTOR" << std::endl;
}

const World& Simulation::getWorld() const
{
    return m_world; 
}

void Simulation::update(float dt)
{
    //std::cout << "SIMULATION UPDATE" << std::endl;
    m_world.update(dt);
}