#ifndef DATEMESSAGEAPPENDER_H
#define DATEMESSAGEAPPENDER_H

#include "AbstractMessageBuilder.h"
#include "LogMessageFormat.h"

namespace lumberjack::format
{
    class DateMessageAppender : public AbstractMessageBuilder
    {
        private:
            const LogMessageFormat &logMessageFormat;
        public:
            DateMessageAppender() = delete;
            DateMessageAppender(const LogMessageFormat& logMessageFormat);
            bool canAddToMessage() override final;
            std::string doMessageBuild() override final;
    };
}

#endif