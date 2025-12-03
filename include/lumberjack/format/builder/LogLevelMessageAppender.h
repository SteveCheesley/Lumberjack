#ifndef LOGLEVELMESSAGEAPPENDER_H
#define LOGLEVELMESSAGEAPPENDER_H

#include "lumberjack/format/builder/AbstractMessageBuilder.h"
#include "lumberjack/format/LogMessageFormat.h"

namespace lumberjack::format::builder
{
    class LogLevelMessageAppender : public AbstractMessageBuilder
    {
        private:
            const lumberjack::format::LogMessageFormat &logMessageFormat;
        protected:
            bool canAddToMessage() override final;
            std::string doMessageBuild(MessageBuilderInput *input) override final;
        public:
            LogLevelMessageAppender() = delete;
            LogLevelMessageAppender(const lumberjack::format::LogMessageFormat &logMessageFormat);
    };
}

#endif