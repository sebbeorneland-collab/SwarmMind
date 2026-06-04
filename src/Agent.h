#pragma once

#include <cstdint>

#include "Genome.h"
#include "SystemSensors.h"
#include "NeuralNetwork.h"

// 2D vector for position and movement
struct vector2
{
    float x = 0.0f;
    float y = 0.0f;
};

class Agent
{
public:
    Agent(uint32_t id);

    // update the agent during simulation
    void update(float dt);

    // set initial position
    void setPosition(float x, float y);

    void setSensorData(const SensorData& data);

    const SensorData& getSensorData() const;

    void addEnergy(float amount);

    float getHealth() const;
    float getEnergy() const;

    bool isAlive() const;

    // get current position
    vector2 getPosition() const;

    const NeuralNetwork& getBrain() const;

    Agent(uint32_t id, const NeuralNetwork& brain);

    uint32_t get_id() const;

private:

    std::vector<float> buildInputs(const SensorData& data);

    // unique id
    uint32_t m_id;

    // world position and movement 
    vector2 m_position;
    vector2 m_velocity;

    // random exploration direction
    vector2 m_wanderDirection;

    // energy and health for surival
    float m_energy;
    float m_health;

    // behavior parameters
    genome m_genome;

    // sensor readings 
    SensorData m_sensorData;

    // reasoning and learning
    NeuralNetwork m_brain; 
};