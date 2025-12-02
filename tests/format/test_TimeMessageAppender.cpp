#include <gtest/gtest.h>
#include "lumberjack/format/TimeMessageAppender.h"
#include "../time/MockTimeProvider.h"

class TimeMessageAppenderTest : public testing::Test
{
    protected:
        lumberjack::time::MockTimeProvider *mockTimeProvider;
        lumberjack::format::TimeMessageAppender *subject;
        lumberjack::format::builder::MessageBuilderInput *sampleInput;

        void SetUp() override
        {
            auto fixedTime = std::chrono::system_clock::from_time_t(1762980773);
            mockTimeProvider = new lumberjack::time::MockTimeProvider(fixedTime);
            sampleInput = new lumberjack::format::builder::MessageBuilderInput(typeid(TimeMessageAppenderTest));
        }
};

TEST_F(TimeMessageAppenderTest, testBasicSuccess)
{
    lumberjack::format::LogMessageFormat logMessageFormat(
        false,
        true,
        false);        
    
    subject = new lumberjack::format::TimeMessageAppender(logMessageFormat, mockTimeProvider);

    std::string result = subject->buildMessage(sampleInput);

    EXPECT_EQ(result, "20:52:53 ");
}

TEST_F(TimeMessageAppenderTest, expectEmptyOutputFromFormat)
{
    lumberjack::format::LogMessageFormat logMessageFormat(
        false,
        false,
        false);        
    
    subject = new lumberjack::format::TimeMessageAppender(logMessageFormat, mockTimeProvider);

    lumberjack::format::builder::MessageBuilderInput input(typeid(TimeMessageAppenderTest));

    std::string result = subject->buildMessage(sampleInput);

    EXPECT_EQ(result, "");
}