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
        std::string logLevelString = "";
        
        switch (input->logLevel) {
            case ERROR:
                logLevelString = "ERROR";
                break;
            case WARNING: 
                logLevelString = "WARNING";
                break;
            case INFO:    
                logLevelString = "INFO";
                break;
            case DEBUG:   
                logLevelString = "DEBUG";
                break;
            case TRACE:   
                logLevelString = "TRACE";
                break;
        }

        return "[" + logLevelString + "] ";
    }
}