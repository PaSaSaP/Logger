#pragma once

#include "sqlite_modern_cpp.h"

#include "PsspLogger/LoggerInterface.h"

namespace pssplogger
{
LoggerInterface* getOutputLogger();
LoggerInterface* getDatabaseLogger(std::shared_ptr<sqlite::database>& db);
}  // namespace pssplogger
