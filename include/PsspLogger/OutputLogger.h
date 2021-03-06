#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "PsspLogger/LoggerInterface.h"

namespace pssplogger
{
class OutputLogger : public LoggerInterface
{
 public:
  void log(LogLevel level, std::string const& file, std::string const& func,
           long long line, std::string const& msg) override;
};
}  // namespace pssplogger
