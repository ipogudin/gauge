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
      const StreamSocket& socket): TCPServerConnection(socket),_manager(manager)
  {
    const string stimeout = _manager.configuration()->getValue(Configuration::PROTOCOL_TIMEOUT);
    size_t pos;
    const long timeout = stol(stimeout, &pos, 10);
    Timespan ts(0l, timeout * 1000);
    ((StreamSocket)socket).setBlocking(false);
  }

  void
  ManagerTCPServerConnection::run()
  {

  }

  //ManagerTCPServerConnectionFactory
  ManagerTCPServerConnectionFactory::ManagerTCPServerConnectionFactory(
      const Manager& manager):_manager(manager)
  {
  }

  TCPServerConnection*
  ManagerTCPServerConnectionFactory::createConnection(const StreamSocket& socket)
  {
    return new ManagerTCPServerConnection(_manager, socket);
  }
} /* namespace Thrower */
