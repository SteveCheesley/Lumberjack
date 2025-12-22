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

#include <iostream> // TEMP

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
            std::make_unique<lumberjack::format::builder::DateMessageAppender>(logMessageFormat)) 
    {
        std::cout << "..:: SC-DEBUG :: Begin initialisation (2param)..." << std::endl;
        std::unique_ptr<lumberjack::format::builder::TimeMessageAppender> timeAppender = 
        std::make_unique<lumberjack::format::builder::TimeMessageAppender>(logMessageFormat);

        std::unique_ptr<lumberjack::format::builder::SourceMessageAppender> sourceAppender = 
        std::make_unique<lumberjack::format::builder::SourceMessageAppender>(logMessageFormat);

        std::unique_ptr<lumberjack::format::builder::LogLevelMessageAppender> logLevelAppender = 
        std::make_unique<lumberjack::format::builder::LogLevelMessageAppender>(logMessageFormat);

        sourceAppender->setNext(logLevelAppender.get());
        timeAppender->setNext(sourceAppender.get());
        messageBuilder.get()->setNext(timeAppender.get());
        std::cout << "..:: SC-DEBUG :: End initialisation (2param)" << std::endl;
    }

    DefaultLogFormatter::DefaultLogFormatter(
        LogMessageFormat logMessageFormat, 
        ITimeProvider* timeProvider,
        std::unique_ptr<lumberjack::format::builder::IMessageBuilder> messageBuilder)
        : logMessageFormat(logMessageFormat), timeProvider(timeProvider), messageBuilder(std::move(messageBuilder))
    {
        std::cout << "..:: SC-DEBUG :: Begin initialisation (3param)..." << std::endl;
        std::cout << "..:: SC-DEBUG :: End initialisation (3param)" << std::endl;
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