#include "Network.h"

namespace AI
{
    Network::Network(const NetworkDescriptor& descriptor)
    {
        layers.reserve(descriptor.size());
        layers.emplace_back(descriptor[0]);

        for (size_t i = 1; i < descriptor.size(); ++i)
        {
            Layer& layer = layers.emplace_back(descriptor[i]);
            layer.ConnectWithPreviousLayer(&layers[i - 1].a);
            layer.InitWeights();
        }        
    }

    Network::Network(const Network& original) : layers{original.layers}
    {
        for (size_t i = 1; i < layers.size(); ++i)
        {
            layers[i].ConnectWithPreviousLayer(&layers[i - 1].a);
        }
    }
}