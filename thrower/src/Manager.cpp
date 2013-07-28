/*
 * Manager.cpp
 *
 *  Created on: Jul 14, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <stdio.h>
#include <string>

#include <Poco/RunnableAdapter.h>
#include <Poco/Timespan.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>

#include "Exception.h"
#include "Manager.h"

using std::size_t;
using std::string;

using Poco::Exception;
using Poco::RunnableAdapter;
using Poco::Timespan;
using Poco::Net::ServerSocket;
using Poco::Net::StreamSocket;
using Poco::Net::SocketStream;

namespace Thrower
{

  Manager::Manager():_conf(NULL),_logger(Logger::logger("Manager"))
  {
    _thread.setName("Manager");
  }

  Manager::~Manager()
  {
    // TODO Auto-generated destructor stub
  }

  void Manager::initialize(Configuration& conf)
  {
    _conf = &conf;
  }

  void Manager::run()
  {
    try
    {
      size_t pos;
      int port = stoi(_conf->getValue(Configuration::PORT));
      ServerSocket server(port);
      server.setBlocking(false);
      //The main control loop manages the whole state of a thrower instance
      StreamSocket managerSocket;
      bool managerConnected = false;
      const Timespan pollTimeout(0l, 100000000l);

      while (1)
      {
        if (server.poll(pollTimeout, StreamSocket::SELECT_READ))
        {
          StreamSocket newManagerSocket = server.acceptConnection();
          if (managerConnected)
          {
            SocketStream newManagerStream(newManagerSocket);
            newManagerStream << "Manager already connected";
            newManagerStream.close();
          }
          else
          {
            managerSocket = newManagerSocket;
            managerConnected = true;
          }
        }

        if (managerSocket.poll(pollTimeout, StreamSocket::SELECT_READ))
        {

        }
      };
    }
    catch (Exception& e)
    {
      _logger.fatal(e.displayText());
    }
  }

  void Manager::start()
  {
    _thread.start(*this);
  }

  void Manager::stop()
  {

  }
} /* namespace Thrower */
