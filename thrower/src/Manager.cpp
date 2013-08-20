/*
 * Manager.cpp
 *
 *  Created on: Jul 14, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <stdio.h>
#include <string>

#include "Exception.h"
#include "Manager.h"

#include <protocol.pb.h>

using namespace std;

using Poco::Exception;

using thrower::protocol::Message;
using thrower::protocol::MessageType;
using thrower::protocol::StatusType;

namespace thrower
{
  //Manager

  Manager::Manager():_logger(Logger::logger("Manager")),_conf(NULL)
  {

  }

  Manager::~Manager()
  {

  }

  void Manager::initialize(Configuration& conf)
  {
    _conf = &conf;
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
      int port = stoi(_conf->getValue(Configuration::PORT));
      _socket = new ServerSocket(port);
      _connectionFactory = new ManagerTCPServerConnectionFactory(*this);
      _server = new TCPServer(_connectionFactory, *_socket);
    }
    catch (Exception& e)
    {
      _logger.fatal(e.displayText());
    }
  }

  void Manager::stop()
  {

  }

  //ManagerTCPServerConnection
  ManagerTCPServerConnection::ManagerTCPServerConnection(const Manager& manager,
      const StreamSocket& socket): TCPServerConnection(socket),_manager(manager)
  {

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
