#ifndef LOGCONFIGURATIONS_H
#define LOGCONFIGURATIONS_H

#include <vector>
#include <string>
#include "lumberjack/configuration/LogConfiguration.h"

namespace lumberjack::configuration
{
    class LogConfigurations
    {
        private:
            LogConfiguration default_;
            std::vector<LogConfiguration> configurations_;
        public:
            LogConfigurations();
            LogConfigurations(LogConfiguration defaultConfiguration);
            LogConfigurations(std::vector<LogConfiguration> configurations);
            LogConfigurations(LogConfiguration defaultConfiguration, std::vector<LogConfiguration> configurations);
            void log(std::type_index source, lumberjack::LogLevel logLevel, const std::string& message);
            void add(LogConfiguration LogConfiguration);
            void clearAllConfigurations();
    };
}

#endif