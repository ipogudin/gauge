/*
 * Logger.cpp
 *
 *  Created on: May 5, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include "Logger.h"

#include "Poco/AsyncChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FormattingChannel.h"
#include "Poco/PatternFormatter.h"
#include "Poco/AutoPtr.h"

using namespace std;

using Poco::AsyncChannel;
using Poco::ConsoleChannel;
using Poco::FormattingChannel;
using Poco::PatternFormatter;
using Poco::AutoPtr;

namespace Thrower
{
  //static public
  void Logger::initialize()
  {
    ConsoleChannel* consoleChannel = new ConsoleChannel;
    PatternFormatter* patternFormatter = new PatternFormatter;
    patternFormatter->setProperty("pattern", "%Y-%m-%d %H:%M:%S.%i [%p] %s: %t");
    FormattingChannel* formattingChannel = new FormattingChannel(patternFormatter, consoleChannel);
    Poco::Logger::setChannel("", formattingChannel);
  }

  Logger& Logger::logger(const string& name)
  {
    Logger* logger = new Logger(Poco::Logger::get(name));
    return *logger;
  }

  void Logger::setLevel(const string& level)
  {
    vector<string> names;
    Poco::Logger::names(names);
    for(auto& name : names) {
      Poco::Logger::get((string)name).setLevel(level);
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
