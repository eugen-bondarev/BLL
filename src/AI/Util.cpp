#include "Util.h"

namespace AI
{
    namespace Util
    {        
        size_t FindGreatestIndex(const Matrix& matrix1D)
        {
            AI_MATRIX_OPERATION_CONDITION(matrix1D.GetCols() == 1, "[FindGreatestIndex(mat input)] input must be 1D.");

            size_t index {0};
            Num value {matrix1D(index, 0)};

            for (size_t i = 0; i < matrix1D.GetRows(); ++i)
            {
                if (matrix1D(i, 0) > value)
                {
                    index = i;
                    value = matrix1D(i, 0);
                }
            }

            return index;
        }
    }
}