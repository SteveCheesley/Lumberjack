#include "lumberjack/format/SourceMessageAppender.h"

namespace lumberjack::format
{
    SourceMessageAppender::SourceMessageAppender(const lumberjack::format::LogMessageFormat &inputLogMessageFormat) 
        : AbstractMessageBuilder(),
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