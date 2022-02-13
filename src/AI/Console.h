#pragma once

#include <string>
#include <vector>

namespace AI
{
    namespace Console
    {
        void Add(const std::string& msg);

        void ClearMessages();
        
        std::vector<std::string>& GetMessages();
    }
}