#ifndef ITIMEPROVIDER_H
#define ITIMEPROVIDER_H

#include <chrono>

namespace lumberjack::time
{
    class ITimeProvider
    {
        public:
            virtual std::chrono::system_clock::time_point now() const = 0;

            virtual ~ITimeProvider() = default;
            ITimeProvider(const ITimeProvider&) = delete;
            auto operator=(const ITimeProvider&) -> ITimeProvider& = delete;
            ITimeProvider(ITimeProvider&&) = delete;
            auto operator=(ITimeProvider&&) -> ITimeProvider& = delete;
    };
};

#endif