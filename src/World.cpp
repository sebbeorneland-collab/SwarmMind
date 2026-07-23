#include "World.h"
#include "SystemSensors.h"
#include "Agent.h"
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>

World::World()
{
    // updates every agent in the simulation 
    for (uint32_t i = 0; i < 12; i++)
    {
        m_agents.emplace_back(i);
        m_agents.back().setPosition(static_cast<float>(rand() % 1200), static_cast<float>(rand() % 800));

    }

    // creates the initial food supply
    for (size_t i = 0; i < m_maxFood; i++)
    {
        spawnFood();
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

NeuralNetwork World::createChildBrain(const NeuralNetwork& parentA, const NeuralNetwork& parentB)
{
    NeuralNetwork child;

    // weights from parents
    std::vector<float> inputWeights = parentA.getInputHiddenWeights();
    std::vector<float> outputWeights = parentA.getHiddenOutputWeights();

    const auto& parentBInput = parentB.getInputHiddenWeights();
    const auto& parentBOutput = parentB.getHiddenOutputWeights();

    // bias from parents
    std::vector<float> hiddenBiases = parentA.getHiddenBiases();
    std::vector<float> outputBiases = parentA.getOutputBiases();

    const auto& parentBHiddenBiases = parentB.getHiddenBiases();
    const auto& parentBOutputBiases = parentB.getOutputBiases();

    // bias
    for (size_t i = 0; i < hiddenBiases.size(); i++)
    {
        if (rand() % 2 == 0)
        {
            hiddenBiases[i] = parentBHiddenBiases[i];
        }
    }

    for (size_t i = 0; i < outputBiases.size(); i++)
    {
        if (rand() % 2 == 0)
        {
            outputBiases[i] = parentBOutputBiases[i];
        }   
    }

    // crossover 
    for (size_t i = 0; i < inputWeights.size(); i++)
    {
        if (rand() % 2 == 0)
        {
            inputWeights[i] = parentBInput[i];
        }
    }
    
    for (size_t i = 0; i < outputWeights.size(); i++)
    {
        if (rand() % 2 == 0)
        {
            outputWeights[i] = parentBOutput[i];
        }
    }

    // mutation 
    for (float& weight : inputWeights)
    {
        if (rand() % 20 == 0)
        {
            float mutation = (static_cast<float>(rand()) / RAND_MAX * 0.2f - 0.1f); 

            weight += mutation;
        }
    }

    for (float& weight : outputWeights)
    {
        if (rand() % 20 == 0)
        {
            float mutation = (static_cast<float>(rand()) / RAND_MAX * 0.2f - 0.1f); 

            weight += mutation;
        }
    }

    for (float& bias : hiddenBiases)
    {   
        if (rand() % 20 == 0)
        {
            float mutation = (static_cast<float>(rand()) / RAND_MAX * 0.2f - 0.1f);

            bias += mutation;
        }
    }

    for (float& bias : outputBiases)
    {
        if (rand() % 20 == 0)
        {
            float mutation = (static_cast<float>(rand()) / RAND_MAX * 0.2f - 0.1f);

            bias += mutation;
        }
    }



    child.setInputHiddenWeights(inputWeights);
    child.setHiddenOutputWeights(outputWeights);

    child.setHiddenBiases(hiddenBiases);
    child.setOutputBiases(outputBiases);

    return child;
}


void World::spawnFood()
{
    Food food;

    food.x = static_cast<float>(rand() % static_cast<int>(m_worldWidth));
    food.y = static_cast<float>(rand() % static_cast<int>(m_worldHeight));

    m_food.push_back(food);
}

void World::removeFood(size_t index)
{
    if (index < m_food.size())
    {
        m_food.erase(m_food.begin() + index);
    }
}

void World::update(float dt)
{
    std::vector<Agent> newborns;

    for (Agent &agent : m_agents)
    {
        SensorData data = SensorSystem::scan(agent, *this);

        agent.setSensorData(data);

        agent.update(dt);

        vector2 pos = agent.getPosition();

        for (size_t i = 0; i < m_food.size(); i++)
        {
            float dx = m_food[i].x - pos.x;
            float dy = m_food[i].y - pos.y;

            float distance = sqrt(dx * dx + dy * dy);

            if (distance < 10.0f)
            {
                agent.addEnergy(20.0f);

                removeFood(i);
                break;
            }
        } 

        for (size_t i = 0; i < m_threats.size(); i++)
        {
            float dx = m_threats[i].x - pos.x;
            float dy = m_threats[i].y - pos.y;

            float distance = sqrt(dx * dx + dy * dy);

            if (distance < 15.0f)
            {
                const float damagePerSecond = 20.0f;
                agent.takeDamage(damagePerSecond * m_threats[i].dangerLevel * dt);
            }
        }

    }

    for (size_t i = 0; i < m_agents.size(); i++)
    {
        for (size_t j = i + 1; j < m_agents.size(); j++)
        {
            Agent& parentA = m_agents[i];
            Agent& parentB = m_agents[j];

            vector2 posA = parentA.getPosition();
            vector2 posB = parentB.getPosition();

            float dx = posA.x - posB.x;
            float dy = posA.y - posB.y;

            float distance = sqrt( dx * dx + dy * dy);

            if (distance < 20 && parentA.getEnergy() > 90.0f && parentB.getEnergy() > 90.0f && parentA.getHealth() == 100.0f && parentB.getHealth() == 100.0f)
            {
                NeuralNetwork childBrain = createChildBrain(parentA.getBrain(), parentB.getBrain());

                Agent child(m_nextAgentId++, childBrain);

                parentA.addEnergy(-50);
                parentB.addEnergy(-50);

                child.setPosition((posA.x + posB.x) * 0.5f, (posA.y + posB.y) * 0.5f);
                
                vector2 posC = child.getPosition();
                std::cout << "Child spawnd at: " << posC.x << ", " << posC.y << std::endl; 

                newborns.push_back(child);
            }
        }
    } 

    
    for(const Agent& child : newborns)
    {
        m_agents.push_back(child);
    }
    

    m_agents.erase(std::remove_if(m_agents.begin(), m_agents.end(), [](const Agent& agent) {return !agent.isAlive();}), m_agents.end());

    if (m_food.size() < m_maxFood)
    {
        m_foodSpawnTimer += dt;

        while (m_foodSpawnTimer >= m_foodSpawnInterval && m_food.size() < m_maxFood)
        {
            spawnFood();
            m_foodSpawnTimer -= m_foodSpawnInterval;
        }
    }
    else
    {
        m_foodSpawnTimer = 0.0f;
    }
}