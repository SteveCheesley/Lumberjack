#ifndef MOCKLOGFORMATTER_H
#define MOCKLOGFORMATTER_H

#include <utility>

#include "lumberjack/format/ILogFormatter.h"

namespace lumberjack::format
{
    class MockLogFormatter : public ILogFormatter 
    {
        private:
            std::string expectedOutput_;
            int invocationCount_ = 0;
        public:
            MockLogFormatter(std::string expectedOutput) : expectedOutput_(std::move(expectedOutput)) {}
            virtual ~MockLogFormatter() = default;

            std::string formatMessage(std::type_index source, lumberjack::LogLevel level, std::string message)
            {
                this->invocationCount_++;
                return this->expectedOutput_;
            }

            [[nodiscard]] auto* getInvocationCount() const
            {
                return &this->invocationCount_;
            }
    };
}

#endif