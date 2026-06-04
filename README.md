# SwarmMind

SwarmMind is an experimental artificial life simulation written in C++.

The goal of the project is to explore how intelligent behavior can emerge through neural networks, evolution, and environmental interaction rather than hardcoded rules.

## Current Features

### Neural Network Agents

Each agent is controlled by a feedforward neural network.

Current network:

* 6 inputs
* 8 hidden neurons
* 2 outputs

Inputs include:

* Food direction
* Threat direction
* Energy
* Health

Outputs control the agent's movement.

### Energy and Health

Agents lose energy over time.

When an agent finds food, it gains energy.

If energy reaches zero, health begins to decrease.

An agent dies when its health reaches zero.

### Reproduction

Agents can reproduce when:

* Health is full
* Energy is above 90
* Another healthy agent is nearby

When reproduction occurs:

* Both parents lose energy
* A child is created between the parents
* The child inherits a neural network from both parents

### Evolution

Children inherit neural network weights from both parents through crossover.

Small random mutations are applied to create variation in the population.

Over time, successful agents can pass on their traits while unsuccessful agents die out.

## Future Plans

* Bias neurons
* Better neural network architecture
* Additional sensors
* Biomes and environmental variation
* Swarm behaviors
* Statistics and fitness tracking
* More advanced evolutionary mechanisms

## Technologies

* C++
* CMake
* Custom Neural Network
* Evolutionary Algorithms

## Goal

Create a self-sustaining artificial ecosystem where complex behaviors emerge naturally through evolution.

