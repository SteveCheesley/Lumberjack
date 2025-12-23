#ifndef IMESSAGEBUILDER_H
#define IMESSAGEBUILDER_H

#include "lumberjack/format/builder/MessageBuilderInput.h"
#include <string>
#include <memory>

namespace lumberjack::format::builder
{
    class IMessageBuilder
    {
        public:
            virtual std::unique_ptr<IMessageBuilder>& setNext(std::unique_ptr<IMessageBuilder> &messageBuilder) = 0;
            virtual std::string buildMessage(MessageBuilderInput* input) = 0;
    };
};

#endif