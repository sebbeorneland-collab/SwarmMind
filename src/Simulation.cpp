#include "Simulation.h"
#include <iostream>

Simulation::Simulation()
{

}

const World& Simulation::getWorld() const
{
    return m_world; 
}

void Simulation::update(float dt)
{
    m_world.update(dt);
}