#ifndef ILOGCONFIGURATION_H
#define ILOGCONFIGURATION_H

#include <vector>
#include <memory>
#include <typeindex>
#include "lumberjack/LogLevel.h"
#include "lumberjack/writer/ILogWriter.h"
#include "lumberjack/format/ILogFormatter.h"

namespace lumberjack::configuration
{
    class LogConfiguration
    {
        private:
            std::vector<std::unique_ptr<lumberjack::writer::ILogWriter>> logWriters_;
            lumberjack::LogLevel maximumLogLevel_;
            std::unique_ptr<lumberjack::format::ILogFormatter> logFormatter_;
        public:
            LogConfiguration(
                lumberjack::LogLevel maximumLogLevel, 
                std::unique_ptr<lumberjack::format::ILogFormatter> logFormatter,
                std::vector<std::unique_ptr<lumberjack::writer::ILogWriter>> logWriters);
            void log(std::type_index source, lumberjack::LogLevel logLevel, const std::string& message);
    };
}

#endif