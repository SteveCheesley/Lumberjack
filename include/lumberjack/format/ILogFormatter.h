#ifndef ILOGFORMATTER_H
#define ILOGFORMATTER_H

#include "../LogLevel.h"
#include <string>

namespace lumberjack::format 
{
    class ILogFormatter 
    {
        public:
           std::string formatMessage(lumberjack::LogLevel level, std::string message);
    };
}

#endif