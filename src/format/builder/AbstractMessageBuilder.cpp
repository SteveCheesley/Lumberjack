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

        if (this->nextHandler)
        {
            // TODO - This is where the segmentation faul happens - Need to debug and find out why!
            /* Hypothesis - nextHandler is a raw pointer, and it isn't cleared after the last set
             * If a smart pointer was used to load the next value but it was subsequently cleared
             * That might explain a segmentation fault - think - what happens on the last link?
             */
            message = this->nextHandler->buildMessage(input);
        }

        if (this->canAddToMessage())
        {
            message = message + this->doMessageBuild(input);
        }

        return message;
    }
}