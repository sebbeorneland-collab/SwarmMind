#pragma once

#include "Agent.h"
#include <vector>

class Agent;

// food for agents
struct Food
{
    float x = 0.0f;
    float y = 0.0f;

    float amount = 100.0f;
};

// danger for the agents
struct Threat
{
    float x = 0.0f;
    float y = 0.0f;

    float dangerLevel = 1.0f;

};

class World
{
public: 

    World();
    void update(float dt);

    const std::vector<Food>& getFood() const;
    const std::vector<Threat>& getThreats() const;
    const std::vector<Agent>& getAgents() const;

    void removeFood(size_t index);
    uint32_t m_nextAgentId = 12;

private:
    float m_worldWidth = 100.0f;
    float m_worldHeight = 100.0f;

    std::vector<Agent> m_agents;
    std::vector<Food> m_food;
    std::vector<Threat> m_threats;

    NeuralNetwork createChildBrain(const NeuralNetwork& parentA, const NeuralNetwork& parentB);


};
