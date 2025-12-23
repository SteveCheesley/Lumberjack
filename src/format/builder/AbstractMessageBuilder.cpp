#include "lumberjack/format/builder/AbstractMessageBuilder.h"

namespace lumberjack::format::builder
{
    std::unique_ptr<IMessageBuilder>& AbstractMessageBuilder::setNext(std::unique_ptr<IMessageBuilder> &messageBuilder)
    {
        this->nextHandler = std::move(messageBuilder);
        return messageBuilder;
    }

    std::string AbstractMessageBuilder::buildMessage(MessageBuilderInput *input)
    {
        std::string message = "";

        if (this->canAddToMessage())
        {
            message = this->doMessageBuild(input);
        }

        if (this->nextHandler)
        {
            message = message + this->nextHandler->buildMessage(input);
        }

        return message;
    }
}