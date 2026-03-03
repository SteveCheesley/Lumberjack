#include <gtest/gtest.h>
#include "lumberjack/Logger.h"
#include "../format/MockLogFormatter.h"

TEST(LoggerTest, WritesToConsole)
{
    lumberjack::Logger subject(typeid(lumberjack::format::MockLogFormatter));

    subject.info("Hello World..");
}