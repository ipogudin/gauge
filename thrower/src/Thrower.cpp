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

#include "Thrower.h"

using Poco::Util::Application;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::Util::IntValidator;

namespace Thrower
{

  Thrower::Thrower():helpRequested(false)
  {

  }

  Thrower::~Thrower()
  {

  }

  void Thrower::defineOptions(OptionSet& options)
  {
    ServerApplication::defineOptions(options);

    options.addOption(
      Option("help", "h", "Display help information")
          .required(false)
          .repeatable(false)
          .callback(OptionCallback<Thrower>(
              this, &Thrower::handleHelp)));
    options.addOption(
      Option("port", "", "Set a management port value")
          .required(false)
          .repeatable(false)
          .argument("port")
          .validator(new IntValidator(1, 65535))
          .callback(OptionCallback<Thrower>(
              this, &Thrower::handlePort)));
  }

  void Thrower::handlePort(const std::string& name,
                    const std::string& value)
  {
    configuration.setPort(stoi(value));
  }

  void Thrower::handleHelp(const std::string& name,
                  const std::string& value)
  {
    HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader(
        "Thrower is a part of tool for performance testing.");
    helpFormatter.format(std::cout);
    stopOptionsProcessing();
    helpRequested = true;
  }

  int Thrower::main(const std::vector<std::string>& args)
  {
    if (!helpRequested)
    {
      waitForTerminationRequest();
    }
    return Application::EXIT_OK;
  }

} /* namespace Thrower */


