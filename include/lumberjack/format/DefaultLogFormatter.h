#ifndef DEFAULTLOGFORMATTER_H
#define DEFAULTLOGFORMATTER_H

#include "lumberjack/format/LogMessageFormat.h"
#include "lumberjack/LogLevel.h"
#include "lumberjack/format/ILogFormatter.h"
#include "lumberjack/time/ITimeProvider.h"
#include "lumberjack/format/builder/IMessageBuilder.h"
#include <string>
#include <memory>

using lumberjack::time::ITimeProvider;

namespace lumberjack::format 
{
    class DefaultLogFormatter : public ILogFormatter
    {
        private:
            LogMessageFormat logMessageFormat;
            ITimeProvider* timeProvider;
            std::unique_ptr<lumberjack::format::builder::IMessageBuilder> messageBuilder;
        public:
            DefaultLogFormatter();
            DefaultLogFormatter(LogMessageFormat LogMessageFormat);
            DefaultLogFormatter(
                LogMessageFormat LogMessageFormat, 
                ITimeProvider* timeProvider
            );
            DefaultLogFormatter(
                LogMessageFormat LogMessageFormat, 
                ITimeProvider* timeProvider, 
                std::unique_ptr<lumberjack::format::builder::IMessageBuilder> messageBuilder
            );
            std::string formatMessage(std::type_index source, LogLevel logLevel, std::string message);
    };
};

#endif