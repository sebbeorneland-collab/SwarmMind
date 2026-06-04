#include "Agent.h"
#include "NeuralNetwork.h"
#include <iostream>

Agent::Agent(uint32_t id) : m_id(id), 
                            m_position{0.0f, 0.0f}, 
                            m_velocity{0.0f, 0.0f}, 
                            m_energy(100.0f), 
                            m_health(100.f)
                            {

                                m_wanderDirection.x = static_cast<float>((rand() % 200) - 100);
                                m_wanderDirection.y = static_cast<float>((rand() % 200) - 100);
                            }

Agent::Agent(uint32_t id, const NeuralNetwork& brain) : m_id(id), 
                                                        m_brain(brain), 
                                                        m_position{0.0f, 0.0f},
                                                        m_velocity{0.0f, 0.0f},    
                                                        m_energy(100.0f),
                                                        m_health(100.0f)
                                                        {
                                                            m_wanderDirection.x = static_cast<float>((rand() % 200) - 100);
                                                            m_wanderDirection.y = static_cast<float>((rand() % 200) - 100);
                                                        }


uint32_t Agent::get_id() const
{
    return m_id;
}

void Agent::setPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}

vector2 Agent::getPosition() const
{
    return m_position;
}

void Agent::setSensorData(const SensorData& data)
{
    m_sensorData = data;
}

const SensorData& Agent::getSensorData() const
{
    return m_sensorData;
}

void Agent::addEnergy(float amount)
{
    m_energy += amount;

    if (m_energy > 100.0f)
    {
        m_energy = 100.0f; 
    }
}

const NeuralNetwork& Agent::getBrain() const
{
    return m_brain;
}

float Agent::getHealth() const 
{
    return m_health;
}

float Agent::getEnergy() const
{
    return m_energy;
}

bool Agent::isAlive() const
{
    return m_health > 0.0f; 
}

std::vector<float> Agent::buildInputs(const SensorData& data)
{
    std::vector<float> inputs;

    float foodDirX = m_wanderDirection.x;
    float foodDirY = m_wanderDirection.y;

    float threatDirX = 0.0f;
    float threatDirY = 0.0f;

    if (!data.visibleThreat.empty())
    {
        threatDirX = data.visibleThreat[0].directionX;
        threatDirY = data.visibleThreat[0].directionY;
    }

    if (!data.visibleFood.empty())
    {
        foodDirX = data.visibleFood[0].directionX;
        foodDirY = data.visibleFood[0].directionY;
    }

    inputs.push_back(foodDirX);
    inputs.push_back(foodDirY);

    inputs.push_back(threatDirX);
    inputs.push_back(threatDirY);

    inputs.push_back(m_energy);
    inputs.push_back(m_health);

    return inputs;
}

void Agent::update(float dt)
{
    m_energy -= 0.01f * dt;

    if (m_energy < 0.0f)
    {
        m_energy = 0; 
    }

    if (m_energy <= 0.0f)
    {
        m_health -=0.01f * dt;
    }

    if (m_health < 0.0f)
    {
        m_health = 0.0f;
    }

    const float speed = 0.5f;

    std::vector<float> inputs = buildInputs(m_sensorData);
    std::vector<float> outputs = m_brain.evalute(inputs);

    m_velocity.x = outputs[0] * speed;
    m_velocity.y = outputs[1] * speed;

    // movement accordning to current velocity
    m_position.x += m_velocity.x * dt;
    m_position.y += m_velocity.y * dt;


    if (rand() % 2500 == 0 && m_sensorData.visibleFood.empty() && m_sensorData.visibleThreat.empty())
    {
        m_wanderDirection.x = static_cast<float>((rand() % 200) - 100);
        m_wanderDirection.y = static_cast<float>((rand() % 200) - 100);
    }
}