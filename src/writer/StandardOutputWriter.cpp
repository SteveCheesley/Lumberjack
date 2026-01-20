#include <iostream>
#include "lumberjack/writer/StandardOutputWriter.h"

namespace lumberjack::writer
{    
    StandardOutputWriter::StandardOutputWriter(bool printsLineBreak) : prints_line_break(printsLineBreak)
    {
    }

    void StandardOutputWriter::writeToLog(const std::string& entry) 
    {
        std::string output = entry;
        if (this->prints_line_break) {
            output += "\n";
        }

        /* === Use of printf
         * I've opted to use printf over cout to try to optimise performance 
         * and reduce both memory and execution overheads. */
        printf(output.data(), 0);
    }
}