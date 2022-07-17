#pragma once

namespace Poco::Net {
class StreamSocket;
} // namespace Poco::Net

namespace lib {
enum class ReadStatus { Failure, Success, GracefulShutdown };

ReadStatus socketRead(Poco::Net::StreamSocket& socket, void* buffer, int length);
} // namespace lib
