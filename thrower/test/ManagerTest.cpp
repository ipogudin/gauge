/*
 * test.cpp
 *
 *  Created on: May 10, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>

#include <Manager.h>
#include <Configuration.h>

#include <protocol.pb.h>

using namespace std;

using testing::ReturnRef;
using testing::NiceMock;

using Poco::Net::SocketAddress;
using Poco::Net::StreamSocket;
using Poco::Net::SocketStream;

using thrower::Manager;
using thrower::Configuration;

class MockConfiguration: public Configuration
{
  public:
    MOCK_METHOD1(getValue, const string& (const string& name));
};

TEST(ManagerTest, RunningManagementSocket)
{
  NiceMock<MockConfiguration> mockConf;
  const string port = "10000";

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

