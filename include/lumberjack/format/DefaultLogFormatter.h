#ifndef DEFAULTLOGFORMATTER_H
#define DEFAULTLOGFORMATTER_H

#include "lumberjack/format/LogMessageFormat.h"
#include "lumberjack/LogLevel.h"
#include <string>

namespace lumberjack::format 
{
    class DefaultLogFormatter
    {
        private:
            LogMessageFormat logMessageFormat;
        public:
            DefaultLogFormatter();
            DefaultLogFormatter(LogMessageFormat LogMessageFormat);
            std::string log(LogLevel logLevel, std::string message);
    };
};

#endif