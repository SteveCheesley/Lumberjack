#ifndef DATEMESSAGEAPPENDER_H
#define DATEMESSAGEAPPENDER_H

#include "AbstractMessageBuilder.h"
#include "LogMessageFormat.h"

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