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
};

class SourceMessageAppenderTest : public testing::Test
{
    protected:
      std::unique_ptr<lumberjack::format::LogMessageFormat> testFormatSpecification;
    
      void SetUp() override
      {
          testFormatSpecification = std::make_unique<lumberjack::format::LogMessageFormat>(
            false,
            false,
            true
          );
      }
};

TEST_F(SourceMessageAppenderTest, BasicSuccess)
{
  lumberjack::format::SourceMessageAppender subject(
      typeid(lumberjack::format::AbstractMessageBuilder),
      *testFormatSpecification);

  lumberjack::format::builder::MessageBuilderInput input(
      typeid(lumberjack::format::AbstractMessageBuilder));

  std::string result = subject.buildMessage(&input);

  EXPECT_EQ(result, "AbstractMessageBuilder ");
}

TEST_F(SourceMessageAppenderTest, FreeFunctionSuccess)
{
  lumberjack::format::SourceMessageAppender subject(
      typeid(sampleFreeFunction),
      *testFormatSpecification);

  lumberjack::format::builder::MessageBuilderInput input(
      typeid(sampleFreeFunction));

  std::string result = subject.buildMessage(&input);

  EXPECT_EQ(result, "FNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES4_E ");
}

TEST_F(SourceMessageAppenderTest, LocalClassSuccess)
{
  lumberjack::format::SourceMessageAppender subject(
      typeid(Person),
      *testFormatSpecification);

  lumberjack::format::builder::MessageBuilderInput input(
      typeid(Person));

  std::string result = subject.buildMessage(&input);

  EXPECT_EQ(result, "Person ");
}

TEST_F(SourceMessageAppenderTest, LocalStructSuccess)
{
  lumberjack::format::SourceMessageAppender subject(
      typeid(Address),
      *testFormatSpecification);

  lumberjack::format::builder::MessageBuilderInput input(
      typeid(Address));

  std::string result = subject.buildMessage(&input);

  EXPECT_EQ(result, "Address ");
}