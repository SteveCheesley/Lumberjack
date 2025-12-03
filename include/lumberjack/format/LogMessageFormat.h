#ifndef LOGMESSAGEFORMAT_H
#define LOGMESSAGEFORMAT_H

namespace lumberjack::format
{
    class LogMessageFormat {
        private:
            bool datePrinted;
            bool timePrinted;
            bool levelPrinted;
            bool sourcePrinted;
        public:
            LogMessageFormat(
                const bool datePrinted, 
                const bool timePrinted, 
                const bool levelPrinted,
                const bool sourcePrinted);
            bool isDatePrinted() const;
            bool isTimePrinted() const;
            bool isLevelPrinted() const;
            bool isSourcePrinted() const;
    };
};

#endif