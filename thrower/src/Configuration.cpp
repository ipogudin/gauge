/*
 * Configuration.cpp
 *
 *  Created on: May 3, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <Poco/Util/IntValidator.h>
#include <Poco/Util/RegExpValidator.h>

#include "Configuration.h"

using Poco::Util::IntValidator;
using Poco::Util::RegExpValidator;

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

  Configuration::Configuration()
  {
    _options["port"] = ConfigurationOption(
        "port",
        "Set a management port",
        "port",
        "4040",
        new IntValidator(1, 65535)
        );
    _options["loglevel"] = ConfigurationOption(
        "loglevel",
        "Set a log level (default information)\n"
        "Available levels: "
        "trace, debug, information, notice, warning, error, critical, fatal",
        "loglevel",
        "notice",
        new RegExpValidator(
          "(trace|debug|information|notice|warning|error|critical|fatal)"
          )
        );
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
    throw "";
  }

} /* namespace Thrower */
