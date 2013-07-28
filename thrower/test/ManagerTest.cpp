/*
 * test.cpp
 *
 *  Created on: May 10, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <iostream>
#include <string>

#include <unistd.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>

#include <Manager.h>
#include <Configuration.h>

using testing::ReturnRef;
using testing::NiceMock;

using Poco::Net::SocketAddress;
using Poco::Net::StreamSocket;

using Thrower::Manager;
using Thrower::Configuration;

class MockConfiguration: public Configuration
{
  public:
    MOCK_METHOD1(getValue, const std::string& (const std::string& name));
};

TEST(ManagerTest, RunningManagementSocket)
{
  NiceMock<MockConfiguration> mockConf;
  const std::string port = "10000";

  ON_CALL(mockConf, getValue(Configuration::PORT))
    .WillByDefault(ReturnRef(port));

  Manager manager;
  manager.initialize(mockConf);
  manager.start();

  usleep(200000);

  size_t pos;
  ASSERT_NO_THROW({
    SocketAddress sa("localhost", stoi(port, &pos, 10));
    StreamSocket ss(sa);
  });
}
