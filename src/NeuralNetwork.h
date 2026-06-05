#pragma once

#include <vector>
#include <iostream>

class NeuralNetwork 
{
public:
    NeuralNetwork();

    std::vector<float> evalute(const std::vector<float>& inputs);

    const std::vector<float>& getInputHiddenWeights() const;
    const std::vector<float>& getHiddenOutputWeights() const;
    const std::vector<float>& getHiddenBiases() const;
    const std::vector<float>& getOutputBiases() const;

    void setInputHiddenWeights(const std::vector<float>& weights);
    void setHiddenOutputWeights(const std::vector<float>& weights);
    void setHiddenBiases(const std::vector<float>& biases);
    void setOutputBiases(const std::vector<float>& biases);



private:
    
    static constexpr int INPUTS = 6;
    static constexpr int HIDDEN = 8;
    static constexpr int OUTPUTS = 2;

    std::vector<float> m_inputHiddenWeights;
    std::vector<float> m_hiddenOutputWeights;
    
    std::vector<float> m_hiddenBiases;
    std::vector<float> m_outputBiases;
    
};