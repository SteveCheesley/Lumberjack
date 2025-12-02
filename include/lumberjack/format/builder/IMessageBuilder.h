#ifndef IMESSAGEBUILDER_H
#define IMESSAGEBUILDER_H

#include "lumberjack/format/builder/MessageBuilderInput.h"
#include <string>

namespace lumberjack::format::builder
{
    class IMessageBuilder
    {
        public:
            virtual IMessageBuilder *setNext(IMessageBuilder *messageBuilder) = 0;
            virtual std::string buildMessage(builder::MessageBuilderInput* input) = 0;
    };
};

#endif