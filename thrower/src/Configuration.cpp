/*
 * Configuration.cpp
 *
 *  Created on: May 3, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include "Configuration.h"

namespace Thrower
{

  Configuration::Configuration():_port(4040),_logLevel("notification")
  {

  }

  Configuration::~Configuration()
  {

  }

  unsigned Configuration::getPort() const
  {
    return _port;
  }

  void Configuration::setPort(unsigned int port)
  {
    _port = port;
  }

  std::string Configuration::getLogLevel() const
  {
    return _logLevel;
  }

  void Configuration::setLogLevel(std::string logLevel)
  {
    _logLevel = logLevel;
  }
} /* namespace Thrower */
