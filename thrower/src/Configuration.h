/*
 * Configuration.h
 *
 *  Created on: May 3, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>

namespace Thrower
{

  class Configuration
  {
  public:
    Configuration();
    virtual
    ~Configuration();

    unsigned getPort() const;
    void setPort(unsigned int port);

    std::string getLogLevel() const;
    void setLogLevel(std::string logLevel);

  private:
    unsigned int _port;
    std::string _logLevel;
  };

} /* namespace Thrower */
#endif /* CONFIGURATION_H_ */
