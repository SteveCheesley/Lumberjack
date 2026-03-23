#include "lumberjack/logging.h"

using lumberjack::configuration::LogConfiguration;
using lumberjack::configuration::LogConfigurations;

namespace lumberjack
{
    auto logConfigurations_storage() -> std::unique_ptr<LogConfigurations<LogConfiguration>>&
    {
        static std::unique_ptr<LogConfigurations<LogConfiguration>> logConfigurations;
        return logConfigurations;
    }

    auto logConfigurations() -> LogConfigurations<LogConfiguration>&
    {
        auto& configurationPointer = logConfigurations_storage();
        if (!configurationPointer)
        {
            // Initialise default and return
            auto defaultLogConfiguration = LogConfiguration();

            static LogConfigurations<LogConfiguration> default_logConfigurations(std::move(defaultLogConfiguration));
            return default_logConfigurations;
        }
        return *configurationPointer;
    }

    void set_logConfigurations(std::unique_ptr<LogConfigurations<LogConfiguration>> logConfigurations) 
    {
        logConfigurations_storage() = std::move(logConfigurations);
    }
}
