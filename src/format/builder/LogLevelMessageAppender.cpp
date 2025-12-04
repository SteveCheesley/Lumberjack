#include "lumberjack/format/builder/LogLevelMessageAppender.h"

namespace lumberjack::format::builder
{
    LogLevelMessageAppender::LogLevelMessageAppender(const lumberjack::format::LogMessageFormat &logMessageFormat) 
        : AbstractMessageBuilder(),
        logMessageFormat(logMessageFormat){}

    bool LogLevelMessageAppender::canAddToMessage() 
    {
        return this->logMessageFormat.isLevelPrinted();
    }

    std::string LogLevelMessageAppender::doMessageBuild(MessageBuilderInput *input)
    {
        std::string logLevelString = "default";

        switch (input->logLevel) {
            case ERROR:   logLevelString = "ERROR";
            case WARNING: logLevelString = "WARNING";
            case INFO:    logLevelString = "INFO";
            case DEBUG:   logLevelString = "DEBUG";
            case TRACE:   logLevelString = "TRACE";
        }

        return "[" + logLevelString + "] ";
    }
}