#include <cassert>
#include <memory>
#include <string>

#include "PsspLogger/LoggerInterface.h"

std::unique_ptr<pssplogger::LoggerInterface> pssplogger::LoggerInterface::pssplogger{
    nullptr};

namespace
{
std::string const LoggerLevelsAsText[]{
    "trace", "debug", "info", "warning", "error",
};
}

std::string const& pssplogger::logLevelAsText(LogLevel logLevel)
{
  assert(static_cast<int>(logLevel) >= 0 && logLevel < LogLevel::NumberOfEnums);
  return LoggerLevelsAsText[static_cast<int>(logLevel)];
}

pssplogger::LoggerInterface* pssplogger::LoggerInterface::getLogger()
{
  return LoggerInterface::pssplogger.get();
}

void pssplogger::LoggerInterface::setLogger(LoggerInterface* pssplogger)
{
  LoggerInterface::pssplogger.reset(pssplogger);
}

std::ostream& pssplogger::LoggerEvent::getStream() { return ostr; }

pssplogger::LoggerEvent::LoggerEvent(LogLevel level, std::string const& file,
                                 std::string const& func, long long line)
    : level(level), file(file), func(func), line(line)
{
}
pssplogger::LoggerEvent::~LoggerEvent()
{
  LoggerInterface::getLogger()->log(level, file, func, line, ostr.str());
}
