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

#include "Logger.h"

using namespace std;

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
        const string& name,
        const string& description,
        const string& argument,
        const string& defaultValue,
        Validator* validator
        );
    ~ConfigurationOption();
    void setValue(const string& value);
    inline const string& getName() const;
    inline const string& getDescription() const;
    inline const string& getArgument() const;
    inline const string& getValue() const;
    inline AutoPtr<Validator>& getValidator();
  private:
    string _name;
    string _description;
    string _argument;
    string _defaultValue;
    AutoPtr<Validator> _validator;
    string _value;
  };

  //ConfigurationOption inline section
  inline const string&
  ConfigurationOption::getName() const
  {
    return _name;
  }

  inline const string&
  ConfigurationOption::getDescription() const
  {
    return _description;
  }

  inline const string&
  ConfigurationOption::getArgument() const
  {
    return _argument;
  }

  inline const string&
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
    virtual void handleOption(const string& name,
                            const string& value);
    virtual inline map<string, ConfigurationOption>::const_iterator
      begin() const;
    virtual inline map<string, ConfigurationOption>::const_iterator
      end() const;
    virtual const string& getValue(const string& name);
    virtual void onOptionUpdated(const void* sender, string& name);

    BasicEvent<string> optionUpdated;

    static const string PORT;
    static const string LOG_LEVEL;
  private:
    map<string, ConfigurationOption> _options;
    Logger logger;
  };

  //Configuration inline section
  inline map<string, ConfigurationOption>::const_iterator
  Configuration::begin() const
  {
    return _options.begin();
  }

  inline map<string, ConfigurationOption>::const_iterator
  Configuration::end() const
  {
    return _options.end();
  }
  //Configuration end of inline section
} /* namespace Thrower */
#endif /* CONFIGURATION_H_ */
