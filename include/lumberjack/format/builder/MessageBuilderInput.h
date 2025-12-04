#ifndef MESSAGEBUILDERINPUT_H
#define MESSAGEBUILDERINPUT_H

#include "lumberjack/LogLevel.h"
#include <typeindex>

namespace lumberjack::format::builder
{
    struct MessageBuilderInput
    {
        const std::type_index &logMessageSource;
        const LogLevel &logLevel;

        MessageBuilderInput(
            const std::type_index &logMessageSource,
            const LogLevel &logLevel) : logMessageSource(logMessageSource),
                                        logLevel(logLevel)
        {
        }
    };
}

#endif