#ifndef STANDARDOUTPUTWRITER_H
#define STANDARDOUTPUTWRITER_H

#include "lumberjack/writer/ILogWriter.h"

namespace lumberjack::writer
{
    class StandardOutputWriter : public ILogWriter
    {
        private:
            bool prints_line_break = true;
        public:
            StandardOutputWriter() = default;
            StandardOutputWriter(bool printsLineBreak);
            void writeToLog(const std::string& entry) override;
    };
}

#endif