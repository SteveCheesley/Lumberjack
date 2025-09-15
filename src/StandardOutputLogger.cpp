#include <iostream>
#include "../include/StandardOutputLogger.h"

using std::cout;
using std::endl;

namespace logger
{
    StandardOutputLogger::StandardOutputLogger() 
    : loggerConfiguration(new LoggerConfiguration()) {};

    StandardOutputLogger::StandardOutputLogger(const LoggerConfiguration& inputLoggerConfiguration) 
        : loggerConfiguration(inputLoggerConfiguration) {};

    void StandardOutputLogger::log(LogLevel level, std::string message)
    {
        // TODO - Process and format message
        cout << "something-to-test" << endl;
    };
}