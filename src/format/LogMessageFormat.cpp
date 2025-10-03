#include "lumberjack/format/LogMessageFormat.h"

using lumberjack::format::LogMessageFormat;

namespace lumberjack::format
{
    LogMessageFormat::LogMessageFormat(
        const bool datePrinted,
        const bool timePrinted,
        const bool sourcePrinted
    )
    {
        this->datePrinted = datePrinted;
        this->timePrinted = timePrinted;
        this->sourcePrinted = sourcePrinted;
    }

    bool LogMessageFormat::isDatePrinted() const
    {
        return datePrinted;
    }

    bool LogMessageFormat::isTimePrinted() const
    {
        return timePrinted;
    }

    bool LogMessageFormat::isSourcePrinted() const
    {
        return sourcePrinted;
    }
};