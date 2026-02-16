#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "lumberjack/configuration/LogConfigurations.h"
#include "../configuration/MockLogConfiguration.h"

using ::testing::_;

TEST(LogConfigurationsTest, TestBasicSuccess) 
{
    lumberjack::configuration::LogConfigurations subject;
    lumberjack::configuration::MockLogConfiguration mockLogConfiguration;

    EXPECT_CALL(mockLogConfiguration, log(_, _, _))
      .Times(1);

    subject.add(std::move(mockLogConfiguration));
    subject.log(
        typeid(lumberjack::configuration::MockLogConfiguration), 
        lumberjack::LogLevel::INFO, 
        "sample"
    );
}