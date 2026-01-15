#include <iostream>
#include "lumberjack/writer/StandardOutputWriter.h"

namespace lumberjack::writer
{
    void StandardOutputWriter::writeToLog(const std::string& entry) 
    {
        /* === Use of printf
         * I've opted to use printf over cout to try to optimise performance 
         * and reduce both memory and execution overheads. */
        printf(entry.data(), 0);
    }
}