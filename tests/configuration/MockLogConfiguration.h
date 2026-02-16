#ifndef MOCKLOGCONFIGURATION_H
#define MOCKLOGCONFIGURATION_H

#include <gmock/gmock.h>
#include "lumberjack/configuration/LogConfiguration.h"

namespace lumberjack::configuration
{
    class MockLogConfiguration : public LogConfiguration 
    {
        public:
            MOCK_METHOD(
                void, 
                log, 
                (std::type_index source, lumberjack::LogLevel logLevel, const std::string& message)
            );
    };
}

#endif