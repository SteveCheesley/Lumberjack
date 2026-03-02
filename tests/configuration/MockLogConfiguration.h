#ifndef MOCKLOGCONFIGURATION_H
#define MOCKLOGCONFIGURATION_H

#include "lumberjack/LogLevel.h"
#include <iostream>

namespace lumberjack::configuration
{
    class MockLogConfiguration
    {
        private:
            std::shared_ptr<int> invocationCount_;
        public:
            MockLogConfiguration() 
            {
                this->invocationCount_ = std::make_shared<int>(0);
            }

            void log(std::type_index source, lumberjack::LogLevel logLevel, const std::string& message)
            {
                ++(*this->invocationCount_);
            }

            [[nodiscard]] auto getInvocationCount()
            {
                return this->invocationCount_;
            }
    };
}

#endif