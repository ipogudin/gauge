/*
 * Thrower.h
 *
 *  Created on: May 3, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef THROWER_H_
#define THROWER_H_

#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/OptionSet.h>

#include "Configuration.h"
#include "Logger.h"

using Poco::Util::ServerApplication;
using Poco::Util::OptionSet;

namespace Thrower
{

  /*
   * The main class representing the thrower application.
   */
  class Thrower: public Poco::Util::ServerApplication
  {
  public:
    Thrower();
    virtual ~Thrower();
  protected:
    void handleHelp(const std::string& name,
                      const std::string& value);
    void handlePort(const std::string& name,
                          const std::string& value);
    void defineOptions(OptionSet& options);
    int main(const std::vector<std::string>& args);
  private:
    bool helpRequested;
    Logger& logger;
    Configuration configuration;
  };

} /* namespace Thrower */
#endif /* THROWER_H_ */
