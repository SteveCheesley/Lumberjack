#ifndef ITIMEPROVIDER_H
#define ITIMEPROVIDER_H

#include <chrono>

namespace lumberjack::time
{
    class ITimeProvider
    {
        public:
            virtual std::chrono::system_clock::time_point now() const = 0;
    };
};

#endif