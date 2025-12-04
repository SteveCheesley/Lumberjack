#include <gtest/gtest.h>
#include <string>
#include <tuple>
#include "lumberjack/format/DefaultLogFormatter.h"
#include "../time/MockTimeProvider.h"

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
            auto fixedTime = std::chrono::system_clock::from_time_t(1609459200);
            mockTimeProvider = new MockTimeProvider(fixedTime);
        }

        // Called after *each* test
        void TearDown() override {
        }
};

TEST_F(DefaultLogFormatterTest, BasicSuccessTest) {
    ILogFormatter* subject = new DefaultLogFormatter(
        LogMessageFormat(true, true, true, true), 
        mockTimeProvider);
    
    std::string result = subject->formatMessage(typeid(DefaultLogFormatterTest), LogLevel::INFO, "Hello World!");

    EXPECT_EQ(result, "2025-10-04 20:39.921 [INFO] Hello, World!");
};

TEST_P(DefaultLogFormatterTest, FormatsOutputBasedOnConfiguration) {
    TestParameters testParameters = GetParam();
    ILogFormatter* subject = new DefaultLogFormatter(
        testParameters.logFormat, 
        mockTimeProvider);
    
    std::string result = subject->formatMessage(typeid(DefaultLogFormatterTest), LogLevel::INFO, "Hello World!");

    EXPECT_EQ(result, testParameters.expectedOutput);
}

INSTANTIATE_TEST_SUITE_P(
    MessageFormatCases,
    DefaultLogFormatterTest,
    ::testing::Values(
        TestParameters{
            LogMessageFormat(true, true, false, false), 
            "2025-10-04 20:39.921 Hello, World!"
        },
        TestParameters{
            LogMessageFormat(true, false, false, false), 
            "2025-10-04 Hello, World!"
        }
    )
);