#include "lumberjack/format/AbstractMessageBuilder.h"

namespace lumberjack::format
{
    IMessageBuilder *AbstractMessageBuilder::setNext(IMessageBuilder *messageBuilder)
    {
        this->nextHandler = messageBuilder;
        return messageBuilder;
    }

    std::string AbstractMessageBuilder::buildMessage()
    {
        std::string message = "";

        if (this->nextHandler)
        {
            message = this->nextHandler->buildMessage();
        }

        if (this->canAddToMessage())
        {
            message = message + this->doMessageBuild();
        }

        return message;
    }
}