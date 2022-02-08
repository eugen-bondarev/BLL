#pragma once

#include <string>

namespace AI 
{
    unsigned long long GetTime();

    struct Timer
    {
        Timer(const std::string& label = "");
        ~Timer();

        unsigned long long Read() const;

    private:
        unsigned long long start;
        std::string label;
    };
}