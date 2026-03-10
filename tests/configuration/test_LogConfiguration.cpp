#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include "lumberjack/configuration/LogConfiguration.h"
#include "../format/MockLogFormatter.h"
#include "../writer/MockLogWriter.h"

class LogConfigurationTest : public testing::Test {
    protected:
        std::unique_ptr<lumberjack::format::ILogFormatter> mockLogFormatter;
        const int* logFormatterInvocationCount;

        std::vector<std::unique_ptr<lumberjack::writer::ILogWriter>> mockLogWriters;
        const std::vector<std::string>* linesWrittenToMock;
        const std::string simulatedFormattedLogOutput = "..:: sample log output ::..";

        /* --== Runs before each test is executed ==-- */
        void SetUp() override 
        {
            // ..:: Mock Log Formatter
            std::unique_ptr<lumberjack::format::MockLogFormatter> logFormatter = 
                std::make_unique<lumberjack::format::MockLogFormatter>(simulatedFormattedLogOutput);
            logFormatterInvocationCount = logFormatter->getInvocationCount();
            mockLogFormatter = std::move(logFormatter);
            
            // ..:: Mock Log Writer
            std::unique_ptr<lumberjack::writer::MockLogWriter> mockLogWriter = 
                std::make_unique<lumberjack::writer::MockLogWriter>();
            
            linesWrittenToMock = mockLogWriter->getLinesWritten();
            mockLogWriters.push_back(std::move(mockLogWriter));
        }

        void TearDown() override 
        {
            /* Runs after each test is complete */
        }

        void validateLogFormatterInvocations(int qty) 
        {
            if (logFormatterInvocationCount == nullptr) 
            {
                FAIL();
            }

            EXPECT_EQ(qty, *logFormatterInvocationCount);
        }

        void validateLogWriterInvocations(int qty)
        {
            if (linesWrittenToMock == nullptr) 
            {
                FAIL();
            }

            std::size_t numberOfLinesWritten = linesWrittenToMock->size();
            EXPECT_EQ(qty, numberOfLinesWritten);            
        }

        void validateLogWriterIsCalledWithEntry(const std::string &entry)
        {
            if (linesWrittenToMock == nullptr) 
            {
                FAIL();
            }
            
            bool lineFound = false;
            for(const std::string &line : *linesWrittenToMock) 
            {
                bool lineEntryMatch = entry == line;
                lineFound |= lineEntryMatch;
            }

            EXPECT_TRUE( lineFound );
        }
};

TEST_F(LogConfigurationTest, TestFormatterWriterWiring) {
    lumberjack::configuration::LogConfiguration subject(
        lumberjack::LogLevel::INFO, 
        std::move(mockLogFormatter), 
        std::move(mockLogWriters));

    subject.log(typeid(lumberjack::format::MockLogFormatter), lumberjack::LogLevel::INFO, "sample");

    validateLogFormatterInvocations(1);
    validateLogWriterIsCalledWithEntry(simulatedFormattedLogOutput);
    validateLogWriterInvocations(1);
}

TEST_F(LogConfigurationTest, ValidateNullFormatter) {
    try 
    {
        lumberjack::configuration::LogConfiguration subject(
        lumberjack::LogLevel::INFO, 
        nullptr, 
        std::move(mockLogWriters));

        std::cout << "Exception was expected to be thrown!\n";
        FAIL();
    } catch (const std::invalid_argument& expectedException)
    {
        std::cout << "Invalid Argument identified on null log formatter\n";
        SUCCEED();   
    }
}

TEST_F(LogConfigurationTest, ValidateNullWriter) {
    std::vector<std::unique_ptr<lumberjack::writer::ILogWriter>> nullLogWriters;
    nullLogWriters.push_back(nullptr);

    try
    {
        lumberjack::configuration::LogConfiguration subject(
        lumberjack::LogLevel::INFO, 
        std::move(mockLogFormatter), 
        std::move(nullLogWriters));

        std::cout << "Exception was expected to be thrown!\n";
        FAIL();
    } catch (const std::invalid_argument& expectedException)
    {
        std::cout << "Invalid Argument identified on null log writer\n";
        SUCCEED();   
    }
}

TEST_F(LogConfigurationTest, TestLogLevelOutOfBounds) {
    lumberjack::configuration::LogConfiguration subject(
        lumberjack::LogLevel::ERROR, 
        std::move(mockLogFormatter), 
        std::move(mockLogWriters));

    subject.log(typeid(lumberjack::format::MockLogFormatter), lumberjack::LogLevel::INFO, "sample");

    validateLogFormatterInvocations(0);
    validateLogWriterInvocations(0);
}

TEST_F(LogConfigurationTest, TestLogLevelWithinBounds) {
    lumberjack::configuration::LogConfiguration subject(
        lumberjack::LogLevel::INFO, 
        std::move(mockLogFormatter), 
        std::move(mockLogWriters));

    subject.log(typeid(lumberjack::format::MockLogFormatter), lumberjack::LogLevel::WARNING, "sample");

    validateLogFormatterInvocations(1);
    validateLogWriterInvocations(1);
}

TEST_F(LogConfigurationTest, TestLogLevelOnBounds) {
    lumberjack::configuration::LogConfiguration subject(
        lumberjack::LogLevel::INFO, 
        std::move(mockLogFormatter), 
        std::move(mockLogWriters));

    subject.log(typeid(lumberjack::format::MockLogFormatter), lumberjack::LogLevel::INFO, "sample");

    validateLogFormatterInvocations(1);
    validateLogWriterInvocations(1);
}