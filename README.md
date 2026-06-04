# SwarmMind

SwarmMind is an experimental artificial life and swarm intelligence simulation written in C++.

The project explores how autonomous agents can evolve complex behaviors through neural networks, natural selection, reproduction, mutation, and environmental interaction.

## Features

### Neural Network Controlled Agents

Each agent is controlled by a feedforward neural network.

Current network structure:

* 6 inputs
* 8 hidden neurons
* 2 output neurons

Inputs currently include:

* Food direction (X,Y)
* Threat direction (X,Y)
* Energy level
* Health level

Outputs control movement within the simulation world.

---

### Energy System

Agents consume energy continuously while alive.

Agents gain energy by finding and consuming food.

Energy is limited to:
0 - 100

---

### Health System

Health acts as the agent's survival resource.
Agents only die when health reaches zero.

---

### Death and Natural Selection

Dead agents are automatically removed from the simulation.

This creates natural selection pressure:

* Successful agents survive longer.
* Unsuccessful agents eventually die.

---

### Reproduction System

Agents can reproduce when:

* Health = 100
* Energy > 90
* Another healthy agent is nearby

When reproduction occurs:

* Both parents lose energy
* A new child agent is created
* The child spawns between the parents

---

### Genetic Inheritance

Children inherit their neural networks from two parents.

The inheritance process uses:

#### Crossover

Each neural weight is inherited from either parent A or parent B.

Example:

Parent A:
0.8  -0.3  0.5

Parent B:
0.1   0.9 -0.7

Child:
0.8   0.9  0.5

### Mutation

After crossover, random mutations may alter some weights.

Example:
0.80
↓
0.86

Mutations introduce genetic variation into the population.

---

### Current Evolution Cycle
Agent born
↓
Explore environment
↓
Find food
↓
Gain energy
↓
Meet another agent
↓
Reproduce
↓
Pass genes to offspring
↓
Starve
↓
Lose health
↓
Die
---

## Future Goals

### Neural Network Improvements

* Bias neurons
* Larger hidden layers
* Additional sensory inputs
* Memory/recurrent connections

### Evolution Improvements

* Fitness tracking
* Lineage tracking
* Generational statistics
* Adaptive mutation rates

### Environment

* Multiple biomes
* Resource scarcity
* Seasons
* Predators
* Environmental hazards

### Swarm Behaviors

* Flocking
* Group movement
* Colony formation
* Emergent cooperation

---

## Technologies

* C++
* CMake
* Custom Neural Network Implementation
* Evolutionary Algorithms

---

## Project Goal

The long-term goal of SwarmMind is to create an evolving artificial ecosystem where intelligent behavior emerges naturally through evolution rather than hardcoded rules.
