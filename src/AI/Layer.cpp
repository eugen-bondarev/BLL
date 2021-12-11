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
    }

    void Layer::ConnectWithPreviousLayer(Matrix* previousLayerActivation)
    {
        this->previousLayerActivation = previousLayerActivation;
    }

    void Layer::InitWeights()
    {
        const Matrix& prevA = *previousLayerActivation;
        w = Matrix(a.GetRows(), prevA.GetRows(), GenRandomWeight);
    }

    void Layer::Evaluate()
    {
        z = w * (*previousLayerActivation) + b;
        a = z.Apply(g.function);
    }

    void Layer::PropagateError(const Matrix& y, Matrix& errorPropagation, LayerAdjustments& adjustments)
    {
        const Matrix delCdelA = (a - y) * 2.0f;
        const Matrix delAdelZ = z.Apply(g.derivative);
		const Matrix delCdelZ = delCdelA.EntrywiseProduct(delAdelZ);
        
        const Matrix& biasGradient = delCdelZ;
        const Matrix weightGradient = delCdelZ * previousLayerActivation->Transpose();
        const Matrix activationGradient = w.Transpose() * delCdelZ;

        adjustments.b -= biasGradient;
        adjustments.w -= weightGradient;
        errorPropagation -= activationGradient;

		// Transpose them back.
		previousLayerActivation->Transpose();
		w.Transpose();
    }
}