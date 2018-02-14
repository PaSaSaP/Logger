#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace logger
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
std::string const& logLevelAsText(LogLevel l);

class LoggerInterface
{
 public:
  virtual ~LoggerInterface() {}

  virtual void log(LogLevel level, std::string const& file,
                   std::string const& func, long long line,
                   std::string const& msg) = 0;
  static LoggerInterface* getLogger();
  static void setLogger(LoggerInterface* logger);

 private:
  static std::unique_ptr<LoggerInterface> logger;
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
}  // namespace logger

#define LOG(level) \
  logger::LoggerEvent{(level), __FILE__, __func__, __LINE__}.getStream()
