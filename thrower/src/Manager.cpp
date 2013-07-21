/*
 * Manager.cpp
 *
 *  Created on: Jul 14, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <stdio.h>

#include "Manager.h"

#include <Poco/RunnableAdapter.h>
using Poco::RunnableAdapter;

namespace Thrower
{

  Manager::Manager():_conf(NULL)
  {
    _thread.setName("Manager");
  }

  Manager::~Manager()
  {
    // TODO Auto-generated destructor stub
  }

  void Manager::initialize(Configuration& conf)
  {
    _conf = &conf;
  }

  void Manager::run()
  {
    while(1) {};
  }

  void Manager::start()
  {
    _thread.start(*this);
  }

  void Manager::stop()
  {

  }
} /* namespace Thrower */
