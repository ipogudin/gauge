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

  Logger& Logger::logger(const std::string& name)
  {
    Logger* logger = new Logger(Poco::Logger::get(name));
    return *logger;
  }

  Logger::Logger(Poco::Logger& logger):_logger(logger)
  {

  }

  Logger::~Logger()
  {
    // TODO Auto-generated destructor stub
  }

  void Logger::setLevel(const std::string& level)
  {
    _logger.setLevel(level);
  }
} /* namespace Thrower */
