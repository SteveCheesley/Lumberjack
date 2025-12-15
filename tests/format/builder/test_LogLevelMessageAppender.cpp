#include <gtest/gtest.h>
#include "lumberjack/format/builder/LogLevelMessageAppender.h"

class LogLevelMessageAppenderTest : public testing::Test
{
    protected:
        std::unique_ptr<lumberjack::format::LogMessageFormat> testFormatSpecification;
        std::unique_ptr<lumberjack::format::builder::MessageBuilderInput> testBuildMessageInput;
        lumberjack::LogLevel defaultInputLogLevel = lumberjack::LogLevel::INFO;

        void SetUp() override
        {
            testFormatSpecification = std::make_unique<lumberjack::format::LogMessageFormat>(
                true,
                true,
                true,
                true
            );

            testBuildMessageInput = std::make_unique<lumberjack::format::builder::MessageBuilderInput>(
                typeid(LogLevelMessageAppenderTest),
                defaultInputLogLevel
            );
        }
};

TEST_F(LogLevelMessageAppenderTest, basicSuccessTest)
{
    lumberjack::format::builder::LogLevelMessageAppender subject(*testFormatSpecification);

    std::string result = subject.buildMessage(testBuildMessageInput.get());

    EXPECT_EQ(result, "[INFO] ");
}

TEST_F(LogLevelMessageAppenderTest, isOutputEmptyIfInactive)
{
    lumberjack::format::LogMessageFormat deactivatedFormat(false, false, false, false);
    lumberjack::format::builder::LogLevelMessageAppender subject(deactivatedFormat);

    std::string result = subject.buildMessage(testBuildMessageInput.get());

    EXPECT_EQ(result, "");
}