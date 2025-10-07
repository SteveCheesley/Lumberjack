#include "lumberjack/format/DefaultLogFormatter.h"
#include "lumberjack/time/SystemTimeProvider.h"

using lumberjack::time::SystemTimeProvider;

namespace lumberjack::format
{
    DefaultLogFormatter::DefaultLogFormatter() 
        : DefaultLogFormatter(LogMessageFormat(true, true, true))
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

    std::string DefaultLogFormatter::formatMessage(LogLevel logLevel, std::string message)
    {
        // TODO - Formatting logic goes here
        return "output-goes-here";
    }
};