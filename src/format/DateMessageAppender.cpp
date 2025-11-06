#include "lumberjack/format/DateMessageAppender.h"

#include "lumberjack/format/LogMessageFormat.h"

namespace lumberjack::format
{
    DateMessageAppender::DateMessageAppender(const LogMessageFormat &inputLogMessageFormat) : AbstractMessageBuilder(), logMessageFormat(inputLogMessageFormat)
    {
    }

    bool DateMessageAppender::canAddToMessage()
    {
        // TODO build automated testing for this before adding functionality
        return true;
    }

    std::string DateMessageAppender::doMessageBuild()
    {
        // TODO build automated testing for this before adding functionality
        return "";
    }
}