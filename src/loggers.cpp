#include "sqlite_modern_cpp.h"

#include "Logger/DatabaseLogger.h"
#include "Logger/LoggerInterface.h"
#include "Logger/OutputLogger.h"
#include "Logger/loggers.h"

logger::LoggerInterface* logger::getOutputLogger()
{
  return new OutputLogger{};
}

logger::LoggerInterface* logger::getDatabaseLogger(
    std::shared_ptr<sqlite::database>& db)
{
  return new DatabaseLogger{db};
}
