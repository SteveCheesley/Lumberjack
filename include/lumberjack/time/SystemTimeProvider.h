#ifndef SYSTEMTIMEPROVIDER_H
#define SYSTEMTIMEPROVIDER_H

#include "lumberjack/time/ITimeProvider.h"

namespace lumberjack::time
{
    class SystemTimeProvider : public ITimeProvider
    {
        public:
            std::chrono::system_clock::time_point now() const override;
    };
};

#endif