#pragma once

#include "World.h"

class Simulation 
{
public:

    Simulation();

    void initialize();
    void update(float dt);

    const World& getWorld() const;

private:
    World m_world;
};