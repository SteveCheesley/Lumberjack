#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <algorithm>

#include <iostream>

#include "lumberjack/configuration/LogConfigurations.h"
#include "../configuration/MockLogConfiguration.h"

using ::testing::_;
using lumberjack::configuration::MockLogConfiguration;

class LogConfigurationsTest : public testing::Test {
    protected:
        MockLogConfiguration defaultMockConfiguration;
        MockLogConfiguration mockLogConfiguration;

        std::shared_ptr<int> defaultInvocationCount;
        std::shared_ptr<int> invocationCount;

        void SetUp() override 
        {
            defaultInvocationCount = defaultMockConfiguration.getInvocationCount();
            invocationCount = mockLogConfiguration.getInvocationCount();
        }

        void validateDefaultConfigurationInvocations(int expectedQty)
        {
            if (defaultInvocationCount == nullptr)
            {
                FAIL();
            }

            EXPECT_EQ(expectedQty, *defaultInvocationCount);
        }

        void validateConfigurationInvocations(int expectedQty)
        {
            if (invocationCount == nullptr)
            {
                FAIL();
            }

            EXPECT_EQ(expectedQty, *invocationCount);
        }
};

TEST_F(LogConfigurationsTest, BasicSuccess) 
{
    lumberjack::configuration::LogConfigurations<MockLogConfiguration> subject(defaultMockConfiguration);

    subject.add(mockLogConfiguration);
    subject.log(
        typeid(MockLogConfiguration), 
        lumberjack::LogLevel::INFO, 
        "sample"
    );

    validateDefaultConfigurationInvocations(0);
    validateConfigurationInvocations(1);
}

TEST_F(LogConfigurationsTest, IsDefaultCalledOnFallback) 
{
    lumberjack::configuration::LogConfigurations<MockLogConfiguration> subject(defaultMockConfiguration);
    
    subject.log(
        typeid(MockLogConfiguration), 
        lumberjack::LogLevel::INFO, 
        "sample"
    );

    validateDefaultConfigurationInvocations(1);
    validateConfigurationInvocations(0);
}


TEST_F(LogConfigurationsTest, AreConfigurationsClearedCorrectly) 
{
    lumberjack::configuration::LogConfigurations<MockLogConfiguration> subject(defaultMockConfiguration);

    subject.add(mockLogConfiguration);
 
    subject.log(
        typeid(MockLogConfiguration), 
        lumberjack::LogLevel::INFO, 
        "sample"
    );

    validateDefaultConfigurationInvocations(0);
    validateConfigurationInvocations(1);

    // Clear the configurations
    subject.clearAllConfigurations();

    subject.log(
        typeid(MockLogConfiguration), 
        lumberjack::LogLevel::INFO, 
        "sample"
    );

    validateDefaultConfigurationInvocations(1);
    validateConfigurationInvocations(1);
}