#include <gtest/gtest.h>
#include "lumberjack/format/DateMessageAppender.h"
#include "lumberjack/LogLevel.h"

class DateMessageAppenderTest : public testing::Test {
    protected:
        lumberjack::format::DateMessageAppender* subject;
};

TEST_F(DateMessageAppenderTest, testBasicSuccess) {
    lumberjack::format::LogMessageFormat logMessageFormat(
        true, 
        false,
        false);

    subject = new lumberjack::format::DateMessageAppender(logMessageFormat);
}