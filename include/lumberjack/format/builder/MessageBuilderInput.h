#ifndef MESSAGEBUILDERINPUT_H
#define MESSAGEBUILDERINPUT_H

#include <typeindex>

namespace lumberjack::format::builder
{
    struct MessageBuilderInput
    {
        const std::type_index &logMessageSource;

        MessageBuilderInput(std::type_index &logMessageSource) : logMessageSource(logMessageSource) {}
    };
}

#endif