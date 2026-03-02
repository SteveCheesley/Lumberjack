#include <gtest/gtest.h>
#include "lumberjack/writer/StandardOutputWriter.h"

TEST(StandardOutputWriterTest, BasicSuccessTest) {
    std::string test_input = "..:: log output ::..";
    lumberjack::writer::StandardOutputWriter subject;

    testing::internal::CaptureStdout();
    subject.writeToLog(test_input);
    
    std::string output = testing::internal::GetCapturedStdout();
    std::string expectedOutput = test_input + "\n";
    EXPECT_EQ(output, expectedOutput);
}

TEST(StandardOutputWriterTest, NoLineBreakTest) {
    std::string test_input = "..:: log output ::..";
    lumberjack::writer::StandardOutputWriter subject(false);

    testing::internal::CaptureStdout();
    subject.writeToLog(test_input);
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, test_input);
}