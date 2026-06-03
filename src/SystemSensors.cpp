#include "SystemSensors.h"
#include <cmath>
#include "Agent.h"
#include "World.h"

SensorData SensorSystem::scan(const Agent& agent, const World& world)
{
    SensorData data;

    for (const auto& food : world.getFood())
    {
        vector2 pos = agent.getPosition();

        // position for food subtracted by position of agent 
        float dx = food.x - pos.x;
        float dy = food.y - pos.y;

        // distance to the food 
        float distance = std::sqrt(dx * dx + dy * dy);

        // gives info to the brain that the agent sees food
        if (distance < 65)
        {
            FoodInfo info;

            info.distance = distance;

            info.directionX = dx;
            info.directionY = dy;

            data.visibleFood.push_back(info);
        }
    }
    
    for (const auto& threats : world.getThreats())
    {
        vector2 pos = agent.getPosition();

        float dx = threats.x - pos.x;
        float dy = threats.y - pos.y;

        // distance to the food 
        float distance = std::sqrt(dx * dx + dy * dy);

        // gives the info to the brain that the agent sees a threat
        if (distance < 65)
        {
            ThreatInfo info;

            info.distance = distance;

            info.directionX = dx;
            info.directionY = dy;

            data.visibleThreat.push_back(info);
        }
    } 

    return data; 
}