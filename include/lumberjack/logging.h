#ifndef LOGGING_H
#define LOGGING_H

#include "lumberjack/configuration/LogConfigurations.h"

using lumberjack::configuration::LogConfiguration;
using lumberjack::configuration::LogConfigurations;

namespace lumberjack
{
    auto logConfigurations() -> LogConfigurations<LogConfiguration>&;
    void set_logConfigurations(std::unique_ptr<LogConfigurations<LogConfiguration>> logConfigurations);
}

#endif