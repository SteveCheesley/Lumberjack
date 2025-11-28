#ifndef ABSTRACTMESSAGEBUILDER_H
#define ABSTRACTMESSAGEBUILDER_H

#include "IMessageBuilder.h"

namespace lumberjack::format
{
    class AbstractMessageBuilder : public IMessageBuilder {
        private:
            IMessageBuilder *nextHandler;
        protected:
            virtual bool canAddToMessage() = 0;
            virtual std::string doMessageBuild(builder::MessageBuilderInput *input) = 0;
        public:
            AbstractMessageBuilder() : nextHandler(nullptr) {
            }
            IMessageBuilder *setNext(IMessageBuilder *messageBuilder) override;
            std::string buildMessage(builder::MessageBuilderInput *input) override final;
    };
}

#endif