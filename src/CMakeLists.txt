cmake_minimum_required(VERSION 3.16)

project(SwarmMind)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(SwarmMind
    main.cpp
    Agent.cpp
    Simulation.cpp
    World.cpp
    NeuralNetwork.cpp
    SystemSensors.cpp
)

target_link_libraries(SwarmMind
    sfml-graphics
    sfml-window
    sfml-system
)