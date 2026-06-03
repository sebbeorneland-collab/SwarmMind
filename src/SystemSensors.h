#pragma once

class Agent;
class World;
#include <vector>


/*
- The agnets should not know where everything is, they should just get information through sensors

*/

// info about detected food source
struct FoodInfo
{
    float distance = 0.0f;

    float directionX = 0.0f;
    float directionY = 0.0f;

    float amount = 0.0f;
};

// info about detectede threat
struct ThreatInfo
{
    float distance = 0.0f;

    float directionX = 0.0f;
    float directionY = 0.0f;

    float amount = 0.0f;
};

// information about other nearby agents
struct AgentInfo
{
    float distance = 0.0f;
};

// info about everything an agent currently can perceive
struct SensorData
{
    std::vector<FoodInfo> visibleFood;
    std::vector<ThreatInfo> visibleThreat;
    std::vector<AgentInfo> nearbyAgents;

};

class SensorSystem
{
public:
    static SensorData scan(const Agent& agnet, const World& world);
};
