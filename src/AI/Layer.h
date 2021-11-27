#ifndef __AI_Layer_h__
#define __AI_Layer_h__

#include "LayerDescriptor.h"
#include "Math.h"

namespace AI
{
    class Layer
    {
    friend class Network;

    public:
        Layer(const LayerDescriptor& descriptor);

    private:
        void ConnectWithPreviousLayer(const Matrix* previousLayerActivation);
        void InitWeights();

        Activation g;

        Matrix a;
        Matrix z;
        Matrix w;
        Matrix b;

        const Matrix* previousLayerActivation {nullptr};
    };
}

#endif