/*
 * MessageTransportTest.cpp
 *
 *  Created on: Aug 20, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <MessageTransport.h>

using Poco::SharedPtr;

using thrower::protocol::Message;
using thrower::protocol::MessageType;
using thrower::protocol::StatusType;
using thrower::MessageTransport;

/*
 * Mock class to simulate the StreamSocket behavior for testing purposes
 */
class MockStreamSocket
{
public:
  /*
   * Configure MockStreamSocket to simulate behavior during reading/writing.
   * The buffer is randomly divided into readingParts number of parts.
   * writingParts can be defined to simulate random partial writing.
   */
  MockStreamSocket(
      const void* buffer,
      int readingBufferLength,
      int readingParts,
      int writingParts):
        _buffer((char*)buffer),
        _bufferLength(readingBufferLength),
        _readingParts(readingParts),
        _writingParts(writingParts)
  {

  }

  int sendBytes(const void* buffer, int length, int flags)
  {
    _writingParts--;

    int maxPartSize =
        (_bufferLength > length)?length:_bufferLength;

    int r = rand();
    unsigned int partSize = (_writingParts < 1)?
        maxPartSize:(r % maxPartSize);

    memcpy(_buffer, (void *)buffer, partSize);

    _buffer += partSize;
    _bufferLength -= partSize;

    return partSize;
  }

  int receiveBytes(const void* buffer, int length, int flags)
  {
    _readingParts--;

    int maxPartSize =
        (_bufferLength > length)?length:_bufferLength;

    int r = rand();
    unsigned int partSize = (_readingParts < 1)?
        maxPartSize:(r % maxPartSize);

    if (partSize < 1) partSize = 1;

    memcpy((void *)buffer, _buffer, partSize);

    _buffer += partSize;
    _bufferLength -= partSize;

    return partSize;
  }

private:
  char* _buffer;
  int _bufferLength;
  int _readingParts;
  int _writingParts;
};

#define PREPARE_BUF(buf, size, message) \
  unsigned long messageSize = message.ByteSize();\
  unsigned long size = messageSize + 3;\
  Buffer<char> buf(size);\
  buf.begin()[0] = (char)((unsigned long)(messageSize & 0x0000000000ff0000) >> 16);\
  buf.begin()[1] = (char)((unsigned long)(messageSize & 0x000000000000ff00) >> 8);\
  buf.begin()[2] = (char)(messageSize & 0x00000000000000ff);\
  message.SerializeToArray(buf.begin() + 3, size);

TEST(MessageTransportTest, ReadingMessage)
{
  Message originalMessage;
  originalMessage.set_status(StatusType::OK);
  originalMessage.set_type(MessageType::RESPONSE);
  PREPARE_BUF(buf, size, originalMessage)

  MockStreamSocket mockSocket(buf.begin(), size, 0, 0);
  MessageTransport<MockStreamSocket> messageTransport(mockSocket);

  SharedPtr<Message> receivedMessage = messageTransport.read();
  ASSERT_FALSE(receivedMessage.isNull());
  ASSERT_EQ(MessageType::RESPONSE, receivedMessage->type());
  ASSERT_EQ(StatusType::OK, receivedMessage->status());
}

TEST(MessageTransportTest, ReadingMessageByParts)
{
  Message originalMessage;
  originalMessage.set_status(StatusType::OK);
  originalMessage.set_type(MessageType::RESPONSE);
  PREPARE_BUF(buf, size, originalMessage)

  MockStreamSocket mockSocket(buf.begin(), size, 3, 0);
  MessageTransport<MockStreamSocket> messageTransport(mockSocket);

  SharedPtr<Message> receivedMessage = messageTransport.read();
  ASSERT_FALSE(receivedMessage.isNull());
  ASSERT_EQ(MessageType::RESPONSE, receivedMessage->type());
  ASSERT_EQ(StatusType::OK, receivedMessage->status());
}

TEST(MessageTransportTest, WritingMessage)
{
  Message originalMessage;
  originalMessage.set_status(StatusType::OK);
  originalMessage.set_type(MessageType::RESPONSE);
  PREPARE_BUF(expectedResult, size, originalMessage)

  Buffer<char> actualResult(size);
  std::fill_n(actualResult.begin(), size, 0);

  MockStreamSocket mockSocket(actualResult.begin(), size, 0, 0);
  MessageTransport<MockStreamSocket> messageTransport(mockSocket);

  messageTransport.write(originalMessage);
  for (int i = 0; i < size; i++)
  {
    ASSERT_EQ(expectedResult[i], actualResult[i]);
  }
}

TEST(MessageTransportTest, WritingMessageByParts)
{
  Message originalMessage;
  originalMessage.set_status(StatusType::OK);
  originalMessage.set_type(MessageType::RESPONSE);
  PREPARE_BUF(expectedResult, size, originalMessage)

  Buffer<char> actualResult(size);
  std::fill_n(actualResult.begin(), size, 0);

  MockStreamSocket mockSocket(actualResult.begin(), size, 0, 3);
  MessageTransport<MockStreamSocket> messageTransport(mockSocket);

  messageTransport.write(originalMessage);
  for (int i = 0; i < size; i++)
  {
    ASSERT_EQ(expectedResult[i], actualResult[i]);
  }
}
