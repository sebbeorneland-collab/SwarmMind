#include "NeuralNetwork.h"
#include "genome.h"

NeuralNetwork::NeuralNetwork()
{
    m_weights.resize(10, 0.5f);
}

std::vector<float> NeuralNetwork::evalute(const std::vector<float>& inputs)
{
    genome m_genome;

    const float riskTolerance = 1.0f;

    float foodDirX= inputs[0];
    float foodDirY = inputs[1];
    
    float threatDirX = inputs[2];
    float threatDirY = inputs[3];

    

    float moveX = foodDirX - threatDirX * riskTolerance;
    float moveY = foodDirY - threatDirY * riskTolerance;

    return {moveX, moveY};
    //return {inputs[0] * 0.05f, inputs[1] * 0.05f};
}