#ifndef SOURCEMESSAGEAPPENDER_H
#define SOURCEMESSAGEAPPENDER_H

#include "lumberjack/format/AbstractMessageBuilder.h"
#include "lumberjack/format/LogMessageFormat.h"

namespace lumberjack::format
{
    class SourceMessageAppender : public AbstractMessageBuilder
    {
        private:
            const lumberjack::format::LogMessageFormat &logMessageFormat;
        protected:
            bool canAddToMessage() override final;
            std::string doMessageBuild() override final;
        public:
            SourceMessageAppender() = delete;
            SourceMessageAppender(const lumberjack::format::LogMessageFormat &inputLogMessageFormat);
    };
}

#endif