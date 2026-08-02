#include "Simulation.h"
#include "World.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Simulation simulation;
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Swarm Intelligence");

    while(window.isOpen())
    {

        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        constexpr int simulationSpeed = 20;
        for (int i = 0; i < simulationSpeed; i++)
        {   
            simulation.update(0.016f);
        }

        //simulation.update(0.016f);

        window.clear();
        const World& world = simulation.getWorld();

        for (const auto& agent : world.getAgents())
        {
            // vision radius
            vector2 pos = agent.getPosition();

            sf::CircleShape vision(65.f);
            vision.setFillColor(sf::Color::Transparent);
            vision.setOutlineThickness(1.f);

            vision.setOutlineColor(sf::Color(80, 80, 80));

            vision.setOrigin(65.f, 65.f);

            vision.setPosition(pos.x, pos.y);
            window.draw(vision);

            // draw the AI agent
            sf::CircleShape circle(3.f);
            if (!agent.getSensorData().visibleThreat.empty())
            {
                circle.setFillColor(sf::Color::Yellow);
            }
            else
            {
                circle.setFillColor(sf::Color::White);
            }

            circle.setPosition(pos.x, pos.y);
            window.draw(circle);
        }

        for (const auto& food : world.getFood())
        {
            sf::CircleShape circle(3.f);
            circle.setFillColor(sf::Color::Green);
            circle.setPosition(food.x, food.y);
            window.draw(circle);
        }

        for (const auto& threat : world.getThreats())
        {
            sf::CircleShape circle(3.f);
            circle.setFillColor(sf::Color::Red);
            circle.setPosition(threat.x, threat.y);
            window.draw(circle);
        }
        window.display();
    }


    return 0;
}