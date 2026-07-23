#include "SystemSensors.h"
#include <cmath>
#include "Agent.h"
#include "World.h"

SensorData SensorSystem::scan(const Agent& agent, const World& world)
{
    constexpr float visionRadius = 65.0f;

    SensorData data;
    const vector2 pos = agent.getPosition();

    FoodInfo nearestFood;
    bool foundFood = false;
    float nearestFoodDistance = visionRadius;

    for (const auto& food : world.getFood())
    {
        const float dx = food.x - pos.x;
        const float dy = food.y - pos.y;
        const float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < nearestFoodDistance)
        {
            nearestFoodDistance = distance;
            nearestFood.distance = distance;
            nearestFood.directionX = dx;
            nearestFood.directionY = dy;
            nearestFood.amount = food.amount;
            foundFood = true;
        }
    }

    if (foundFood)
    {
        data.visibleFood.push_back(nearestFood);
    }

    ThreatInfo nearestThreat;
    bool foundThreat = false;
    float nearestThreatDistance = visionRadius;

    for (const auto& threat : world.getThreats())
    {
        const float dx = threat.x - pos.x;
        const float dy = threat.y - pos.y;
        const float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < nearestThreatDistance)
        {
            nearestThreatDistance = distance;
            nearestThreat.distance = distance;
            nearestThreat.directionX = dx;
            nearestThreat.directionY = dy;
            nearestThreat.amount = threat.dangerLevel;
            foundThreat = true;
        }
    }

    if (foundThreat)
    {
        data.visibleThreat.push_back(nearestThreat);
    }

    return data;
}