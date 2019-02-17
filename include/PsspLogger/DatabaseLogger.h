#pragma once

#include <memory>

#include "sqlite_modern_cpp.h"

#include "PsspLogger/LoggerInterface.h"

namespace pssplogger
{
class DatabaseLogger : public LoggerInterface
{
 public:
  void log(LogLevel level, std::string const& file, std::string const& func,
           long long line, std::string const& msg) override;

  explicit DatabaseLogger(std::shared_ptr<sqlite::database> const& db);

 private:
  std::shared_ptr<sqlite::database> const database;
};
}  // namespace pssplogger
