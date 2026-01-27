#include "lumberjack/configuration/LogConfiguration.h"

namespace lumberjack::configuration
{
    LogConfiguration::LogConfiguration(lumberjack::LogLevel maximumLogLevel,
                                       std::unique_ptr<lumberjack::format::ILogFormatter> logFormatter,
                                       std::vector<std::unique_ptr<lumberjack::writer::ILogWriter>> logWriters) 
                                       : logWriters_(std::move(logWriters)), 
                                       maximumLogLevel_(maximumLogLevel), 
                                       logFormatter_(std::move(logFormatter))
    {
    }

    void LogConfiguration::log(std::type_index source, lumberjack::LogLevel logLevel, const std::string& message)
    {
        
    }
}