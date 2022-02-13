#include "Console.h"

#include <mutex>

namespace AI
{
    namespace Console
    {
        static std::vector<std::string> messages;

        void Add(const std::string& msg)
        {
            static std::mutex mutex;
            std::lock_guard<std::mutex> lockGuard{ mutex };
            messages.push_back(msg);
        }

        void ClearMessages()
        {
            while (messages.size() > 50)
            {
                messages.erase(std::begin(messages));
            }
        }

        std::vector<std::string>& GetMessages()
        {
            return messages;
        }
    }
}