#include "lumberjack/format/builder/LogLevelMessageAppender.h"

namespace lumberjack::format::builder
{
    LogLevelMessageAppender::LogLevelMessageAppender(const lumberjack::format::LogMessageFormat &logMessageFormat) 
        : AbstractMessageBuilder(),
        logMessageFormat(logMessageFormat){}

    bool LogLevelMessageAppender::canAddToMessage() 
    {
        return true;
    }

    std::string LogLevelMessageAppender::doMessageBuild(MessageBuilderInput *input)
    {
        return "sample output";
    }
}