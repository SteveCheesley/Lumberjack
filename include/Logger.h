#pragma once

#include <string>

namespace logger
{
    enum LogLevel
    {
        ERROR,
        WARNING,
        INFO,
        DEBUG,
        TRACE
    };

    struct LoggerConfiguration
    {
        const bool isDatePrinted;
        const bool isTimePrinted;
        const LogLevel defaultMaxLogLevel;

        LoggerConfiguration(
            bool printDate = true, 
            bool printTime = true, 
            LogLevel defaultLogLevel = LogLevel::INFO) : 
            isDatePrinted(printDate), isTimePrinted(printTime), defaultMaxLogLevel(defaultLogLevel) {};
    };

    class Logger
    {
        public:
            virtual void log(LogLevel level, std::string message) = 0;
    };
}