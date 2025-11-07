#include <iomanip>
#include "lumberjack/time/time_functions.h"

std::tm *getUtcTime(ITimeProvider *timeProvider)
{
    // Append the date
    std::chrono::system_clock::time_point now = timeProvider->now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    // Convert to UTC-based tm structure
    return std::gmtime(&time);
}

std::string formatTime(std::tm *timestamp, std::string formatString)
{
    std::ostringstream dateStringStream;
    dateStringStream << std::put_time(timestamp, formatString.c_str());

    return dateStringStream.str();
}