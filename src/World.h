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

    struct BrainRecord
    {
        NeuralNetwork brain;
        float fitness = 0.0f;
        float age = 0.0f;
        uint32_t foodEaten = 0;
        uint32_t children = 0;

    };

    float m_worldWidth = 1200.0f;
    float m_worldHeight = 800.0f;

    float m_foodSpawnTimer = 0.0f;
    float m_foodSpawnInterval = 1.0f;
    float m_maxFood = 20;

    size_t m_targetPopulation = 12;
    uint32_t m_generation = 1;
    size_t m_eliteCopies = 2;
    float m_lowMutationProbability = 0.02f;
    float m_lowMutationMagnitude = 0.05f;
    float m_highMutationProbability = 0.08f;
    float m_highMutationMagnitude = 0.15f;

    bool m_hasPreviousAverageFitness = false;
    float m_previousAverageFitness = 0.0f;
    std::vector<float> m_recentAverageFitness; 

    std::vector<Agent> m_agents;
    std::vector<Food> m_food;
    std::vector<Threat> m_threats;
    std::vector<BrainRecord> m_generationArchive;

    void spawnFood();
    void archiveDeadAgents();
    void logGenerationStats();
    void startNextGeneration();
    const BrainRecord& selectParentByFitness() const;
    NeuralNetwork createChildBrain(
        const NeuralNetwork& parentA,
        const NeuralNetwork& parentB,
        float mutationProbability = 0.05f,
        float mutationMagnitude = 0.1f
    );


};

