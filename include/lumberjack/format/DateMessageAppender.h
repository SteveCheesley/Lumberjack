#ifndef DATEMESSAGEAPPENDER_H
#define DATEMESSAGEAPPENDER_H

#include "lumberjack/format/AbstractMessageBuilder.h"
#include "lumberjack/format/LogMessageFormat.h"
#include "lumberjack/time/ITimeProvider.h"

namespace lumberjack::format
{
    class DateMessageAppender : public AbstractMessageBuilder
    {
        private:
            lumberjack::time::ITimeProvider* timeProvider;
            const LogMessageFormat &logMessageFormat;
        protected:
            bool canAddToMessage() override final;
            std::string doMessageBuild() override final;
        public:
            DateMessageAppender() = delete;
            DateMessageAppender(const LogMessageFormat& logMessageFormat);
            DateMessageAppender(
                const LogMessageFormat& logMessageFormat, 
                lumberjack::time::ITimeProvider* timeProvider);
    };
}

#endif