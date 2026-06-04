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

    void setInputHiddenWeights(const std::vector<float>& weights);
    void setHiddenOutputWeights(const std::vector<float>& weights);

private:
    
    static constexpr int INPUTS = 6;
    static constexpr int HIDDEN = 8;
    static constexpr int OUTPUTS = 2;

    std::vector<float> m_inputHiddenWeights;
    std::vector<float> m_hiddenOutputWeights;

    
};