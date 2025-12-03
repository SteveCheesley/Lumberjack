#ifndef DATEMESSAGEAPPENDER_H
#define DATEMESSAGEAPPENDER_H

#include "lumberjack/format/builder/AbstractMessageBuilder.h"
#include "lumberjack/format/LogMessageFormat.h"
#include "lumberjack/time/ITimeProvider.h"

namespace lumberjack::format::builder
{
    class DateMessageAppender : public AbstractMessageBuilder
    {
        private:
            lumberjack::time::ITimeProvider* timeProvider;
            const LogMessageFormat &logMessageFormat;
        protected:
            bool canAddToMessage() override final;
            std::string doMessageBuild(MessageBuilderInput* input) override final;
        public:
            DateMessageAppender() = delete;
            DateMessageAppender(const LogMessageFormat& logMessageFormat);
            DateMessageAppender(
                const LogMessageFormat& logMessageFormat, 
                lumberjack::time::ITimeProvider* timeProvider);
    };
}

#endif