#ifndef MOCKLOGCONFIGURATION_H
#define MOCKLOGCONFIGURATION_H

#include "lumberjack/LogLevel.h"

namespace lumberjack::configuration
{
    class MockLogConfiguration
    {
        private:
            int invocationCount_ = 0;
        public:
            void log(std::type_index source, lumberjack::LogLevel logLevel, const std::string& message)
            {
                this->invocationCount_++;
            }

            [[nodiscard]] auto* getInvocationCount() const
            {
                return &this->invocationCount_;
            }
    };
}

#endif