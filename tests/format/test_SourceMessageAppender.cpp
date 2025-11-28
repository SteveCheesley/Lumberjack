#include <gtest/gtest.h>
#include "lumberjack/format/SourceMessageAppender.h"

#include <iostream>
#include <vector>

class Person
{
  public:
    Person(std::string name, int age);
    std::string getName();
    int getAge();
};

struct Address
{
  int doorNumber;
  std::string firstLine;
  std::string secondLine;
  std::string town;
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
    true
  ); // TODO - DRY

  lumberjack::format::SourceMessageAppender subject(
    typeid(sampleFreeFunction), 
    logMessageFormat
    );

  std::string result = subject.buildMessage();

  EXPECT_EQ(result, "FNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES4_E ");
}

TEST(SourceMessageAppenderTest, LocalClassSuccess) {
  lumberjack::format::LogMessageFormat logMessageFormat(
    false,
    false,
    true
  ); // TODO - DRY

  lumberjack::format::SourceMessageAppender subject(
    typeid(Person), 
    logMessageFormat
    );

  std::string result = subject.buildMessage();

  EXPECT_EQ(result, "Person ");
}

TEST(SourceMessageAppenderTest, LocalStructSuccess) {
  lumberjack::format::LogMessageFormat logMessageFormat(
    false,
    false,
    true
  ); // TODO - DRY

  lumberjack::format::SourceMessageAppender subject(
    typeid(Address), 
    logMessageFormat
    );

  std::string result = subject.buildMessage();

  EXPECT_EQ(result, "Address ");
}