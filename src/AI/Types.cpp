#include "Types.h"

#include "Util/Util.h"

namespace AI
{
    bool DefaultComparator(const Matrix& m0, const Matrix& m1)
    {
        return Util::FindGreatestIndex(m0) == Util::FindGreatestIndex(m1);
    }
}