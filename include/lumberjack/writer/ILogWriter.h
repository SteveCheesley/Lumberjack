#ifndef ILOGWRITER_H
#define ILOGWRITER_H

#include <string>

namespace lumberjack::writer
{
    class ILogWriter
    {
        public:
            virtual void writeToLog(const std::string& entry) = 0;
            virtual ~ILogWriter() = default;

            ILogWriter(const ILogWriter&) = delete;
            auto operator=(const ILogWriter&) -> ILogWriter& = delete;
            ILogWriter(ILogWriter&&) = delete;
            auto operator=(ILogWriter&&) -> ILogWriter& = delete;
    };
}

#endif