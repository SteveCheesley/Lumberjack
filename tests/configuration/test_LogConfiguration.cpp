#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <map>
#include "lumberjack/configuration/LogConfiguration.h"
#include "../format/MockLogFormatter.h"
#include "../writer/MockLogWriter.h"

class LogConfigurationTest : public testing::Test {
    protected:
        std::unique_ptr<lumberjack::format::ILogFormatter> mockLogFormatter;
        std::vector<std::unique_ptr<lumberjack::writer::ILogWriter>> mockLogWriters;
        const std::vector<std::string>* linesWrittenToMock;

        void SetUp() override 
        {
            /* --== Runs before each test is executed ==-- */
    
            // ..:: Mock Log Formatter
            std::string formattedLogOutput = "..:: sample log output ::.."; // <- This will need to live somewhere else
            mockLogFormatter = std::make_unique<lumberjack::format::MockLogFormatter>(formattedLogOutput);
            
            // ..:: Mock Log Writer
            std::unique_ptr<lumberjack::writer::MockLogWriter> mockLogWriter = 
                std::make_unique<lumberjack::writer::MockLogWriter>();
            // TODO - Add a reset function to the mockLogWriter
            
            linesWrittenToMock = mockLogWriter->getLinesWritten();
            mockLogWriters.push_back(std::move(mockLogWriter));
        }

        void TearDown() override 
        {
            /* Runs after each test is complete */
        }
};

TEST_F(LogConfigurationTest, BasicSuccessTest) {
    lumberjack::configuration::LogConfiguration subject(
        lumberjack::LogLevel::INFO, 
        std::move(mockLogFormatter), 
        std::move(mockLogWriters));

    subject.log(typeid(lumberjack::format::MockLogFormatter), lumberjack::LogLevel::INFO, "sample");

    // TEST - Validate that the mock formatter was used as expected
    /* TODO */

    // TEST - Validate that the mock writer(s) were used as expected
    std::size_t numberOfLinesWritten = linesWrittenToMock->size();
    EXPECT_EQ(1, numberOfLinesWritten);

    
    // TODO - Turn this into a parameterised test to validate actions such as resources being missing
}