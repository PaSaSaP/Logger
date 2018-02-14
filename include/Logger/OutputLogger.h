#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include "Logger/LoggerInterface.h"

namespace logger {

    class OutputLogger: public LoggerInterface
    {
    public:
        void
        log(LogLevel level, std::string const &file, std::string const &func, long long line, std::string const& msg) override;
    };
}
