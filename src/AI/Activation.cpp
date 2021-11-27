#include "Activation.h"

namespace AI
{
    namespace Templates
    {
        Num Sigmoid(const Num x)
        {
            return 1.0f / (1.0f + exp(-x));
        }

        Num SigmoidDerivative(const Num x)
        {
            return Sigmoid(x) * (1.0f - Sigmoid(x));
        }
    }

    Activation sigmoid = { Templates::Sigmoid, Templates::SigmoidDerivative };
}