#pragma once

#include <vector>
#include <iostream>

class NeuralNetwork 
{
public:
    NeuralNetwork();

    std::vector<float> evalute(const std::vector<float>& inputs);

private:
    std::vector<float> m_weights;
};