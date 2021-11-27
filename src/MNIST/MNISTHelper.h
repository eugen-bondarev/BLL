#ifndef __MNIST_MNISTHelper_h__
#define __MNIST_MNISTHelper_h__

#pragma once

#include "../AI/TrainingData.h"

namespace MNIST
{
    using namespace AI;

    TrainingData Load(const Str& imagesPath, const Str& labelsPath);
}

#endif