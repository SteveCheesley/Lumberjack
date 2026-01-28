#include <gtest/gtest.h>
#include <vector>
#include "lumberjack/configuration/LogConfiguration.h"
#include "../format/MockLogFormatter.h"
#include "../writer/MockLogWriter.h"

TEST(LogConfigurationTest, BasicSuccessTest) {
    std::string formattedLogOutput = "..:: sample log output ::..";
    std::unique_ptr<lumberjack::format::ILogFormatter> mockLogFormatter = 
        std::make_unique<lumberjack::format::MockLogFormatter>(formattedLogOutput);
    
    std::vector<std::unique_ptr<lumberjack::writer::ILogWriter>> mockLogWriters;
    mockLogWriters.push_back(std::make_unique<lumberjack::writer::MockLogWriter>());

    lumberjack::configuration::LogConfiguration subject(lumberjack::LogLevel::INFO, std::move(mockLogFormatter), std::move(mockLogWriters));

    subject.log(typeid(lumberjack::format::MockLogFormatter), lumberjack::LogLevel::INFO, "sample");

    
}