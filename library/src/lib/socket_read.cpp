#include <Poco/Net/StreamSocket.h>

#include "lib/socket_read.hpp"

namespace lib {
ReadStatus socketRead(Poco::Net::StreamSocket& socket, void* buffer, int length)
{
  const int statusCode{socket.receiveBytes(buffer, length, MSG_WAITALL)};

  if (statusCode == 0) {
    return ReadStatus::GracefulShutdown;
  }

  if (statusCode == length) {
    return ReadStatus::Success;
  }

  return ReadStatus::Failure;
}
} // namespace lib
