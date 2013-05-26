/*
 * Logger.cpp
 *
 *  Created on: May 5, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include "Logger.h"

#include "Poco/AsyncChannel.h"
#include "Poco/ConsoleChannel.h"

using Poco::AsyncChannel;
using Poco::ConsoleChannel;

namespace Thrower
{
  //static public
  Logger& Logger::logger(const std::string& name)
  {
    Logger* logger = new Logger(Poco::Logger::get(name));
    return *logger;
  }

  void Logger::setLevel(const std::string& level)
  {
    std::vector<std::string> names;
    Poco::Logger::names(names);
    for(
        std::vector<std::string>::iterator it = names.begin();
        it != names.end();
        ++it) {
      Poco::Logger::get((std::string)*it).setLevel(level);
    }
  }

  //public
  Logger::~Logger()
  {
    // TODO Auto-generated destructor stub
  }

  //protected
  Logger::Logger(Poco::Logger& logger):_logger(logger)
  {

  }
} /* namespace Thrower */
