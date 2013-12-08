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
   * readingBuffer is randomly divided into readingParts number of parts.
   * writingParts can be defined to simulate random partial writing.
   */
  MockStreamSocket(
      const void* readingBuffer,
      int readingBufferLength,
      int readingParts,
      int writingParts):
        _readingBuffer((char*)readingBuffer),
        _readingBufferLength(readingBufferLength),
        _readingParts(readingParts),
        _writingParts(writingParts)
  {

  }

  int sendBytes(const void* buffer, int length, int flags)
  {
    return 0;
  }

  int receiveBytes(const void* buffer, int length, int flags)
  {
    _readingParts--;

    int maxPartSize =
        (_readingBufferLength > length)?length:_readingBufferLength;

    int r = rand();
    unsigned int partSize = (_readingParts < 1 || length < 100)?
        maxPartSize:(r % maxPartSize);

    memcpy((void *)buffer, _readingBuffer, partSize);

    _readingBuffer += partSize;
    _readingBufferLength -= partSize;

    return partSize;
  }

private:
  char* _readingBuffer;
  int _readingBufferLength;
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

  MockStreamSocket mockSocket(buf.begin(), size, 0, 0);
  MessageTransport<MockStreamSocket> messageTransport(mockSocket);

  SharedPtr<Message> receivedMessage = messageTransport.read();
  ASSERT_FALSE(receivedMessage.isNull());
  ASSERT_EQ(MessageType::RESPONSE, receivedMessage->type());
  ASSERT_EQ(StatusType::OK, receivedMessage->status());
}
