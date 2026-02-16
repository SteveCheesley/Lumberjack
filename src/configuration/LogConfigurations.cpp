#include "lumberjack/configuration/LogConfigurations.h"
#include "lumberjack/format/DefaultLogFormatter.h"
#include "lumberjack/writer/StandardOutputWriter.h"

namespace lumberjack::configuration
{
    LogConfigurations::LogConfigurations() = default;

    LogConfigurations::LogConfigurations(LogConfiguration defaultConfiguration) : default_(std::move(defaultConfiguration))
    {}

    LogConfigurations::LogConfigurations(std::vector<LogConfiguration> configurations) : configurations_(std::move(configurations))
    {}

    LogConfigurations::LogConfigurations(
        LogConfiguration defaultConfiguration, 
        std::vector<LogConfiguration> configurations) 
            : default_(std::move(defaultConfiguration)), configurations_(std::move(configurations))
    {}

    void LogConfigurations::log(std::type_index source, lumberjack::LogLevel logLevel, const std::string& message)
    {
    }

    void LogConfigurations::add(LogConfiguration LogConfiguration)
    {
    }

    void LogConfigurations::clearAllConfigurations()
    {   
    }
}