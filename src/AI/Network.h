#ifndef __AI_Network_h__
#define __AI_Network_h__

#pragma once

#include "NetworkDescriptor.h"
#include "Layer.h"
#include "Types.h"

namespace AI
{
    class Network
    {
    public:
        Network(const NetworkDescriptor& descriptor);
        Network(const Network& original);

        Matrix Feedforward(const Matrix& input);
        void SGD(
            const TrainingData& trainingData, 
            const size_t numEpochs, 
            const size_t miniBatchSize, 
            const Num eta,
            const TrainingData& testData = {},
            const TestComparator& comparator = DefaultComparator
        );

    private:
        Layer& GetFirstLayer();
        Layer& GetLastLayer();

        float Test(const TrainingData& testData, const TestComparator& comparator);

        void Backpropagation(const TrainingData& miniBatch, NetworkAdjustments& adjustments);
        NetworkAdjustments CreateAdjustmentsShape();
        void ApplyAdjustments(NetworkAdjustments& adjustments, const size_t miniBatchSize, const Num eta);

        Vec<Layer> layers;
    };
}

#endif