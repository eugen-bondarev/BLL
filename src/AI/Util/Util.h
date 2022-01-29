#ifndef __AI_Util_h__
#define __AI_Util_h__

#pragma once

#include "../Math.h"
#include <algorithm>
#include <random>

namespace AI
{
    namespace Util
    {
        size_t FindGreatestIndex(const Matrix& matrix1D);

        template <typename T>
        Vec<T> Shuffle(const Vec<T>& vector)
        {
            Vec<T> copy{ vector };
            static auto randomEngine = std::default_random_engine{};
            std::shuffle(std::begin(copy), std::end(copy), randomEngine);
            return copy;
        }
    }    
}

#endif