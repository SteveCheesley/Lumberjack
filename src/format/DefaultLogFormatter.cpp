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
            new SystemTimeProvider(), 
            std::make_unique<lumberjack::format::builder::DateMessageAppender>(logMessageFormat))
    {
        std::unique_ptr<lumberjack::format::builder::TimeMessageAppender> timeAppender = 
        std::make_unique<lumberjack::format::builder::TimeMessageAppender>(logMessageFormat);

        std::unique_ptr<lumberjack::format::builder::SourceMessageAppender> sourceAppender = 
        std::make_unique<lumberjack::format::builder::SourceMessageAppender>(logMessageFormat);

        std::unique_ptr<lumberjack::format::builder::LogLevelMessageAppender> logLevelAppender = 
        std::make_unique<lumberjack::format::builder::LogLevelMessageAppender>(logMessageFormat);

        sourceAppender->setNext(logLevelAppender.get());
        timeAppender->setNext(sourceAppender.get());
        messageBuilder.get()->setNext(timeAppender.get());
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