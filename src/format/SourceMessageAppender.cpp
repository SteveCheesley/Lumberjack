#include "lumberjack/format/SourceMessageAppender.h"

namespace lumberjack::format
{
    SourceMessageAppender::SourceMessageAppender(const std::type_index &inputLogMessageSource,
        const lumberjack::format::LogMessageFormat &inputLogMessageFormat) 
        : AbstractMessageBuilder(),
        logMessageSource(inputLogMessageSource),
        logMessageFormat(inputLogMessageFormat)
    {
    }

    bool SourceMessageAppender::canAddToMessage()
    {
        return this->logMessageFormat.isSourcePrinted();
    }

    std::string SourceMessageAppender::doMessageBuild()
    {
        // Add implementation to this function
        return "dateString";
    }
}