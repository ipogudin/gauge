/*
 * Configuration.cpp
 *
 *  Created on: May 3, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include "Configuration.h"

namespace Thrower
{

  Configuration::Configuration():port(4040)
  {

  }

  Configuration::~Configuration()
  {

  }

  unsigned Configuration::getPort() const
  {
    return port;
  }

  void Configuration::setPort(unsigned int port)
  {
    this->port = port;
  }

} /* namespace Thrower */
