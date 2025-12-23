#ifndef SOURCEMESSAGEAPPENDER_H
#define SOURCEMESSAGEAPPENDER_H

#include "lumberjack/format/builder/AbstractMessageBuilder.h"
#include "lumberjack/format/LogMessageFormat.h"

namespace lumberjack::format::builder
{
    class SourceMessageAppender : public AbstractMessageBuilder
    {
        private:
            const lumberjack::format::LogMessageFormat logMessageFormat;
            std::string demangleTypeIndex(const char *sourceName);
            std::string getClassNameFromDemangledString(std::string demangledString);
            int countCurlyBraces(std::string demangledString);
        protected:
            bool canAddToMessage() override final;
            std::string doMessageBuild(MessageBuilderInput* input) override final;
        public:
            SourceMessageAppender() = delete;
            SourceMessageAppender(const lumberjack::format::LogMessageFormat &inputLogMessageFormat);
    };
}

#endif