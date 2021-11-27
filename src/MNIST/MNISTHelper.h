#ifndef __MNIST_MNISTHelper_h__
#define __MNIST_MNISTHelper_h__

#pragma once

#include "../AI/TrainingData.h"
#include "../AI/Util/Path.h"

namespace MNIST
{
    using namespace AI;
    using namespace AI::Util;

    TrainingData Load(const Path& imagesPath, const Path& labelsPath);
}

#endif