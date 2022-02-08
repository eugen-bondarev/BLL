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
            const Num eta
        );

    private:
        Layer& GetFirstLayer();
        Layer& GetLastLayer();

        void Backpropagation(const TrainingData& miniBatch, NetworkAdjustments& adjustments);
        void CreateAdjustmentsShape(NetworkAdjustments& adjustments);
        void ApplyAndNullifyAdjustments(NetworkAdjustments& adjustments, const size_t miniBatchSize, const Num eta);

        Vec<Layer> layers;
    };
}

#endif