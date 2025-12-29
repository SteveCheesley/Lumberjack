#include <gtest/gtest.h>
#include <string>
#include <tuple>
#include "lumberjack/format/DefaultLogFormatter.h"
#include "../time/MockTimeProvider.h"

#include <iostream>

using lumberjack::format::DefaultLogFormatter;
using lumberjack::format::ILogFormatter;
using lumberjack::time::ITimeProvider;
using lumberjack::time::MockTimeProvider;
using lumberjack::format::LogMessageFormat;
using lumberjack::LogLevel;

struct TestParameters {
    LogMessageFormat logFormat;
    std::string expectedOutput;
};

class DefaultLogFormatterTest : public ::testing::TestWithParam<TestParameters> {
    protected:
        ITimeProvider* mockTimeProvider;

        // Called before *each* test
        void SetUp() override {
            auto fixedTime = std::chrono::system_clock::from_time_t(1704564384);
            mockTimeProvider = new MockTimeProvider(fixedTime);
        }

        // Called after *each* test
        void TearDown() override {
        }
};

TEST_P(DefaultLogFormatterTest, FormatsOutputBasedOnConfiguration) {
    TestParameters testParameters = GetParam();
    ILogFormatter* subject = new DefaultLogFormatter(
        testParameters.logFormat, 
        mockTimeProvider);
    
    std::string result = subject->formatMessage(
        typeid(DefaultLogFormatterTest), 
        LogLevel::INFO, 
        "Hello World!");

    EXPECT_EQ(result, testParameters.expectedOutput);
}

INSTANTIATE_TEST_SUITE_P(
    MessageFormatCases,
    DefaultLogFormatterTest,
    ::testing::Values(
        TestParameters{
            LogMessageFormat(true, true, true, true), 
            "2024-01-06 18:06:24 DefaultLogFormatterTest [INFO] Hello World!"
        },
        TestParameters{
            LogMessageFormat(true, true, true, false), 
            "2024-01-06 18:06:24 [INFO] Hello World!"
        },
        TestParameters{
            LogMessageFormat(true, true, false, false), 
            "2024-01-06 18:06:24 Hello World!"
        },
        TestParameters{
            LogMessageFormat(true, false, false, false), 
            "2024-01-06 Hello World!"
        }
    )
);