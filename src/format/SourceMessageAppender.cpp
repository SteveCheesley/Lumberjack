#include "lumberjack/format/SourceMessageAppender.h"
#include <cxxabi.h>
#include <iostream>
#include <cctype>

namespace lumberjack::format
{
    SourceMessageAppender::SourceMessageAppender(const lumberjack::format::LogMessageFormat &inputLogMessageFormat)
        : AbstractMessageBuilder(),
          logMessageFormat(inputLogMessageFormat)
    {
    }

    bool SourceMessageAppender::canAddToMessage()
    {
        return this->logMessageFormat.isSourcePrinted();
    }

    std::string SourceMessageAppender::doMessageBuild(builder::MessageBuilderInput* input)
    {
        std::type_index inputSource = input->logMessageSource;
        const char *sourceName = inputSource.name();
        std::string sourceNameString(sourceName);

        // Is the input a Class?
        if (std::string(sourceName).at(0) == 'N') 
        {
            std::string demangledString = demangleTypeIndex(sourceName);
            std::string className = getClassNameFromDemangledString(demangledString);

            return className + " ";
        }

        // Is the input a local Class or Struct?
        if (std::isdigit(std::string(sourceName).at(0))) {
            std::string demangledString = demangleTypeIndex(sourceName);

            return demangledString + " ";
        }

        return sourceNameString + " ";
    }

    std::string SourceMessageAppender::demangleTypeIndex(const char *sourceName) 
    {
        int demanglingStatus;
        char *demangled = abi::__cxa_demangle(sourceName, 0, 0, &demanglingStatus);
        
        std::string result = std::string(demangled);
        
        std::free(demangled);
        demangled = nullptr;

        return result;
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