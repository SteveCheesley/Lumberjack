#include <chrono>

#include "lumberjack/format/DateMessageAppender.h"
#include "lumberjack/format/LogMessageFormat.h"
#include "lumberjack/time/SystemTimeProvider.h"
#include "lumberjack/time/time_functions.h"

namespace lumberjack::format
{
    DateMessageAppender::DateMessageAppender(const LogMessageFormat &inputLogMessageFormat) 
        : DateMessageAppender(inputLogMessageFormat, new lumberjack::time::SystemTimeProvider())
    {
    }

    DateMessageAppender::DateMessageAppender(
        const LogMessageFormat &inputLogMessageFormat,
        lumberjack::time::ITimeProvider* timeProvider) : AbstractMessageBuilder(), 
        logMessageFormat(inputLogMessageFormat),
        timeProvider(timeProvider) 
    {
    }

    bool DateMessageAppender::canAddToMessage()
    {
        return this->logMessageFormat.isDatePrinted();
    }

    std::string DateMessageAppender::doMessageBuild()
    {
        // TODO - Setup the class to pass in a time provider (follow the constructor from the DefaultLogFormatter)
        std::tm* utcTime = getUtcTime(timeProvider);
        std::string dateString = formatTime(utcTime, "%Y-%m-%d");

        return dateString;
    }
}