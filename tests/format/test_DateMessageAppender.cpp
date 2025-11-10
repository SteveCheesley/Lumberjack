#include <string>
#include <gtest/gtest.h>
#include "lumberjack/format/DateMessageAppender.h"
#include "lumberjack/LogLevel.h"
#include "../time/MockTimeProvider.h"

class DateMessageAppenderTest : public testing::Test
{
protected:
    lumberjack::time::MockTimeProvider* mockTimeProvider;
    lumberjack::format::DateMessageAppender *subject;

    void SetUp() override
    {
        auto fixedTime = std::chrono::system_clock::from_time_t(1759737600);
        mockTimeProvider = new lumberjack::time::MockTimeProvider(fixedTime);
    }
};

TEST_F(DateMessageAppenderTest, testBasicSuccess)
{
    lumberjack::format::LogMessageFormat logMessageFormat(
        true,
        false,
        false);

    subject = new lumberjack::format::DateMessageAppender(logMessageFormat, mockTimeProvider);

    std::string result = subject->buildMessage();

    EXPECT_EQ(result, "2025-10-06 ");
}