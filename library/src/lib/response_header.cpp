#include <Poco/ByteOrder.h>

#include "lib/response_header.hpp"

namespace lib {
ResponseHeader ResponseHeader::asHostByteOrder() const
{
  ResponseHeader returnValue{*this};
  returnValue.result = Poco::ByteOrder::fromNetwork(returnValue.result);
  returnValue.messageLength
    = Poco::ByteOrder::fromNetwork(returnValue.messageLength);
  return returnValue;
}
} // namespace lib
