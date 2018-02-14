#include <cassert>
#include <memory>
#include <string>

#include "Logger/LoggerInterface.h"

std::unique_ptr<logger::LoggerInterface> logger::LoggerInterface::logger{
    nullptr};

namespace
{
std::string const LoggerLevelsAsText[]{
    "trace", "debug", "info", "warning", "error",
};
}

std::string const& logger::logLevelAsText(LogLevel level)
{
  assert(static_cast<int>(level) >= 0 && level < LogLevel::NumberOfEnums);
  return LoggerLevelsAsText[static_cast<int>(level)];
}

logger::LoggerInterface* logger::LoggerInterface::getLogger()
{
  return LoggerInterface::logger.get();
}

void logger::LoggerInterface::setLogger(LoggerInterface* logger)
{
  LoggerInterface::logger.reset(logger);
}

std::ostream& logger::LoggerEvent::getStream() { return ostr; }

logger::LoggerEvent::LoggerEvent(LogLevel level, std::string const& file,
                                 std::string const& func, long long line)
    : level(level), file(file), func(func), line(line)
{
}
logger::LoggerEvent::~LoggerEvent()
{
  LoggerInterface::getLogger()->log(level, file, func, line, ostr.str());
}
