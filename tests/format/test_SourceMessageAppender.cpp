#include <gtest/gtest.h>
#include "lumberjack/format/SourceMessageAppender.h"

#include <iostream>
#include <vector>

class Frank
{
  public:
    Frank();
    bool isFrankHome();
};

struct Bob 
{
  int age;
  std::string name;
};

struct Fred
{
  bool isHe;
  int houseNumber;
  std::string streetName;
};

std::string sampleFreeFunction(std::string input)
{
    std::string output = "Hello " + input;
    return output;
}

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

TEST(SourceMessageAppenderTest, FreeFunctionSuccess) {
  lumberjack::format::LogMessageFormat logMessageFormat(
    false,
    false,
    true // <- Let's engage the source printout
  );

  lumberjack::format::SourceMessageAppender subject(
    typeid(sampleFreeFunction), 
    logMessageFormat
    );

  std::string result = subject.buildMessage();

  EXPECT_EQ(result, "sampleFreeFunction ");
}

TEST(SourceMessageAppenderTest, ClassRawOutput) {
  std::cout << "std::string=" << typeid(std::string).name() << std::endl;
  std::cout << "std::vector<int>=" << typeid(std::vector<int>).name() << std::endl;
  std::cout << "SourceMessageAppender=" << typeid(lumberjack::format::SourceMessageAppender).name() << std::endl;
  std::cout << "IMessageBuilder=" << typeid(lumberjack::format::IMessageBuilder).name() << std::endl;
  std::cout << "LogMessageFormat=" << typeid(lumberjack::format::LogMessageFormat).name() << std::endl;
  std::cout << "Bob=" << typeid(Bob).name() << std::endl;
  std::cout << "Fred=" << typeid(Fred).name() << std::endl;
  std::cout << "Frank=" << typeid(Frank).name() << std::endl;
  
}
