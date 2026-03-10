#include <gtest/gtest.h>
#include "lumberjack/logging.h"
#include "lumberjack/Logger.h"
#include "lumberjack/format/DefaultLogFormatter.h"
#include "lumberjack/writer/StandardOutputWriter.h"
#include "lumberjack/configuration/LogConfiguration.h"
#include "lumberjack/configuration/LogConfigurations.h"
#include "../format/MockLogFormatter.h"

class LoggerTest : public ::testing::Test 
{
    protected:
        static void SetUpTestSuite() 
        {
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
                std::make_unique<lumberjack::configuration::LogConfigurations<lumberjack::configuration::LogConfiguration>>(std::move(logConfigurationVector));

            lumberjack::set_logConfigurations(std::move(logConfigurations));
        }
};

TEST_F(LoggerTest, WritesToConsole)
{
    lumberjack::Logger subject(typeid(lumberjack::format::MockLogFormatter));

    subject.info("Application starting...");
    subject.info("Connecting to database 'UserDB'...");
    subject.info("Database connection established.");
    subject.warn("User 'alice' login attempt.");
    subject.info("User 'alice' authenticated successfully.");
    subject.info("Received GET request at /api/users");
    subject.info("Processing request for user ID 42");
    subject.info("Request processed successfully in 27ms");
    subject.info("Reading configuration file 'config.yml'");
    subject.info("Configuration loaded successfully");
    subject.info("Initiating payment for order #12345");
    subject.info("Payment gateway responded with status: SUCCESS");
    subject.info("Sending confirmation email to 'alice@example.com'");
    subject.info("Email sent successfully");
    subject.info("Cache miss for key 'user_42_profile'");
    subject.info("Caching profile data for user ID 42");
    subject.info("User 'bob' login attempt.");
    subject.error("User 'bob' failed authentication: invalid password");
    subject.info("Scheduled cleanup job started");
    subject.info("Cleanup job completed, removed 12 expired sessions");
    subject.info("Application shutting down...");


}