#include <ctime>
#include <string>
#include <gtest/gtest.h>
#include "Logger.h"
#include "StandardOutputLogger.h"

using logger::Logger;
using logger::LogLevel;
using logger::StandardOutputLogger;
using logger::LoggerConfiguration;

struct DateFormatHelper {
    inline static std::string DATE_LOG_FORMAT = "%F"; 

    time_t getTimeNow() {
        return time(NULL);
    }

    std::string getExpectedDate(const time_t* timestampPtr) {
        tm datetime = *localtime(timestampPtr);

        char buffer [128];
        if (std::strftime(buffer, sizeof(buffer), DATE_LOG_FORMAT.c_str(), &datetime)) {
            return std::string(buffer);
        }

        return {};
    }
};

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

TEST_F(StandardOutputLoggerTester, WritesDateProperly) {
    DateFormatHelper dateFormatHelper;
    time_t now = dateFormatHelper.getTimeNow();

    std::cout << "..:: DEBUG ::.." << std::endl;
    std::cout << now << std::endl;
    std::cout << "....:: Formatted Date:" << dateFormatHelper.getExpectedDate(&now) << std::endl;
    std::cout << "..:: END DEBUG ::.." << std::endl;

    logger = new StandardOutputLogger(new LoggerConfiguration(
        true, 
        false, 
        LogLevel::ERROR));
    logger->log(LogLevel::ERROR, "Hello, world!");

    std::string output = getCapturedOutput();

    EXPECT_EQ(output, "INFO  :: Hello, World!");
}