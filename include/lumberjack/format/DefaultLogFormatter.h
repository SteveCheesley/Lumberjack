#ifndef DEFAULTLOGFORMATTER_H
#define DEFAULTLOGFORMATTER_H

#include "lumberjack/format/LogMessageFormat.h"
#include "lumberjack/LogLevel.h"
#include "lumberjack/format/ILogFormatter.h"
#include "lumberjack/time/ITimeProvider.h"
#include <string>

using lumberjack::time::ITimeProvider;

namespace lumberjack::format 
{
    class DefaultLogFormatter : public ILogFormatter
    {
        private:
            LogMessageFormat logMessageFormat;
            ITimeProvider* timeProvider;
        public:
            DefaultLogFormatter();
            DefaultLogFormatter(LogMessageFormat LogMessageFormat);
            DefaultLogFormatter(LogMessageFormat LogMessageFormat, ITimeProvider* timeProvider);
            std::string formatMessage(LogLevel logLevel, std::string message);
    };
};

#endif