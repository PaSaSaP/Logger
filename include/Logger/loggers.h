#pragma once

#include "sqlite_modern_cpp.h"

#include "Logger/LoggerInterface.h"

namespace logger
{
    LoggerInterface* getOutputLogger();
    LoggerInterface* getDatabaseLogger(std::shared_ptr<sqlite::database>& db);
}
