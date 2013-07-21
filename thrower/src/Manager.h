/*
 * Manager.h
 *
 *  Created on: Jul 14, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include <Poco/Runnable.h>
#include <Poco/Thread.h>

#include "Configuration.h"

using Poco::Runnable;
using Poco::Thread;

namespace Thrower
{
  /*
   * This class contains essential logic
   * to interact with the conductor (a central remote controller) and
   * to manage thrower's internals.
   */
  class Manager: public Runnable
  {
  public:
    Manager();
    virtual
    ~Manager();
    void initialize(Configuration& conf);
    void run();
    void start();
    void stop();
  private:
    Configuration* _conf;
    Thread _thread;
  };
} /* namespace Thrower */
#endif /* MANAGER_H_ */
