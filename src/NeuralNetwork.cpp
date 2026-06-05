#include "NeuralNetwork.h"
#include "genome.h"
#include "cmath"

const std::vector<float>& NeuralNetwork::getInputHiddenWeights() const
{
    return m_inputHiddenWeights;
}

const std::vector<float>& NeuralNetwork::getHiddenOutputWeights() const
{
    return m_hiddenOutputWeights;
}

const std::vector<float>& NeuralNetwork::getHiddenBiases() const
{
    return m_hiddenBiases;
}

const std::vector<float>& NeuralNetwork::getOutputBiases() const
{
    return m_outputBiases;
}

void NeuralNetwork::setHiddenBiases(const std::vector<float>& biases)
{
    m_hiddenBiases = biases;
}

void NeuralNetwork::setOutputBiases(const std::vector<float>& biases)
{
    m_outputBiases = biases;
}

void NeuralNetwork::setInputHiddenWeights(const std::vector<float>& weights)
{
    m_inputHiddenWeights = weights;
}

void NeuralNetwork::setHiddenOutputWeights(const std::vector<float>& weights)
{
    m_hiddenOutputWeights = weights;
}

NeuralNetwork::NeuralNetwork()
{
    m_inputHiddenWeights.resize(INPUTS * HIDDEN);
    m_hiddenOutputWeights.resize(HIDDEN * OUTPUTS);

    m_hiddenBiases.resize(HIDDEN);
    m_outputBiases.resize(OUTPUTS);

    for (float& weight : m_inputHiddenWeights) 
    {
        weight = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f);
    }

    for (float& weight : m_hiddenOutputWeights) 
    {
        weight = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f);
    }

    for (float& bias : m_hiddenBiases)
    {
        bias = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f);
    }

    for (float& bias : m_outputBiases)
    {
        bias = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f);
    }
}

std::vector<float> NeuralNetwork::evalute(const std::vector<float>& inputs)
{
    std::vector<float> hidden(HIDDEN);

    for (int h = 0; h < HIDDEN; h++)
    {
        float sum = m_hiddenBiases[h];

        for (int i = 0; i < INPUTS; i++)
        {
            sum += inputs[i] * m_inputHiddenWeights[h * INPUTS + i];
        }

        hidden[h] = std::tanh(sum);
    }

    std::vector<float> outputs(OUTPUTS);

    for (int o = 0; o < OUTPUTS; o++)
    {
        float sum = m_outputBiases[o];

        for (int h = 0; h < HIDDEN; h++)
        {
            sum += hidden[h] * m_hiddenOutputWeights[o * HIDDEN + h];
        }

        outputs[o] = std::tanh(sum);
    }

    
    return outputs;
}