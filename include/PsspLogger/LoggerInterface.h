#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace pssplogger
{
enum class LogLevel
{
  trace,
  debug,
  info,
  warning,
  error,
  NumberOfEnums,
};
std::string const& logLevelAsText(LogLevel logLevel);

class LoggerInterface
{
 public:
  virtual ~LoggerInterface() {}

  virtual void log(LogLevel level, std::string const& file,
                   std::string const& func, long long line,
                   std::string const& msg) = 0;
  static LoggerInterface* getLogger();
  static void setLogger(LoggerInterface* pssplogger);

 private:
  static std::unique_ptr<LoggerInterface> pssplogger;
};

class LoggerEvent
{
 public:
  std::ostream& getStream();

  LoggerEvent(LogLevel level, std::string const& file, std::string const& func,
              long long line);
  ~LoggerEvent();

 private:
  LogLevel level;
  std::string file;
  std::string func;
  unsigned line;
  std::ostringstream ostr;
};
}  // namespace pssplogger

#define LOG(level) \
  pssplogger::LoggerEvent{(level), __FILE__, __func__, __LINE__}.getStream()
