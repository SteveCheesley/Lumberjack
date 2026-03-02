#include "lumberjack/logging.h"
#include "lumberjack/Logger.h"

namespace lumberjack
{
    Logger::Logger(std::type_index source) : source_(source)
    {}

    void Logger::log(LogLevel logLevel, const std::string& logMessage)
    {
        lumberjack::logConfigurations().log(this->source_,logLevel, logMessage);
    }

    void Logger::info(const std::string& message)
    {
        this->log(LogLevel::INFO, message);
    }

    void Logger::warn(const std::string& message)
    {
        this->log(LogLevel::WARNING, message);
    }

    void Logger::error(const std::string& message)
    {
        this->log(LogLevel::ERROR, message);
    }

    void Logger::debug(const std::string& message)
    {
        this->log(LogLevel::DEBUG, message);
    }

    void Logger::trace(const std::string& message)
    {
        this->log(LogLevel::TRACE, message);
    }
}
