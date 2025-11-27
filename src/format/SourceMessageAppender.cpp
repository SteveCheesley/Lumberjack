#include "lumberjack/format/SourceMessageAppender.h"
#include <cxxabi.h>
#include <iostream>

namespace lumberjack::format
{
    SourceMessageAppender::SourceMessageAppender(const std::type_index &inputLogMessageSource,
                                                 const lumberjack::format::LogMessageFormat &inputLogMessageFormat)
        : AbstractMessageBuilder(),
          logMessageSource(inputLogMessageSource),
          logMessageFormat(inputLogMessageFormat)
    {
    }

    bool SourceMessageAppender::canAddToMessage()
    {
        return this->logMessageFormat.isSourcePrinted();
    }

    std::string SourceMessageAppender::doMessageBuild()
    {
        const char *sourceName = logMessageSource.name();
        std::string sourceNameString(sourceName);
        // Is the input a Class?
        if (std::string(sourceName).at(0) == 'N') 
        {
            // Demangle the source name
            int demanglingStatus;
            char *demangled = abi::__cxa_demangle(sourceName, 0, 0, &demanglingStatus);
            std::string demangledString = std::string(demangled);
        
            // Extract the class name where a namespace exists
            std::string className = getClassNameFromDemangledString(demangledString);
            
            // Clear allocation after use
            std::free(demangled);
            demangled = nullptr;

            return className + " ";
        }

        // TODO - Add in a condition that handles local class and struct definitions (i.e. 0-9 prefix)

        return sourceNameString + " ";
    }

    int SourceMessageAppender::countCurlyBraces(std::string demangledString)
    {
        int openBraceCount = 0;
        int closeBraceCount = 0;
        for (std::string::iterator it = demangledString.begin(); it != demangledString.end(); ++it)
        {
            if (*it == '(') openBraceCount++;
            if (*it == ')') closeBraceCount++;
        }

        std::cout << "...::: openBraceCount=" << openBraceCount << " :::..." << std::endl;
        std::cout << "...::: closeBraceCount=" << closeBraceCount << " :::..." << std::endl;

        return -1;
    }

    std::string SourceMessageAppender::getClassNameFromDemangledString(std::string demangledString)
    {
        std::size_t lastSeparatorPosition = demangledString.find_last_of("::");
        std::string className = demangledString.substr(lastSeparatorPosition + 1);
        return className;
    }
}