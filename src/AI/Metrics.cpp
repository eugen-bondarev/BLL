#include "Metrics.h"

#include <chrono>
#include <iostream>

namespace ai 
{
    unsigned long long get_time() 
    {
        unsigned long long milliseconds_since_epoch = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
        return milliseconds_since_epoch;
    }

    Timer::Timer(const std::string& p_label) : label{p_label}
    {
        start = get_time();
    }

    unsigned long long Timer::read() const
    {
        const unsigned long long delta = get_time() - start;
        return delta;
    }

    Timer::~Timer()
    {
        if (label.empty())
        {
            return;
        }
        
        const unsigned long long delta = read();
        std::cout << label << " lasted " << delta << " ms\n";
    }
}