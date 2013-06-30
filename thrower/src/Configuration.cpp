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

using Poco::Util::IntValidator;
using Poco::Util::RegExpValidator;
using Poco::Delegate;

namespace Thrower
{
  //class ConfigurationEntry
  ConfigurationOption::ConfigurationOption():_validator(NULL)
  {

  }

  ConfigurationOption::ConfigurationOption(
       const std::string& name,
       const std::string& description,
       const std::string& argument,
       const std::string& defaultValue,
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
  ConfigurationOption::setValue(const std::string& value)
  {
    _value = value;
  }
  //class Configuration

  const std::string Configuration::PORT = "port";
  const std::string Configuration::LOG_LEVEL = "loglevel";

  Configuration::Configuration():logger(Logger::logger("Configuration"))
  {
    _options[PORT] = ConfigurationOption(
        PORT,
        "Set a management port",
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

    optionUpdated += Poco::delegate(this, &Configuration::onOptionUpdated);
  }

  Configuration::~Configuration()
  {

  }

  void
  Configuration::handleOption(const std::string& name, const std::string& value)
  {
    if (_options.find(name) != _options.end())
    {
      _options[name].setValue(value);
      std::string n = name;
      optionUpdated.notify(this, n);
    }
  }

  const std::string&
  Configuration::getValue(const std::string& name)
  {
    if (_options.find(name) != _options.end())
    {
      return _options[name].getValue();
    }
    throw Poco::LogicException("A parameter " + name + " is not found");
  }

  void
  Configuration::onOptionUpdated(const void* sender, std::string& name)
  {
    if (name == LOG_LEVEL)
    {
      Logger::setLevel(this->getValue(name));
    }

    if (logger.trace())
    {
      std::string message = "The option \"";
      message.append(name);
      message.append("\" was updated");
      logger.trace(message);
    }
  }

} /* namespace Thrower */
