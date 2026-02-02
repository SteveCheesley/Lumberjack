#include <gtest/gtest.h>
#include <vector>
#include "lumberjack/configuration/LogConfiguration.h"
#include "../format/MockLogFormatter.h"
#include "../writer/MockLogWriter.h"

TEST(LogConfigurationTest, BasicSuccessTest) {
    std::string formattedLogOutput = "..:: sample log output ::..";
    std::unique_ptr<lumberjack::format::ILogFormatter> mockLogFormatter = 
        std::make_unique<lumberjack::format::MockLogFormatter>(formattedLogOutput);
    
    // Standalone initialisation of the mockLogWriter so I can extract the linesWritten from it.
    std::unique_ptr<lumberjack::writer::MockLogWriter> mockLogWriter = 
        std::make_unique<lumberjack::writer::MockLogWriter>();
    const std::vector<std::string>* linesWritten = mockLogWriter->getLinesWritten(); // Need this to read the lines that were written to the mockLogWriter

    std::vector<std::unique_ptr<lumberjack::writer::ILogWriter>> mockLogWriters;
    mockLogWriters.push_back(std::move(mockLogWriter));

    lumberjack::configuration::LogConfiguration subject(lumberjack::LogLevel::INFO, std::move(mockLogFormatter), std::move(mockLogWriters));

    subject.log(typeid(lumberjack::format::MockLogFormatter), lumberjack::LogLevel::INFO, "sample");

    // TODO - I need to put in code that verifies calls correctly
    std::size_t numberOfLinesWritten = linesWritten->size();
    EXPECT_EQ(1, numberOfLinesWritten);

    // ..:: Cleanup
    delete linesWritten;
    linesWritten = nullptr;
    
    // TODO - Turn this into a parameterised test to validate actions such as resources being missing
}