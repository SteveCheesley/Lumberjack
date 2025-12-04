#include <string>
#include <gtest/gtest.h>
#include "lumberjack/format/builder/DateMessageAppender.h"
#include "lumberjack/LogLevel.h"
#include "../../time/MockTimeProvider.h"

class DateMessageAppenderTest : public testing::Test
{
    protected:
        lumberjack::time::MockTimeProvider* mockTimeProvider;
        lumberjack::format::builder::DateMessageAppender *subject;
        lumberjack::format::builder::MessageBuilderInput *sampleInput;

        void SetUp() override
        {
            auto fixedTime = std::chrono::system_clock::from_time_t(1759737600);
            mockTimeProvider = new lumberjack::time::MockTimeProvider(fixedTime);
            sampleInput = new lumberjack::format::builder::MessageBuilderInput(
                typeid(DateMessageAppenderTest),
            lumberjack::LogLevel::INFO);
        }
};

TEST_F(DateMessageAppenderTest, testBasicSuccess)
{
    lumberjack::format::LogMessageFormat logMessageFormat(
        true,
        false,
        false,
        false);

    subject = new lumberjack::format::builder::DateMessageAppender(logMessageFormat, mockTimeProvider);

    std::string result = subject->buildMessage(sampleInput);

    EXPECT_EQ(result, "2025-10-06 ");
}