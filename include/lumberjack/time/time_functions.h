#ifndef TIME_FUNCTIONS_H
#define TIME_FUNCTIONS_H

#include <ctime>
#include <string>

#include "lumberjack/time/ITimeProvider.h"

using lumberjack::time::ITimeProvider;

std::tm* getUtcTime(ITimeProvider* timeProvider);
std::string formatTime(std::tm* timestamp, std::string formatString);

#endif