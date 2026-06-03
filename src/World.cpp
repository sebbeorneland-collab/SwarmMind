#include "World.h"
#include "SystemSensors.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>

World::World()
{
    // updates every agent in the simulation 
    for (uint32_t i = 0; i < 12; i++)
    {
        m_agents.emplace_back(i);
        m_agents.back().setPosition(static_cast<float>(rand() % 1200), static_cast<float>(rand() % 800));

    }

    // randomizes food
    for (uint32_t i = 0; i < 10; i++)
    {
        Food food;

        food.x = static_cast<float>(rand() % 1200);
        food.y = static_cast<float>(rand() % 800);

        m_food.push_back(food);
    }

    // randomized threats
    for (uint32_t i = 0; i < 20; i++)
    {
        Threat threat;

        threat.x = static_cast<float>(rand() % 1200);
        threat.y = static_cast<float>(rand() % 800);

        m_threats.push_back(threat);
    }


    for (auto& agent : m_agents)
    {
        SensorData data = SensorSystem::scan(agent, *this);
    }
 }

const std::vector<Food>& World::getFood() const
{
    return m_food;
}

const std::vector<Threat>& World::getThreats() const
{
    return m_threats;
}

const std::vector<Agent>& World::getAgents() const
{
    return m_agents;
}

void World::update(float dt)
{
    for (Agent &agent : m_agents)
    {
        SensorData data = SensorSystem::scan(agent, *this);

        agent.setSensorData(data);

        agent.update(dt);
    }
}