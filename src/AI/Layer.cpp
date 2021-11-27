#include "Layer.h"

namespace AI
{
    // Die Funktion generiert eine zufällige Zahl [0, 1)
    static Num GenRandomWeight(Num)
    {
        return rand() / static_cast<Num>(RAND_MAX);
    }

    Layer::Layer(const LayerDescriptor& descriptor) :
        g {descriptor.g},
        a {descriptor.numNeurons, 1},
        z {descriptor.numNeurons, 1},
        b {descriptor.numNeurons, 1}
    {
    }

    void Layer::ConnectWithPreviousLayer(const Matrix* previousLayerActivation)
    {
        this->previousLayerActivation = previousLayerActivation;
    }

    void Layer::InitWeights()
    {
        w = Matrix(a.GetRows(), previousLayerActivation->GetRows(), GenRandomWeight);
    }

    void Layer::Evaluate()
    {
        z = w * (*previousLayerActivation) + b;
        a = z.Apply(g.function);
    }
}