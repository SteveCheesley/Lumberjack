#ifndef IMESSAGEBUILDER_H
#define IMESSAGEBUILDER_H

#include <string>

namespace lumberjack::format
{
    class IMessageBuilder
    {
        public:
            virtual IMessageBuilder *setNext(IMessageBuilder *messageBuilder) = 0;
            virtual std::string buildMessage() = 0;
    };
}

#endif