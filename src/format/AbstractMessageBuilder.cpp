#include "lumberjack/format/AbstractMessageBuilder.h"

namespace lumberjack::format
{
    IMessageBuilder *AbstractMessageBuilder::setNext(IMessageBuilder *messageBuilder)
    {
        this->nextHandler = messageBuilder;
        return messageBuilder;
    }

    std::string AbstractMessageBuilder::buildMessage(builder::MessageBuilderInput *input)
    {
        std::string message = "";

        if (this->nextHandler)
        {
            message = this->nextHandler->buildMessage(input);
        }

        if (this->canAddToMessage())
        {
            message = message + this->doMessageBuild(input);
        }

        return message;
    }
}