/*
 * Configuration.h
 *
 *  Created on: May 3, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>
#include <map>
#include <Poco/Util/Validator.h>
#include <Poco/AutoPtr.h>
#include <Poco/BasicEvent.h>

using Poco::AutoPtr;
using Poco::Util::Validator;
using Poco::BasicEvent;

namespace Thrower
{
  class ConfigurationOption
  {
  public:
    ConfigurationOption();
    ConfigurationOption(
        const std::string& name,
        const std::string& description,
        const std::string& argument,
        const std::string& defaultValue,
        Validator* validator
        );
    ~ConfigurationOption();
    void setValue(const std::string& value);
    inline const std::string& getName() const;
    inline const std::string& getDescription() const;
    inline const std::string& getArgument() const;
    inline const std::string& getValue() const;
    inline AutoPtr<Validator>& getValidator();
  private:
    std::string _name;
    std::string _description;
    std::string _argument;
    std::string _defaultValue;
    AutoPtr<Validator> _validator;
    std::string _value;
  };

  //ConfigurationOption inline section
  inline const std::string&
  ConfigurationOption::getName() const
  {
    return _name;
  }

  inline const std::string&
  ConfigurationOption::getDescription() const
  {
    return _description;
  }

  inline const std::string&
  ConfigurationOption::getArgument() const
  {
    return _argument;
  }

  inline const std::string&
  ConfigurationOption::getValue() const
  {
    if (_value.empty())
    {
      return _defaultValue;
    }
    return _value;
  }

  inline AutoPtr<Validator>&
    ConfigurationOption::getValidator()
    {
      return _validator;
    }
  //ConfigurationOption end of inline section

  class Configuration
  {
  public:
    Configuration();
    virtual
    ~Configuration();
    void handleOption(const std::string& name,
                            const std::string& value);
    inline std::map<std::string, ConfigurationOption>::const_iterator
      begin() const;
    inline std::map<std::string, ConfigurationOption>::const_iterator
      end() const;
    const std::string& getValue(const std::string& name);

    BasicEvent<std::string> optionUpdated;
  private:
    std::map<std::string, ConfigurationOption> _options;
  };

  //Configuration inline section
  inline std::map<std::string, ConfigurationOption>::const_iterator
  Configuration::begin() const
  {
    return _options.begin();
  }

  inline std::map<std::string, ConfigurationOption>::const_iterator
  Configuration::end() const
  {
    return _options.end();
  }
  //Configuration end of inline section
} /* namespace Thrower */
#endif /* CONFIGURATION_H_ */
