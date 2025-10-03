#include "lumberjack/format/DefaultLogFormatter.h"

namespace lumberjack::format
{
    DefaultLogFormatter::DefaultLogFormatter() 
        : DefaultLogFormatter(LogMessageFormat(true, true, true))
    {
    }

    DefaultLogFormatter::DefaultLogFormatter(LogMessageFormat logMessageFormat) 
        : logMessageFormat(logMessageFormat)
    {
    }

    std::string DefaultLogFormatter::log(LogLevel logLevel, std::string message)
    {
        // TODO - Formatting logic goes here
        return "output-goes-here";
    }
};