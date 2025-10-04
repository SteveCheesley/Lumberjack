#ifndef DEFAULTLOGFORMATTER_H
#define DEFAULTLOGFORMATTER_H

#include "lumberjack/format/LogMessageFormat.h"
#include "lumberjack/LogLevel.h"
#include "lumberjack/format/ILogFormatter.h"
#include <string>

namespace lumberjack::format 
{
    class DefaultLogFormatter : public ILogFormatter
    {
        private:
            LogMessageFormat logMessageFormat;
        public:
            DefaultLogFormatter();
            DefaultLogFormatter(LogMessageFormat LogMessageFormat);
            std::string formatMessage(LogLevel logLevel, std::string message);
    };
};

#endif