#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>
// #include <iostream>
#include "lumberjack/format/DefaultLogFormatter.h"
#include "lumberjack/time/SystemTimeProvider.h"

using lumberjack::time::SystemTimeProvider;

namespace lumberjack::format
{
    DefaultLogFormatter::DefaultLogFormatter() 
        : DefaultLogFormatter(LogMessageFormat(true, true, true, true))
    {
    }

    DefaultLogFormatter::DefaultLogFormatter(LogMessageFormat logMessageFormat) 
        : DefaultLogFormatter(logMessageFormat, new SystemTimeProvider())
    {
    }

    DefaultLogFormatter::DefaultLogFormatter(
        LogMessageFormat logMessageFormat, 
        ITimeProvider* timeProvider)
        : logMessageFormat(logMessageFormat), timeProvider(timeProvider)
    {
    }

    std::string DefaultLogFormatter::formatMessage(std::type_index source, LogLevel logLevel, std::string message)
    {
        std::string output = "";

        std::string dateString = "";
        std::string timeString = "";
        std::string sourceString = "";

        if (logMessageFormat.isDatePrinted()) {
            // Append the date
            std::chrono::system_clock::time_point now = timeProvider->now();
            std::time_t time = std::chrono::system_clock::to_time_t(now);

            // Convert to UTC-based tm structure
            std::tm* utc_time = std::gmtime(&time);

            // Use this string stream to build the entire output
            std::ostringstream dateStringStream;
            dateStringStream << std::put_time(utc_time, "%Y-%m-%d");

            dateString = dateStringStream.str();
        }

        // NOTE: This code is terrible, but I want to understand better how time_point works..
        // TODO - This needs to go in a private method - This could actually be a design pattern - better
        if (logMessageFormat.isTimePrinted()) {
            // Append the date
            std::chrono::system_clock::time_point now = timeProvider->now();
            std::time_t time = std::chrono::system_clock::to_time_t(now);

            // Convert to UTC-based tm structure
            std::tm* utc_time = std::gmtime(&time);

            // Use this string stream to build the entire output
            std::ostringstream timeStringStream;
            timeStringStream << std::put_time(utc_time, "%H:%M:%S");

            timeString = timeStringStream.str();
        }

        if (logMessageFormat.isSourcePrinted()) {
            // This is passed in / processed as a type_index
        }

        // I'm seriously thinking COR for this logic
        std::string logLevelString = "";

        switch (logLevel) {
            case ERROR:   logLevelString = "ERROR";
            case WARNING: logLevelString = "WARNING";
            case INFO:    logLevelString = "INFO";
            case DEBUG:   logLevelString = "DEBUG";
            case TRACE:   logLevelString = "TRACE";
        }

        // TODO - figure out why this always picks trace, regardless of what I give it

        output = dateString + " " + 
                 timeString + " " + 
                 "[" + logLevelString + "] " +
                 sourceString + message;
        
        return output;
    }
};