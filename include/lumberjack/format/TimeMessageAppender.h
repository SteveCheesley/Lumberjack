#ifndef TIMEMESSAGEAPPENDER_H
#define TIMEMESSAGEAPPENDER_H

#include "lumberjack/format/AbstractMessageBuilder.h"
#include "lumberjack/format/LogMessageFormat.h"
#include "lumberjack/time/ITimeProvider.h"

namespace lumberjack::format
{
    class TimeMessageAppender : public AbstractMessageBuilder
    {
        private:
            lumberjack::time::ITimeProvider* timeProvider;
            const lumberjack::format::LogMessageFormat &logMessageFormat;
        protected:
            bool canAddToMessage() override final;
            std::string doMessageBuild(builder::MessageBuilderInput* input) override final;
        public:
            TimeMessageAppender() = delete;
            TimeMessageAppender(const lumberjack::format::LogMessageFormat& logMessageFormat);
            TimeMessageAppender(
                const lumberjack::format::LogMessageFormat& logMessageFormat, 
                lumberjack::time::ITimeProvider* timeProvider);
    };
}

#endif