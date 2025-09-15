#include <gtest/gtest.h>
#include "Logger.h"
#include "StandardOutputLogger.h"

using logger::Logger;
using logger::LogLevel;
using logger::StandardOutputLogger;
using logger::LoggerConfiguration;

class StandardOutputLoggerTester : public testing::Test {
    protected:
        std::streambuf* originalCoutBuffer = std::cout.rdbuf();
        std::stringstream buffer;

        Logger* logger;

        StandardOutputLoggerTester() {
            // SetUp
            originalCoutBuffer = std::cout.rdbuf();
            std::cout.rdbuf(buffer.rdbuf());
        }

        ~StandardOutputLoggerTester() {
            // TearDown
            std::cout.rdbuf(originalCoutBuffer);

        }

        std::string getCapturedOutput() const {
            return buffer.str();
        }

        void clearCapturedOutput() {
            buffer.str("");
            buffer.clear();
        }
};

TEST_F(StandardOutputLoggerTester, WritesBasicLogEntry) {
    logger = new StandardOutputLogger(new LoggerConfiguration(
        false, 
        false, 
        LogLevel::ERROR));
    logger->log(LogLevel::INFO, "Hello, world!");

    std::string output = getCapturedOutput();

    EXPECT_EQ(output, "INFO  :: Hello, World!");
}

TEST_F(StandardOutputLoggerTester, DoesNotWriteInvalidLevel) {
    logger = new StandardOutputLogger(new LoggerConfiguration(
        false, 
        false, 
        LogLevel::INFO));
    logger->log(LogLevel::ERROR, "Hello, world!");

    std::string output = getCapturedOutput();

    ASSERT_TRUE(output.empty());
}