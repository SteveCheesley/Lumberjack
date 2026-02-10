#include <stdexcept>
#include "lumberjack/configuration/LogConfiguration.h"

namespace lumberjack::configuration
{
    LogConfiguration::LogConfiguration(lumberjack::LogLevel maximumLogLevel,
                                       std::unique_ptr<lumberjack::format::ILogFormatter> logFormatter,
                                       std::vector<std::unique_ptr<lumberjack::writer::ILogWriter>>&& logWriters) 
                                       : maximumLogLevel_(maximumLogLevel), 
                                       logFormatter_(std::move(logFormatter))
    {
        // Validate input pointers
        if (!logFormatter)
        {
            throw std::invalid_argument("logFormatter cannot be null!");
        }

        for (const auto& logWriter: logWriters)
        {
            if (!logWriter)
            {
                throw std::invalid_argument("A Log Writer cannot be null!");
            }
        }

        logWriters_ = std::move(logWriters);
    }

    void LogConfiguration::log(std::type_index source, lumberjack::LogLevel logLevel, const std::string& message)
    {
        // TODO - Let's build this out now we have the desired unit test

        // [1] - Let's format the given input first


        // [2] - Once we have formatted input let's dispatch it to every writer

    }
}