#ifndef __AI_Network_h__
#define __AI_Network_h__

#pragma once

#include "NetworkDescriptor.h"
#include "Layer.h"
#include "Types.h"

#include <atomic>

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

        float GetCurrentEpochProgress() const;
        float GetCurrentSGDProgress() const;
        void StopTraining();
        bool IsTrainingRunning() const;

    private:
        Layer& GetFirstLayer();
        Layer& GetLastLayer();

        float Test(const TrainingData& testData, const TestComparator& comparator);

        void Backpropagation(const TrainingData& miniBatch, NetworkAdjustments& adjustments);
        NetworkAdjustments CreateAdjustmentsShape();
        void ApplyAdjustments(NetworkAdjustments& adjustments, const size_t miniBatchSize, const Num eta);

        Vec<Layer> layers;

        std::atomic<float> currentEpochProgress = 0.f;
        std::atomic<float> currentSgdProgress = 0.f;
        std::atomic<bool> isTrainingRunning = false;
        std::atomic<bool> stopTraining = false;
    };
}

#endif