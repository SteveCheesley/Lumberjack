#include <gtest/gtest.h>
#include <string>
#include "lumberjack/format/DefaultLogFormatter.h"

using lumberjack::format::DefaultLogFormatter;
using lumberjack::format::ILogFormatter;
using lumberjack::LogLevel;

TEST(DefaultLogFormatterTest, HandlesStandardInput) {
    ILogFormatter* subject = new DefaultLogFormatter();
    
    std::string result = subject->formatMessage(LogLevel::INFO, "Hello World!");

    EXPECT_EQ(result, "2025-10-04 20:39.921 [INFO] Hello, World!");
}