#include "Network.h"

namespace AI
{
    Network::Network(const NetworkDescriptor& descriptor)
    {
        layers.reserve(descriptor.size());
        layers.emplace_back(descriptor[0]);
            
        for (size_t i = 1; i < descriptor.size(); ++i)
        {
            // Wird erst von c++17 unterstützt:
            // Layer& layer = layers.emplace_back(p_descriptor[i]);

            // Alternative:
            layers.emplace_back(descriptor[i]);
            Layer& layer = layers[layers.size() - 1];

            layer.ConnectWithPreviousLayer(&layers[i - 1].a);
            layer.InitWeights();
        }
    }

    Network::Network(const Network& original) : layers {original.layers}
    {
        for (size_t i = 1; i < layers.size(); ++i)
        {
            layers[i].ConnectWithPreviousLayer(&layers[i - 1].a);
        }
    }

    Layer& Network::GetFirstLayer()
    {
        return layers[0];
    }

    Layer& Network::GetLastLayer()
    {
        return layers[layers.size() - 1];
    }

    Matrix Network::Feedforward(const Matrix& input)
    {
        GetFirstLayer().a = input;

        for (size_t i = 1; i < layers.size(); ++i)
        {
            layers[i].Evaluate();
        }

        return GetLastLayer().a;
    }
}