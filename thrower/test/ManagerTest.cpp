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

#include <Poco/Timespan.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>

#include <Manager.h>
#include <Configuration.h>
#include <MessageTransport.h>

#include <protocol.pb.h>

using namespace std;

using testing::ReturnRef;
using testing::NiceMock;

using Poco::Timespan;
using Poco::Net::SocketAddress;
using Poco::Net::StreamSocket;
using Poco::Net::SocketStream;

using thrower::Manager;
using thrower::Configuration;
using thrower::MessageTransport;

using thrower::protocol::Message;
using thrower::protocol::MessageType;
using thrower::protocol::StatusType;

class MockConfiguration: public Configuration
{
  public:
    MOCK_METHOD1(getValue, const string& (const string& name));
};

SharedPtr<Manager> startManager(Configuration& conf)
{
  SharedPtr<Manager> manager = new Manager();
  manager->initialize(conf);
  manager->start();
  usleep(200000l);
  return manager;
};

SharedPtr<Message> executeRequest(Configuration& conf, Message& request, long writeTimeout)
{
  size_t pos;
  SocketAddress address("localhost",
      stoi(conf.getValue(Configuration::PORT), &pos, 10));
  StreamSocket socket(address);
  if (writeTimeout > 0) {
    Timespan ts(0l, writeTimeout);
    socket.setReceiveTimeout(ts);
    socket.setSendTimeout(ts);
    socket.setBlocking(false);
  }

  MessageTransport<StreamSocket> transport(socket);
  if (writeTimeout > 0) {
      usleep(writeTimeout * 1000l);
  }
  transport.write(request);
  return transport.read();
};

TEST(ManagerTest, HelloManagementInterface)
{
  NiceMock<MockConfiguration> mockConf;
  const string port = "10000";
  const string timeout = "900";

  ON_CALL(mockConf, getValue(Configuration::PORT))
    .WillByDefault(ReturnRef(port));
  ON_CALL(mockConf, getValue(Configuration::PROTOCOL_TIMEOUT))
        .WillByDefault(ReturnRef(timeout));

  SharedPtr<Manager> manager = startManager(mockConf);

  Message request;
  request.set_type(MessageType::HELLO);

  SharedPtr<Message> response;

  ASSERT_NO_THROW({
    response = executeRequest(mockConf, request, 0);
  });
  EXPECT_FALSE(response.isNull());
  EXPECT_EQ(StatusType::OK, response->status());
}

TEST(ManagerTest, TwoConnectionsToManagementInterface)
{
  NiceMock<MockConfiguration> mockConf;
  const string port = "10000";
  const string timeout = "1000";

  ON_CALL(mockConf, getValue(Configuration::PORT))
    .WillByDefault(ReturnRef(port));
  ON_CALL(mockConf, getValue(Configuration::PROTOCOL_TIMEOUT))
      .WillByDefault(ReturnRef(timeout));

  SharedPtr<Manager> manager = startManager(mockConf);

  Message requestFrom1Client;
  requestFrom1Client.set_type(MessageType::HELLO);

  SharedPtr<Message> responseFor1stClient;

  ASSERT_NO_THROW({
    responseFor1stClient = executeRequest(mockConf, requestFrom1Client, 0);
  });
  EXPECT_FALSE(responseFor1stClient.isNull());
  EXPECT_EQ(StatusType::OK, responseFor1stClient->status());

  Message requestFrom2ndClient;
  requestFrom2ndClient.set_type(MessageType::HELLO);

  SharedPtr<Message> responseFor2Client;

  ASSERT_NO_THROW({
    responseFor2Client = executeRequest(mockConf, requestFrom2ndClient, 0);
  });
  EXPECT_FALSE(responseFor2Client.isNull());
  EXPECT_EQ(StatusType::ERROR, responseFor2Client->status());
}

TEST(ManagerTest, HungInitialConnection)
{
  NiceMock<MockConfiguration> mockConf;
  const string port = "10000";
  const string timeout = "50";

  ON_CALL(mockConf, getValue(Configuration::PORT))
    .WillByDefault(ReturnRef(port));
  ON_CALL(mockConf, getValue(Configuration::PROTOCOL_TIMEOUT))
        .WillByDefault(ReturnRef(timeout));

  SharedPtr<Manager> manager = startManager(mockConf);

  Message request;
  request.set_type(MessageType::HELLO);

  SharedPtr<Message> response;

  ASSERT_ANY_THROW({
    response = executeRequest(mockConf, request, 100l);
  });
  EXPECT_TRUE(response.isNull());
}
