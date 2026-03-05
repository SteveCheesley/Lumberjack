#include <gtest/gtest.h>
#include "lumberjack/logging.h"
#include "lumberjack/Logger.h"
#include "lumberjack/format/DefaultLogFormatter.h"
#include "lumberjack/writer/StandardOutputWriter.h"
#include "lumberjack/configuration/LogConfiguration.h"
#include "lumberjack/configuration/LogConfigurations.h"
#include "../format/MockLogFormatter.h"

class GlobalTestEnvironment : public ::testing::Environment 
{
    public:
        void SetUp() override {
            // --== Runs once before all tests
            // Log Formatter
            std::unique_ptr<lumberjack::format::ILogFormatter> defaultLogFormatter = 
                std::make_unique<lumberjack::format::DefaultLogFormatter>();
            
            // Log Writer
            std::vector<std::unique_ptr<lumberjack::writer::ILogWriter>> logWriters;
            logWriters.push_back(std::make_unique<lumberjack::writer::StandardOutputWriter>());

            // Log Configuration
            lumberjack::configuration::LogConfiguration testLogConfiguration(
                lumberjack::LogLevel::INFO, 
                std::move(defaultLogFormatter), 
                std::move(logWriters));

            // Log Configuraitons
            std::vector<lumberjack::configuration::LogConfiguration> logConfigurationVector;
            logConfigurationVector.push_back(std::move(testLogConfiguration));

            std::unique_ptr<lumberjack::configuration::LogConfigurations<lumberjack::configuration::LogConfiguration>> logConfigurations = 
                std::make_unique<lumberjack::configuration::LogConfigurations<lumberjack::configuration::LogConfiguration>>(logConfigurationVector);

            lumberjack::set_logConfigurations(std::move(logConfigurations));
        }

        void TearDown() override {
            // --== Runs once after all tests
        }

        void setupLogConfigurations() {
            
        };
};

TEST(LoggerTest, WritesToConsole)
{
    lumberjack::Logger subject(typeid(lumberjack::format::MockLogFormatter));

    subject.warn("...::: Hello World ===|||=== :::...");

    // Now that I know this is working and that the issue was the wiring threshold I can set up a 
    // working example.
}