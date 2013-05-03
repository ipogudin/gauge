/*
 * Configuration.h
 *
 *  Created on: May 3, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

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

  private:
    unsigned int port;
  };

} /* namespace Thrower */
#endif /* CONFIGURATION_H_ */
