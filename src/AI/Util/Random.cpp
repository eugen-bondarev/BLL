#include "Random.h"

#include <time.h>

namespace AI
{
    namespace Util
    {
        namespace Random
        {
            void Reset(const size_t seed)
            {
                if (seed == std::numeric_limits<size_t>::max())
                {
                    srand(time(0));
                }
                else
                {
                    srand(seed);
                }
            }
        }
    }
}