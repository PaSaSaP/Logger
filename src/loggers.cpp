#include "sqlite_modern_cpp.h"

#include "PsspLogger/DatabaseLogger.h"
#include "PsspLogger/LoggerInterface.h"
#include "PsspLogger/OutputLogger.h"
#include "PsspLogger/loggers.h"

pssplogger::LoggerInterface* pssplogger::getOutputLogger()
{
  return new OutputLogger{};
}

pssplogger::LoggerInterface* pssplogger::getDatabaseLogger(
    std::shared_ptr<sqlite::database>& db)
{
  return new DatabaseLogger{db};
}
