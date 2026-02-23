#ifndef LOGGER_H
#define LOGGER_H

#include <typeindex>
#include <string>
#include "lumberjack/LogLevel.h"

namespace lumberjack
{
    class Logger
    {
        private:
            std::type_index source_;
        public:
            explicit Logger(std::type_index source);
            ~Logger();

            Logger(const Logger&) = delete;
            auto operator=(const Logger&) -> Logger& = delete;
            Logger(Logger&&) = delete;
            auto operator=(Logger&&) -> Logger& = delete;

            void log(LogLevel logLevel, std::string logMessage);
            void info(std::string message);
            void warn(std::string message);
            void error(std::string message);
            void debug(std::string message);
            void trace(std::string message);
    };    
}

#endif