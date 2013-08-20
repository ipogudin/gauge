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
  usleep(200000);
  return manager;
};

SharedPtr<Message> executeRequest(Configuration& conf, Message& request)
{
  SharedPtr<Message> response = new Message();
  size_t pos;
  SocketAddress address("localhost",
      stoi(conf.getValue(Configuration::PORT), &pos, 10));
  StreamSocket socket(address);
  Timespan ts(1l, 0l);
  socket.setReceiveTimeout(ts);
  socket.setSendTimeout(ts);
  SocketStream stream(socket);
  request.SerializeToOstream(&stream);
  stream.flush();
  response->ParseFromIstream(&stream);
  return response;
};

TEST(ManagerTest, HelloManagementInterface)
{
  NiceMock<MockConfiguration> mockConf;
  const string port = "10000";

  ON_CALL(mockConf, getValue(Configuration::PORT))
    .WillByDefault(ReturnRef(port));

  SharedPtr<Manager> manager = startManager(mockConf);

  Message request;
  request.set_type(MessageType::HELLO);

  SharedPtr<Message> response;

  ASSERT_NO_THROW({
    response = executeRequest(mockConf, request);
  });
  EXPECT_FALSE(response.isNull());
  EXPECT_EQ(StatusType::OK, response->status());
}

TEST(ManagerTest, TwoConnectionsToManagementInterface)
{
  NiceMock<MockConfiguration> mockConf;
  const string port = "10000";

  ON_CALL(mockConf, getValue(Configuration::PORT))
    .WillByDefault(ReturnRef(port));

  SharedPtr<Manager> manager = startManager(mockConf);

  Message requestFrom1Client;
  requestFrom1Client.set_type(MessageType::HELLO);

  SharedPtr<Message> responseFor1Client;

  ASSERT_NO_THROW({
    responseFor1Client = executeRequest(mockConf, requestFrom1Client);
  });
  EXPECT_FALSE(responseFor1Client.isNull());
  EXPECT_EQ(StatusType::OK, responseFor1Client->status());

  Message requestFrom2Client;
  requestFrom2Client.set_type(MessageType::HELLO);

  SharedPtr<Message> responseFor2Client;

  ASSERT_NO_THROW({
    responseFor2Client = executeRequest(mockConf, requestFrom2Client);
  });
  EXPECT_FALSE(responseFor2Client.isNull());
  EXPECT_EQ(StatusType::ERROR, responseFor2Client->status());
}
