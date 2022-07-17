#include <Poco/ByteOrder.h>

#include "lib/request_header.hpp"

namespace lib {
RequestHeader RequestHeader::asHostByteOrder() const
{
  RequestHeader result{*this};
  result.number1    = Poco::ByteOrder::fromNetwork(result.number1);
  result.number2    = Poco::ByteOrder::fromNetwork(result.number2);
  result.nameLength = Poco::ByteOrder::fromNetwork(result.nameLength);
  return result;
}
} // namespace lib
