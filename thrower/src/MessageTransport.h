/*
 * MessageTransport.h
 *
 *  Created on: Aug 20, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef MESSAGEREADER_H_
#define MESSAGETRANSPORT_H_

#include <Poco/SharedPtr.h>
#include <Poco/Buffer.h>

#include <protocol.pb.h>
#include <Exception.h>

using Poco::SharedPtr;
using Poco::Buffer;

using thrower::protocol::MessageHeader;
using thrower::protocol::Message;
using thrower::protocol::MessageType;
using thrower::protocol::StatusType;

namespace thrower
{
  /*
   * This class is a helper to read messages from SocketStream.
   */
  template <class TSocket>
  class MessageTransport
  {
  public:
    MessageTransport(TSocket& socket);
    virtual
    ~MessageTransport();
    SharedPtr<Message> read();
    void write(Message& message);
  private:
    TSocket _socket;
  };

  //Implementation
  template <class TSocket>
  MessageTransport<TSocket>::MessageTransport(TSocket& socket):_socket(socket)
  {

  }

  template <class TSocket>
  MessageTransport<TSocket>::~MessageTransport()
  {

  }

  template <class TSocket>
  SharedPtr<Message> MessageTransport<TSocket>::read()
  {
    MessageHeader header;
    unsigned int bufferSize = 64;
    unsigned int readSize = 0;
    Buffer<char> headerBuffer(bufferSize);
    bool parsed = false;

    while(readSize < bufferSize)
    {
      readSize += _socket.receiveBytes(
          headerBuffer.begin() + readSize, bufferSize - readSize, 0);
      std::cout << readSize << std::endl << std::endl << std::endl;
      if (header.ParseFromArray(headerBuffer.begin(), readSize))
      {
        parsed = true;
        break;
      }
    }

    if (!parsed)
    {
      throw Poco::RuntimeException("that's pity");
    }

    unsigned int messageSize = 0;
    messageSize = header.size();
    readSize = 0;

    Buffer<char> messageBuffer(messageSize);
    //copy already read bytes

    while(readSize < messageSize)
    {
      readSize += _socket.receiveBytes(
          messageBuffer.begin() + readSize, messageSize - readSize, 0);
    }

    SharedPtr<Message> message;
    if (!message->ParseFromArray(messageBuffer.begin(), messageSize))
    {
        throw Poco::RuntimeException("that's pity");
    }
    return message;
  }

  template <class TSocket>
  void MessageTransport<TSocket>::write(Message& message)
  {
  }
} /* namespace Thrower */
#endif /* MESSAGEREADER_H_ */
