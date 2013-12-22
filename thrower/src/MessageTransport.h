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
    unsigned int bufferSize = 3;
    unsigned int readSize = 0;
    Buffer<char> headerBuffer(bufferSize);

    while(readSize < bufferSize)
    {
      readSize += _socket.receiveBytes(
          headerBuffer.begin() + readSize, bufferSize - readSize, 0);
    }

    unsigned long messageSize = 0;
    messageSize |= ((unsigned long)headerBuffer.begin()[0]) << 16;
    messageSize |= ((unsigned long)headerBuffer.begin()[1]) << 8;
    messageSize |= ((unsigned long)headerBuffer.begin()[2]);

    Buffer<char> messageBuffer(messageSize);
    readSize = 0;
    //copy of bytes which have been already read

    while(readSize < messageSize)
    {
      readSize += _socket.receiveBytes(
          messageBuffer.begin() + readSize, messageSize - readSize, 0);
    }

    SharedPtr<Message> message(new Message);
    if (!message->ParseFromArray(messageBuffer.begin(), messageSize))
    {
        throw Poco::RuntimeException("that's pity");
    }
    return message;
  }

  template <class TSocket>
  void MessageTransport<TSocket>::write(Message& message)
  {
    unsigned long messageSize = message.ByteSize();
    unsigned long size = messageSize + 3;
    Buffer<char> buffer(size);
    buffer.begin()[0] = (char)((unsigned long)(messageSize & 0x0000000000ff0000) >> 16);
    buffer.begin()[1] = (char)((unsigned long)(messageSize & 0x000000000000ff00) >> 8);
    buffer.begin()[2] = (char)(messageSize & 0x00000000000000ff);
    message.SerializeToArray(buffer.begin() + 3, size);

    int writtenSize = 0;
    while(writtenSize < size)
    {
      writtenSize += _socket.sendBytes(
          buffer.begin() + writtenSize, size - writtenSize, 0);
    }
  }
} /* namespace Thrower */
#endif /* MESSAGEREADER_H_ */