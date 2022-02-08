#include "Metrics.h"

#include <chrono>
#include <iostream>

namespace AI 
{
    unsigned long long GetTime() 
    {
        unsigned long long milliseconds_since_epoch = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
        return milliseconds_since_epoch;
    }

    Timer::Timer(const std::string& label) : label{label}
    {
        start = GetTime();
    }

    unsigned long long Timer::Read() const
    {
        const unsigned long long delta = GetTime() - start;
        return delta;
    }

    Timer::~Timer()
    {
        if (label.empty())
        {
            return;
        }
        
        const unsigned long long delta = Read();
        std::cout << label << " lasted " << delta << " ms\n";
    }
}