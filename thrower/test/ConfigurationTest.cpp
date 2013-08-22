/*
 * test.cpp
 *
 *  Created on: May 10, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <iostream>
#include <set>

#include <gtest/gtest.h>

#include <Configuration.h>
#include <Exception.h>

using namespace std;

using thrower::Configuration;
using thrower::ConfigurationOption;

TEST(ConfigurationTest, IterationThroughPredefinedConfigurationOptions)
{
  set<string> expectedOptions;
  expectedOptions.insert(Configuration::PORT);
  expectedOptions.insert(Configuration::LOG_LEVEL);
  expectedOptions.insert(Configuration::PROTOCOL_TIMEOUT);

  Configuration conf;

  for (auto& pair : conf)
  {
    EXPECT_TRUE(
        expectedOptions.find(pair.second.getName()) != expectedOptions.end()
        );
  }
}

TEST(ConfigurationTest, GettingNonExistentKey)
{
  Configuration conf;

  EXPECT_THROW({
    //Getting non-existent key raises throws a logic excetion
    const string& value = conf.getValue("NotExistingKey");
  }, Poco::LogicException);
}
