/*
 * test.cpp
 *
 *  Created on: May 10, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <iostream>

#include <gtest/gtest.h>

#include <Configuration.h>
#include <Exception.h>

using namespace std;

using thrower::Configuration;
using thrower::ConfigurationOption;

TEST(ConfigurationTest, IterationThroughPredefinedConfigurationOptions)
{
  string expected = "loglevel port ";
  string actual;
  Configuration conf;

  for (auto& pair : conf)
  {
    actual.append(pair.second.getName());
    actual.append(" ");
  }
  EXPECT_EQ(expected, actual);
}

TEST(ConfigurationTest, GettingNonExistentKey)
{
  Configuration conf;

  EXPECT_THROW({
    //Getting non-existent key raises throws a logic excetion
    const string& value = conf.getValue("NotExistingKey");
  }, Poco::LogicException);
}
