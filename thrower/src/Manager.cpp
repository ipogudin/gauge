/*
 * Manager.cpp
 *
 *  Created on: Jul 14, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <iostream>
#include <string>

#include <Poco/Timespan.h>
#include <Poco/Net/SocketStream.h>

#include "Exception.h"
#include "Manager.h"
#include "MessageTransport.h"

#include <protocol.pb.h>

using namespace std;

using Poco::Exception;
using Poco::Timespan;
using Poco::Net::SocketStream;

using thrower::protocol::Message;
using thrower::protocol::MessageType;
using thrower::protocol::StatusType;

namespace thrower
{
  //Manager

  Manager::Manager():_logger(Logger::logger("Manager")),_configuration(NULL)
    ,sessionMutex(new Mutex)
  {

  }

  Manager::~Manager()
  {

  }

  void Manager::initialize(Configuration& conf)
  {
    _configuration = &conf;
  }

  void Manager::start()
  {
    if (!_server.isNull())
    {
      throw IncorrectStateException("Manager is already started");
    }

    try
    {
      size_t pos;
      int port = stoi(_configuration->getValue(Configuration::PORT));
      _socket = new ServerSocket(port);
      _connectionFactory = new ManagerTCPServerConnectionFactory(*this);
      _server = new TCPServer(_connectionFactory, *_socket);
      _server->start();
    }
    catch (Exception& e)
    {
      _logger.fatal(e.displayText());
    }
  }

  void Manager::stop()
  {

  }

  Configuration* Manager::configuration()
  {
    return _configuration;
  }

  //ManagerTCPServerConnection
  ManagerTCPServerConnection::ManagerTCPServerConnection(const Manager& manager,
      const StreamSocket& socket): TCPServerConnection(socket),_manager((Manager*)&manager)
  {
    const string stimeout = _manager->configuration()->getValue(Configuration::PROTOCOL_TIMEOUT);
    size_t pos;
    const long timeout = stol(stimeout, &pos, 10);
    Timespan ts(0l, timeout * 1000);
    ((StreamSocket)socket).setReceiveTimeout(ts);
    ((StreamSocket)socket).setSendTimeout(ts);
    ((StreamSocket)socket).setBlocking(true);
  }

  void
  ManagerTCPServerConnection::run()
  {
    MessageTransport<StreamSocket> transport(socket());

    SharedPtr<Message> message = transport.read();

    switch(message->type()) {
    case MessageType::PING:
    case MessageType::HELLO:
      _manager->sessionMutex->lock();
      try
      {
        Message response;
        response.set_type(MessageType::RESPONSE);
        if (_manager->activeSession == nullptr)
        {
          response.set_status(StatusType::OK);
          _manager->activeSession = &socket();
        }
        else {
          response.set_status(StatusType::ERROR);
        }
        transport.write(response);
      }
      catch (Exception& e) {

      }
      _manager->sessionMutex->unlock();
      break;
    }
  }

  //ManagerTCPServerConnectionFactory
  ManagerTCPServerConnectionFactory::ManagerTCPServerConnectionFactory(
      const Manager& manager):_manager((Manager*)&manager)
  {
  }

  TCPServerConnection*
  ManagerTCPServerConnectionFactory::createConnection(const StreamSocket& socket)
  {
    return new ManagerTCPServerConnection(*_manager, socket);
  }
} /* namespace Thrower */
