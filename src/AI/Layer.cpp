#include "Layer.h"

namespace AI
{
    // Die Funktion generiert eine zufällige Zahl [-1, 1)
    static Num GenRandomWeight(Num)
    {
        return rand() / static_cast<Num>(RAND_MAX) * 2.0f - 1.0f;
    }

    Layer::Layer(const LayerDescriptor& descriptor) :
        g {descriptor.g},
        a {descriptor.numNeurons, 1},
        z {descriptor.numNeurons, 1},
        b {descriptor.numNeurons, 1}
    {
        b.setRandom();
    }

    void Layer::ConnectWithPreviousLayer(Matrix* previousLayerActivation)
    {
        this->previousLayerActivation = previousLayerActivation;
    }

    void Layer::InitWeights()
    {
        const Matrix& prevA = *previousLayerActivation;
        w = Matrix(a.rows(), prevA.rows());
        w.setRandom();
    }

    void Layer::Evaluate()
    {
        z = w * (*previousLayerActivation) + b;
        a = z.unaryExpr(g.function);
    }

    Matrix Layer::PropagateError(const Matrix& y, LayerAdjustments& adjustments)
    {
        const Matrix delCdelA = a - y;
        const Matrix delAdelZ = z.unaryExpr(g.derivative);
        const Matrix delCdelZ = delCdelA.array() * delAdelZ.array();
        
        const Matrix& biasGradient = delCdelZ;
        const Matrix weightGradient = delCdelZ * previousLayerActivation->transpose();
        const Matrix activationGradient = w.transpose() * delCdelZ;

        adjustments.b -= biasGradient;
        adjustments.w -= weightGradient;

        return activationGradient;
    }
}