#ifndef __AI_Types_h__
#define __AI_Types_h__

#pragma once

#include "Math.h"

#include <vector>

namespace AI
{
    template <typename T>
    using Vec = std::vector<T>;

    struct TrainingSample
    {
        Matrix input;
        Matrix output;
    };

    using TrainingData = Vec<TrainingSample>;

    struct LayerAdjustments
    {
        Matrix w;
        Matrix b;
    };

    using NetworkAdjustments = Vec<LayerAdjustments>;
}

#endif