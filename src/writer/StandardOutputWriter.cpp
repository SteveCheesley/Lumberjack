#include <iostream>
#include "lumberjack/writer/StandardOutputWriter.h"

namespace lumberjack::writer
{
    void StandardOutputWriter::writeToLog(const std::string& entry) 
    {
        printf(entry.data(), 0);
    }
}