#include "lumberjack/time/SystemTimeProvider.h"

namespace lumberjack::time
{
    std::chrono::system_clock::time_point SystemTimeProvider::now()
    {
        return std::chrono::system_clock::now();
    }
}