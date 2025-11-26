#ifndef ILOGFORMATTER_H
#define ILOGFORMATTER_H

#include "../LogLevel.h"
#include <string>
#include <typeindex>

namespace lumberjack::format 
{
    class ILogFormatter 
    {
        public:
           virtual std::string formatMessage(std::type_index source, lumberjack::LogLevel level, std::string message) = 0;
    };
}

#endif