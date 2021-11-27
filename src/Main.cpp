#include "AI/Network.h"
#include "AI/Math.h"

int main()
{
    try
    {
        srand(time(nullptr));

        AI::Network network({
            {2},
            {4},
            {1}
        });
    }
    catch (const std::runtime_error& error)
    {
        LINE_OUT(error.what());
    }

    return 0;
}