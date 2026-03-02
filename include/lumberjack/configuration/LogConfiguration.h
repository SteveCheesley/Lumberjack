#ifndef LOGCONFIGURATION_H
#define LOGCONFIGURATION_H

#include <vector>
#include <memory>
#include <typeindex>
#include "lumberjack/LogLevel.h"
#include "lumberjack/writer/ILogWriter.h"
#include "lumberjack/format/ILogFormatter.h"
#include "lumberjack/format/DefaultLogFormatter.h"
#include "lumberjack/writer/StandardOutputWriter.h"

namespace lumberjack::configuration
{
    class LogConfiguration
    {
        private:
            std::vector<std::unique_ptr<lumberjack::writer::ILogWriter>> logWriters_;
            lumberjack::LogLevel maximumLogLevel_;
            std::unique_ptr<lumberjack::format::ILogFormatter> logFormatter_;

            static std::unique_ptr<lumberjack::format::ILogFormatter> getDefaultLogFormatter() 
            {
                return std::make_unique<lumberjack::format::DefaultLogFormatter>();
            }

            static std::vector<std::unique_ptr<lumberjack::writer::ILogWriter>> getDefaultLogWriters()
            {
                std::vector<std::unique_ptr<lumberjack::writer::ILogWriter>> defaultWriters;
                defaultWriters.push_back(std::make_unique<lumberjack::writer::StandardOutputWriter>());

                return defaultWriters;
            }
        public:
            LogConfiguration();
            LogConfiguration(
                lumberjack::LogLevel maximumLogLevel, 
                std::unique_ptr<lumberjack::format::ILogFormatter> logFormatter,
                std::vector<std::unique_ptr<lumberjack::writer::ILogWriter>>&& logWriters);

            // Delete Copy Constructor to force pointer-safe move
            LogConfiguration(const LogConfiguration& other) = delete;
            LogConfiguration& operator=(const LogConfiguration& other) = delete;

            // Define move operators to facilitate pointer-safe movement
            LogConfiguration(LogConfiguration&& other) noexcept : 
                logWriters_(std::move(other.logWriters_)), 
                maximumLogLevel_(other.maximumLogLevel_), 
                logFormatter_(std::move(other.logFormatter_)) {}
            
            LogConfiguration& operator=(LogConfiguration&& other) noexcept
            {
                if (this != &other) 
                {
                    logWriters_ = std::move(other.logWriters_);
                    maximumLogLevel_ = std::move(other.maximumLogLevel_); 
                    logFormatter_ = std::move(other.logFormatter_);
                }
                return *this;
            }
            
            void log(std::type_index source, lumberjack::LogLevel logLevel, const std::string& message);
    };
}

#endif