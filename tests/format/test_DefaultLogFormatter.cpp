#include <gtest/gtest.h>
#include <string>
#include "lumberjack/format/DefaultLogFormatter.h"
#include "../time/MockTimeProvider.h"

using lumberjack::format::DefaultLogFormatter;
using lumberjack::format::ILogFormatter;
using lumberjack::time::ITimeProvider;
using lumberjack::time::MockTimeProvider;
using lumberjack::format::LogMessageFormat;
using lumberjack::LogLevel;

TEST(DefaultLogFormatterTest, HandlesStandardInput) {
    auto fixedTime = std::chrono::system_clock::from_time_t(1609459200);
    ITimeProvider* mockTimeProvider = new MockTimeProvider(fixedTime);

    ILogFormatter* subject = new DefaultLogFormatter(LogMessageFormat(true, true, true), mockTimeProvider);
    
    std::string result = subject->formatMessage(LogLevel::INFO, "Hello World!");

    EXPECT_EQ(result, "2025-10-04 20:39.921 [INFO] Hello, World!");
}