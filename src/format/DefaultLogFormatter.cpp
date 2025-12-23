#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "lumberjack/format/DefaultLogFormatter.h"
#include "lumberjack/time/SystemTimeProvider.h"

#include "lumberjack/format/builder/DateMessageAppender.h"
#include "lumberjack/format/builder/TimeMessageAppender.h"
#include "lumberjack/format/builder/SourceMessageAppender.h"
#include "lumberjack/format/builder/LogLevelMessageAppender.h"

using lumberjack::time::SystemTimeProvider;

namespace lumberjack::format
{
    DefaultLogFormatter::DefaultLogFormatter() 
        : DefaultLogFormatter(LogMessageFormat(true, true, true, true))
    {
    }

    DefaultLogFormatter::DefaultLogFormatter(LogMessageFormat logMessageFormat) 
        : DefaultLogFormatter(logMessageFormat, 
            new SystemTimeProvider())
    {
    }

    DefaultLogFormatter::DefaultLogFormatter(LogMessageFormat logMessageFormat, ITimeProvider* timeProvider) 
    : DefaultLogFormatter(
            logMessageFormat, 
            timeProvider, 
            std::make_unique<lumberjack::format::builder::DateMessageAppender>(logMessageFormat, timeProvider)) 
    {
        std::unique_ptr<lumberjack::format::builder::IMessageBuilder> timeAppender = 
        std::make_unique<lumberjack::format::builder::TimeMessageAppender>(logMessageFormat, timeProvider);

        std::unique_ptr<lumberjack::format::builder::IMessageBuilder> sourceAppender = 
        std::make_unique<lumberjack::format::builder::SourceMessageAppender>(logMessageFormat);

        std::unique_ptr<lumberjack::format::builder::IMessageBuilder> logLevelAppender = 
        std::make_unique<lumberjack::format::builder::LogLevelMessageAppender>(logMessageFormat);

        sourceAppender->setNext(logLevelAppender);
        timeAppender->setNext(sourceAppender);
        messageBuilder->setNext(timeAppender);
    }

    DefaultLogFormatter::DefaultLogFormatter(
        LogMessageFormat logMessageFormat, 
        ITimeProvider* timeProvider,
        std::unique_ptr<lumberjack::format::builder::IMessageBuilder> messageBuilder)
        : logMessageFormat(logMessageFormat), timeProvider(timeProvider), messageBuilder(std::move(messageBuilder))
    {
    }

    /*
     * TODO - Need a proper destructor
     */
    std::string DefaultLogFormatter::formatMessage(std::type_index source, LogLevel logLevel, std::string message)
    {
        lumberjack::format::builder::MessageBuilderInput input(
            source,
            logLevel
        );
        
        std::string output = messageBuilder->buildMessage(&input);

        output = output + message;

        return output;
    }
};