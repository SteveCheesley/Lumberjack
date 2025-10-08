#ifndef MOCKTIMEPROVIDER_H
#define MOCKTIMEPROVIDER_H

#include "lumberjack/time/ITimeProvider.h"

using lumberjack::time::ITimeProvider;

namespace lumberjack::time
{
    class MockTimeProvider : public ITimeProvider {
        public:
            MockTimeProvider(std::chrono::system_clock::time_point fixedTime)
                : fixedTime(fixedTime) {}

            std::chrono::system_clock::time_point now() const override {
                return fixedTime;
            }   
        private:
            std::chrono::system_clock::time_point fixedTime;
    };
};

#endif