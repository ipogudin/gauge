/*
 * Thrower.h
 *
 *  Created on: May 3, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef THROWER_H_
#define THROWER_H_

#include <google/protobuf/stubs/common.h>

#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/OptionSet.h>

#include "Configuration.h"
#include "Logger.h"
#include "Manager.h"

using namespace std;

using Poco::Util::ServerApplication;
using Poco::Util::OptionSet;

namespace thrower
{

  /*
   * The main class representing the thrower application.
   */
  class Thrower: public ServerApplication
  {
  public:
    Thrower();
    virtual ~Thrower();
  protected:
    void handleHelp(const string& name,
                      const string& value);
    void defineOptions(OptionSet& options);
    int main(const vector<string>& args);
  private:
    Logger _logger;
    bool _helpRequested;
    Configuration _configuration;
    Manager _manager;
  };

  extern Logger protobufLogger;

  void LogHandler(google::protobuf::LogLevel level,
          const char* filename, int line, const std::string& message);
} /* namespace Thrower */
#endif /* THROWER_H_ */
