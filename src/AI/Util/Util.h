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
        void Shuffle(Vec<T>& vector)
        {
            static auto randomEngine = std::default_random_engine {};
            std::shuffle(std::begin(vector), std::end(vector), randomEngine);
        }
    }    
}

#endif