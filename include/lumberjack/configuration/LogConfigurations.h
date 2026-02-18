#ifndef LOGCONFIGURATIONS_H
#define LOGCONFIGURATIONS_H

#include <vector>
#include <string>
#include "lumberjack/configuration/LogConfiguration.h"

namespace lumberjack::configuration
{
    template<typename ConfigurationType>
    class LogConfigurations
    {
        private:
            ConfigurationType default_;
            std::vector<ConfigurationType> configurations_;
        public:
            LogConfigurations() = default;
            LogConfigurations(ConfigurationType defaultConfiguration);
            LogConfigurations(std::vector<ConfigurationType> configurations);
            LogConfigurations(ConfigurationType defaultConfiguration, std::vector<ConfigurationType> configurations);
            void log(std::type_index source, lumberjack::LogLevel logLevel, const std::string& message);
            void add(ConfigurationType LogConfiguration);
            void clearAllConfigurations();
    };

    /*
     * ..:: Template Function Implementations ::..
     */

    template<typename ConfigurationType>
    LogConfigurations<ConfigurationType>::LogConfigurations(ConfigurationType defaultConfiguration) : default_(defaultConfiguration)
    {}

    template<typename ConfigurationType>
    LogConfigurations<ConfigurationType>::LogConfigurations(std::vector<ConfigurationType> configurations) : configurations_(std::move(configurations))
    {}

    template<typename ConfigurationType>
    LogConfigurations<ConfigurationType>::LogConfigurations(
        ConfigurationType defaultConfiguration, 
        std::vector<ConfigurationType> configurations) 
            : default_(defaultConfiguration), configurations_(std::move(configurations))
    {}

    template<typename ConfigurationType>
    void LogConfigurations<ConfigurationType>::log(std::type_index source, lumberjack::LogLevel logLevel, const std::string& message)
    {
    }

    template<typename ConfigurationType>
    void LogConfigurations<ConfigurationType>::add(ConfigurationType logConfiguration)
    {
    }

    template<typename ConfigurationType>
    void LogConfigurations<ConfigurationType>::clearAllConfigurations()
    {   
    }
}

#endif