#ifndef __AI_Layer_h__
#define __AI_Layer_h__

#include "LayerDescriptor.h"
#include "Types.h"
#include "Math.h"

namespace AI
{
    class Layer
    {
    friend class Network;

    public:
        Layer(const LayerDescriptor& descriptor);

    private:
        void ConnectWithPreviousLayer(Matrix* previousLayerActivation);
        void InitWeights();
        void Evaluate();
        Matrix PropagateError(const Matrix& errorPropagation, LayerAdjustments& adjustments);

        Activation g {sigmoid};

        Matrix a;
        Matrix z;
        Matrix w;
        Matrix b;

        Matrix* previousLayerActivation {nullptr};
    };
}

#endif