#pragma once


/*
- parameters that define behavior of agents
- can be altered through mutations 

the parameters are ranged from 0 -> 1

*/
struct genome
{
    // how much risk the agent can take
    float riskTolerance = 0.5f; 

    // how willing the agent is to explore surroundings 
    float explorationTolerance = 0.5f;

    // importance of information received from other agents
    float communication = 0.5f;

    // how willing the agent is stay close to the group
    float cohesion = 0.5f;

    // movement speed of the agents
    float speed = 1.0f;
};