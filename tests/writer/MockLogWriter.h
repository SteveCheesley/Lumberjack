#ifndef MOCKLOGWRITER_H
#define MOCKLOGWRITER_H

#include <vector>

#include "lumberjack/writer/ILogWriter.h"

namespace lumberjack::writer
{
    class MockLogWriter : public ILogWriter 
    {
        private:
            std::vector<std::string> linesWritten_;
        public:
            MockLogWriter() = default;
      
            void writeToLog(const std::string& entry) override
            {
                this->linesWritten_.push_back(entry);
            }

            const std::vector<std::string>* getLinesWritten() const
            {
                return &this->linesWritten_;
            }
    };
}

#endif