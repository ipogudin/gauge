/*
 * Thrower.cpp
 *
 *  Created on: May 3, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include <iostream>
#include <string>

#include <Poco/Util/Application.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/IntValidator.h>
#include <Poco/Util/RegExpValidator.h>
#include <Poco/Delegate.h>

#include "Thrower.h"

using namespace std;

using Poco::Util::Application;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::Util::IntValidator;
using Poco::Util::RegExpValidator;
using Poco::Delegate;

namespace Thrower
{

  Thrower::Thrower():_helpRequested(false),_logger(Logger::logger("Thrower"))
  {

  }

  Thrower::~Thrower()
  {

  }

  void Thrower::defineOptions(OptionSet& options)
  {
    Logger::initialize();
    setLogger(_logger.logger());

    ServerApplication::defineOptions(options);

    options.addOption(
      Option("help", "h", "Display help information")
          .required(false)
          .repeatable(false)
          .callback(OptionCallback<Thrower>(
              this, &Thrower::handleHelp)));

    for (auto& pair : _configuration)
    {
      ConfigurationOption co = pair.second;
      Option o(co.getName(), "", co.getDescription());
      o.required(false).repeatable(false);
      if (!co.getArgument().empty())
      {
        o.argument(co.getArgument());
        o.validator(co.getValidator());
      }
      o.callback(OptionCallback<Configuration>(
        &_configuration, &Configuration::handleOption
        ));
      options.addOption(o);
    }
  }

  void Thrower::handleHelp(const string& name,
                  const string& value)
  {
    HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader(
        "Thrower is a part of tool for performance testing.");
    helpFormatter.format(cout);
    stopOptionsProcessing();
    _helpRequested = true;
  }

  int Thrower::main(const vector<string>& args)
  {
    _logger.debug("Application has been started");
    if (!_helpRequested)
    {
      _manager.initialize(_configuration);
      _manager.start();
      waitForTerminationRequest();
      _manager.stop();
    }
    return Application::EXIT_OK;
  }
} /* namespace Thrower */


