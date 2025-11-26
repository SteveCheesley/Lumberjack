#include <gtest/gtest.h>
#include "lumberjack/format/SourceMessageAppender.h"

TEST(SourceMessageAppenderTest, BasicSuccess) {
  lumberjack::format::LogMessageFormat logMessageFormat(
    false,
    false,
    true // <- Let's engage the source printout
  );

  lumberjack::format::SourceMessageAppender subject(
    typeid(lumberjack::format::AbstractMessageBuilder), 
    logMessageFormat
    );

  std::string result = subject.buildMessage();

  EXPECT_EQ(result, "AbstractMessageBuilder ");
}