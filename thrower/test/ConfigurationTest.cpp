/*
 * test.cpp
 *
 *  Created on: May 10, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <iostream>

#include <gtest/gtest.h>

#include <Configuration.h>

using Thrower::Configuration;
using Thrower::ConfigurationOption;

TEST(ConfigurationTest, IterationThroughPredefinedConfigurationOptions)
{
  std::string expected = "loglevel port ";
  std::string actual;
  Configuration conf;

  for (auto& pair : conf)
  {
    actual.append(pair.second.getName());
    actual.append(" ");
  }
  EXPECT_EQ(expected, actual);
}

