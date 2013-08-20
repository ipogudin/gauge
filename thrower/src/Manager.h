/*
 * Manager.h
 *
 *  Created on: Jul 14, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include <Poco/SharedPtr.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/TCPServer.h>
#include <Poco/Net/TCPServerConnection.h>
#include <Poco/Net/TCPServerConnectionFactory.h>

#include "Configuration.h"
#include "Logger.h"

using Poco::SharedPtr;
using Poco::Net::ServerSocket;
using Poco::Net::StreamSocket;
using Poco::Net::TCPServer;
using Poco::Net::TCPServerConnection;
using Poco::Net::TCPServerConnectionFactory;

namespace thrower
{
  class ManagerTCPServerConnectionFactory;

  /*
   * This class contains essential logic
   * to interact with the conductor (central remote controller) and
   * to manage thrower's internals.
   */
  class Manager
  {
  public:
    Manager();
    virtual
    ~Manager();
    void initialize(Configuration& conf);
    void start();
    void stop();
  private:
    Logger _logger;
    Configuration* _conf;
    SharedPtr<ServerSocket> _socket;
    SharedPtr<TCPServer> _server;
    SharedPtr<ManagerTCPServerConnectionFactory> _connectionFactory;
  };

  class ManagerTCPServerConnection: public TCPServerConnection
  {
  public:
    ManagerTCPServerConnection(const Manager& manager, const StreamSocket& socket);
    void run();
  private:
    Manager _manager;
  };

  class ManagerTCPServerConnectionFactory: public TCPServerConnectionFactory
  {
  public:
    ManagerTCPServerConnectionFactory(const Manager& manager);
    TCPServerConnection* createConnection(const StreamSocket& socket);
  private:
    Manager _manager;
  };
} /* namespace Thrower */
#endif /* MANAGER_H_ */
