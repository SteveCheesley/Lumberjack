#include <chrono>

#include "lumberjack/format/builder/TimeMessageAppender.h"
#include "lumberjack/format/LogMessageFormat.h"
#include "lumberjack/time/SystemTimeProvider.h"
#include "lumberjack/time/time_functions.h"

namespace lumberjack::format::builder
{
    TimeMessageAppender::TimeMessageAppender(const lumberjack::format::LogMessageFormat &inputLogMessageFormat)
        : TimeMessageAppender(inputLogMessageFormat, new lumberjack::time::SystemTimeProvider())
    {
    }

    TimeMessageAppender::TimeMessageAppender(
        const lumberjack::format::LogMessageFormat &inputLogMessageFormat,
        lumberjack::time::ITimeProvider *timeProvider) : AbstractMessageBuilder(),
        logMessageFormat(inputLogMessageFormat),
        timeProvider(timeProvider)
    {
    }
    bool TimeMessageAppender::canAddToMessage()
    {
        return this->logMessageFormat.isTimePrinted();
    }

    std::string TimeMessageAppender::doMessageBuild(builder::MessageBuilderInput* input)
    {
        std::tm* utcTime = getUtcTime(timeProvider);
        std::string dateString = formatTime(utcTime, "%H:%M:%S ");

        return dateString;
    }
}