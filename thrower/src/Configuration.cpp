/*
 * Configuration.cpp
 *
 *  Created on: May 3, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <stdio.h>

#include <Poco/Util/IntValidator.h>
#include <Poco/Util/RegExpValidator.h>
#include <Poco/Delegate.h>

#include "Configuration.h"
#include "Exception.h"

using namespace std;

using Poco::Util::IntValidator;
using Poco::Util::RegExpValidator;
using Poco::Delegate;

namespace thrower
{
  //class ConfigurationEntry
  ConfigurationOption::ConfigurationOption():_validator(NULL)
  {

  }

  ConfigurationOption::ConfigurationOption(
       const string& name,
       const string& description,
       const string& argument,
       const string& defaultValue,
       Validator* validator):
           _name(name),
           _description(description),
           _argument(argument),
           _defaultValue(defaultValue),
           _validator(validator)
  {
  }

  ConfigurationOption::~ConfigurationOption()
  {
    _validator = NULL;
  }

  void
  ConfigurationOption::setValue(const string& value)
  {
    _value = value;
  }
  //class Configuration

  const string Configuration::PORT = "port";
  const string Configuration::LOG_LEVEL = "loglevel";
  const string Configuration::PROTOCOL_TIMEOUT = "protocoltimeout";

  Configuration::Configuration():logger(Logger::logger("Configuration"))
  {
    _options[PORT] = ConfigurationOption(
        PORT,
        "Set a management port (default 4040)",
        PORT,
        "4040",
        new IntValidator(1, 65535)
        );
    _options[LOG_LEVEL] = ConfigurationOption(
        LOG_LEVEL,
        "Set a log level (default information)\n"
        "Available levels: "
        "trace, debug, information, notice, warning, error, critical, fatal",
        LOG_LEVEL,
        "notice",
        new RegExpValidator(
          "(trace|debug|information|notice|warning|error|critical|fatal)"
          )
        );
    _options[PROTOCOL_TIMEOUT] = ConfigurationOption(
        PROTOCOL_TIMEOUT,
        "Set a protocols timeout (ms)",
        PROTOCOL_TIMEOUT,
        "10000",
        new IntValidator(0, 1000000)
        );

    optionUpdated += Poco::delegate(this, &Configuration::onOptionUpdated);
  }

  Configuration::~Configuration()
  {

  }

  void
  Configuration::handleOption(const string& name, const string& value)
  {
    if (_options.find(name) != _options.end())
    {
      _options[name].setValue(value);
      string n = name;
      optionUpdated.notify(this, n);
    }
  }

  const string&
  Configuration::getValue(const string& name)
  {
    if (_options.find(name) != _options.end())
    {
      return _options[name].getValue();
    }
    throw Poco::LogicException("A parameter " + name + " is not found");
  }

  void
  Configuration::onOptionUpdated(const void* sender, string& name)
  {
    if (name == LOG_LEVEL)
    {
      Logger::setLevel(this->getValue(name));
    }

    if (logger.trace())
    {
      string message = "The option \"";
      message.append(name);
      message.append("\" was updated");
      logger.trace(message);
    }
  }

} /* namespace Thrower */
