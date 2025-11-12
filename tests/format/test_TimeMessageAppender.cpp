#include <gtest/gtest.h>
#include "lumberjack/format/TimeMessageAppender.h"
#include "../time/MockTimeProvider.h"

class TimeMessageAppenderTest : public testing::Test
{
    protected:
        lumberjack::time::MockTimeProvider *mockTimeProvider;
        lumberjack::format::TimeMessageAppender *subject;

        void SetUp() override
        {
            auto fixedTime = std::chrono::system_clock::from_time_t(1762980773);
            mockTimeProvider = new lumberjack::time::MockTimeProvider(fixedTime);
        }
};

TEST_F(TimeMessageAppenderTest, testBasicSuccess)
{
    lumberjack::format::LogMessageFormat logMessageFormat(
        false,
        true,
        false);        
    
        subject = new lumberjack::format::TimeMessageAppender(logMessageFormat, mockTimeProvider);

        std::string result = subject->buildMessage();

        EXPECT_EQ(result, "20:52:53 ");
}