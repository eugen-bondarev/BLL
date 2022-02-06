#include "Network.h"

#include "Util/Util.h"

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
            Layer& layer{ layers[layers.size() - 1] };

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

    void Network::CreateAdjustmentsShape(NetworkAdjustments& adjustments)
    {
        adjustments.resize(layers.size());
        for (size_t l = 1; l < layers.size(); ++l)
        {
            adjustments[l].w = Matrix(layers[l].w.GetRows(), layers[l].w.GetCols());
            adjustments[l].b = Matrix(layers[l].b.GetRows(), layers[l].b.GetCols());
        }
    }

    static TrainingData CreateMiniBatch(const TrainingData& trainingData, const size_t miniBatchSize, const size_t sample)
    {
        TrainingData miniBatch{ miniBatchSize };
        for (size_t i = 0; i < miniBatchSize; i++)
        {
            const size_t trainingDataIndex{ static_cast<size_t>((sample / static_cast<Num>(trainingData.size())) * (trainingData.size() - miniBatchSize) + i) };
            miniBatch[i] = trainingData[trainingDataIndex];
        }
        return miniBatch;
    }

    void Network::Backpropagation(const TrainingData& miniBatch, NetworkAdjustments& adjustments)
    {
        for (const TrainingSample& sample : miniBatch)
        {
            Feedforward(sample.input);
            Matrix y{ sample.output };

            for (size_t l = layers.size(); l--> 1;)
            {
                const Matrix errorPropagation{ layers[l].PropagateError(y, adjustments[l]) };
                y = layers[l - 1].a - errorPropagation;
            }
        }
    }

    void Network::ApplyAndNullifyAdjustments(NetworkAdjustments& adjustments, const size_t miniBatchSize, const Num eta)
    {
        for (size_t l = 1; l < layers.size(); ++l)
        {
            layers[l].w += adjustments[l].w * (eta / miniBatchSize);
            layers[l].b += adjustments[l].b * (eta / miniBatchSize);

            adjustments[l].w.Nullify();
            adjustments[l].b.Nullify();
        }
    }

    void Network::SGD(const TrainingData& trainingData, const size_t miniBatchSize, const size_t numEpochs, const Num eta)
    {
        for (size_t epoch = 0; epoch < numEpochs; ++epoch)
        {
            const TrainingData shuffled{ Util::Shuffle(trainingData) };

            NetworkAdjustments adjustments{};
            CreateAdjustmentsShape(adjustments);
            for (size_t sample = 0; sample < shuffled.size(); sample += miniBatchSize)
            {
                const TrainingData miniBatch{ CreateMiniBatch(shuffled, miniBatchSize, sample) };
                Backpropagation(miniBatch, adjustments);
                ApplyAndNullifyAdjustments(adjustments, miniBatchSize, eta);
            }
        }
    }
}