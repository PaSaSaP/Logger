#pragma once

#include <memory>

#include "sqlite_modern_cpp.h"

#include "Logger/LoggerInterface.h"

namespace logger
{
class DatabaseLogger : public LoggerInterface
{
 public:
  void log(LogLevel level, std::string const& file, std::string const& func,
           long long line, std::string const& msg) override;

  DatabaseLogger(std::shared_ptr<sqlite::database>& db);

 private:
  std::shared_ptr<sqlite::database> database;
};
}  // namespace logger
