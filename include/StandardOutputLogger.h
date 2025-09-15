#pragma once

#include "Logger.h"

namespace logger
{
    class StandardOutputLogger : public Logger {
        private:
            const LoggerConfiguration& loggerConfiguration;
        public:
            StandardOutputLogger();
            StandardOutputLogger(const LoggerConfiguration& inputLoggerConfiguration);
            void log(LogLevel level, std::string message);
    };
}