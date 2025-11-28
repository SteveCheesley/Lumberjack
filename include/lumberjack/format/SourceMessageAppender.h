#ifndef SOURCEMESSAGEAPPENDER_H
#define SOURCEMESSAGEAPPENDER_H

#include "lumberjack/format/AbstractMessageBuilder.h"
#include "lumberjack/format/LogMessageFormat.h"
#include <typeindex>

namespace lumberjack::format
{
    class SourceMessageAppender : public AbstractMessageBuilder
    {
        private:
            const std::type_index &logMessageSource;
            const lumberjack::format::LogMessageFormat &logMessageFormat;
            std::string demangleTypeIndex(const char *sourceName);
            std::string getClassNameFromDemangledString(std::string demangledString);
            int countCurlyBraces(std::string demangledString);
        protected:
            bool canAddToMessage() override final;
            std::string doMessageBuild() override final;
        public:
            SourceMessageAppender() = delete;
            SourceMessageAppender(const std::type_index &inputLogMessageSource,
                const lumberjack::format::LogMessageFormat &inputLogMessageFormat);
    };
}

#endif