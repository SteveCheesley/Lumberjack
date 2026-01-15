#ifndef STANDARDOUTPUTWRITER_H
#define STANDARDOUTPUTWRITER_H

#include "lumberjack/writer/ILogWriter.h"

namespace lumberjack::writer
{
    class StandardOutputWriter : public ILogWriter
    {
        public:
            void writeToLog(std::string entry) override;
    };
}

#endif