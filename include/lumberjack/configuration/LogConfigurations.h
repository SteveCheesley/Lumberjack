#ifndef LOGCONFIGURATIONS_H
#define LOGCONFIGURATIONS_H

#include <map>
#include <string>
#include "lumberjack/configuration/LogConfiguration.h"

namespace lumberjack::configuration
{
    class LogConfigurations
    {
        private:
            LogConfiguration default_;
            std::map<std::string, LogConfiguration> configurations_;
        public:
            LogConfigurations();
            void log(std::type_index source, lumberjack::LogLevel logLevel, const std::string& message);
    };
}

#endif