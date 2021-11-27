#include "AI/Network.h"
#include "AI/Math.h"

int main()
{
    try
    {
        AI::Matrix a = {
            { 1, 4 },
            { 2, 5 },
            { 3, 6 }
        };

        AI::Matrix b = {
            { 10, 11 },
            { 20, 21 },
            { 30, 31 },
        };

        AI::Matrix c = a.Transpose() * b;
        
        LINE_OUT(a.ToString());
        LINE_OUT(b.ToString());
        LINE_OUT(c.ToString());
    }
    catch (const std::runtime_error& error)
    {
        LINE_OUT(error.what());
    }

    return 0;
}