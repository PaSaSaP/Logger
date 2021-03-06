#include <sstream>
#include <string>

#include "PsspLogger/OutputLogger.h"

void pssplogger::OutputLogger::log(LogLevel level, std::string const& file,
                               std::string const& func, long long line,
                               std::string const& msg)
{
  std::ostringstream ostr;
  ostr << logLevelAsText(level) << " | " << file << ':' << line << " | " << func
       << " | " << msg << '\n';
  std::cout << ostr.str();
}
