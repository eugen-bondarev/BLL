#ifndef __AI_Random_h__
#define __AI_Random_h__

#pragma once

#include <limits>

namespace AI
{
    namespace Util
    {
        namespace Random
        {
            void Reset(const size_t seed = std::numeric_limits<size_t>::max());
        }
    }
}

#endif