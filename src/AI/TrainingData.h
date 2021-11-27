#ifndef __AI_TrainingData_h__
#define __AI_TrainingData_h__

#pragma once

#include "Math.h"

namespace AI
{
    struct TrainingSample
    {
        Matrix input;
        Matrix output;
    };

    using TrainingData = Vec<TrainingSample>;
}

#endif