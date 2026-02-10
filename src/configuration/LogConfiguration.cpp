#include <stdexcept>
#include "lumberjack/configuration/LogConfiguration.h"

namespace lumberjack::configuration
{
    LogConfiguration::LogConfiguration(lumberjack::LogLevel maximumLogLevel,
                                       std::unique_ptr<lumberjack::format::ILogFormatter> logFormatter,
                                       std::vector<std::unique_ptr<lumberjack::writer::ILogWriter>>&& logWriters) 
                                       : maximumLogLevel_(maximumLogLevel)
    {
        // Validate input pointers
        if (!logFormatter)
        {
            throw std::invalid_argument("logFormatter cannot be null!");
        }

        logFormatter_ = std::move(logFormatter);

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
        std::string formattedOutput = this->logFormatter_->formatMessage(source, logLevel, message);

        for (const auto& logWriter : this->logWriters_)
        {
            logWriter->writeToLog(formattedOutput);
        }
    }
}