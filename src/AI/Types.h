#ifndef __AI_Types_h__
#define __AI_Types_h__

#pragma once

#include "Math.h"

#include <vector>
#include <functional>

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
    using TestData = TrainingData;
    using TestComparator = std::function<bool(const Matrix& m0, const Matrix& m1)>;
    bool DefaultComparator(const Matrix& m0, const Matrix& m1);

    struct LayerAdjustments
    {
        Matrix w;
        Matrix b;
    };

    using NetworkAdjustments = Vec<LayerAdjustments>;
}

#endif