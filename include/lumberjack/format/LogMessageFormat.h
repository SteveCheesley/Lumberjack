#ifndef LOGMESSAGEFORMAT_H
#define LOGMESSAGEFORMAT_H

namespace lumberjack::format
{
    class LogMessageFormat {
        private:
            bool datePrinted;
            bool timePrinted;
            bool sourcePrinted;
        public:
            LogMessageFormat(
                const bool datePrinted, 
                const bool timePrinted, 
                const bool sourcePrinted);
            bool isDatePrinted() const;
            bool isTimePrinted() const;
            bool isSourcePrinted() const;
    };
};

#endif