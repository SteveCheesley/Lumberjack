#include "lumberjack/time/SystemTimeProvider.h"

using lumberjack::time::SystemTimeProvider;

namespace lumberjack::time
{
    std::chrono::system_clock::time_point SystemTimeProvider::now() const 
    {
        return std::chrono::system_clock::now();
    }
}