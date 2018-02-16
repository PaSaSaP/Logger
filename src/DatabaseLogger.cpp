#include <cassert>
#include <memory>

#include "sqlite_modern_cpp.h"

#include "Logger/DatabaseLogger.h"

void logger::DatabaseLogger::log(logger::LogLevel level,
                                 std::string const& file,
                                 std::string const& func, long long line,
                                 std::string const& msg)
{
  *database
      << "insert into logs (level, file, line, func, msg) values (?,?,?,?,?);"
      << logger::logLevelAsText(level) << file << line << func << msg;
}

logger::DatabaseLogger::DatabaseLogger(
    std::shared_ptr<sqlite::database> const& db)
    : database(db)
{
  assert(nullptr != database.get());
  *database << "create table if not exists logs ("
               "   _id integer primary key autoincrement not null,"
               "   level text,"
               "   file text,"
               "   line int,"
               "   func text,"
               "   msg func"
               ");";
}
