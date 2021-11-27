#include "Activation.h"

namespace AI
{
    namespace Templates
    {
        Num Sigmoid(const Num x)
        {
            return 1.0f / (1.0f + exp(-x));
        }
    }

    Activation sigmoid = { Templates::Sigmoid };
}