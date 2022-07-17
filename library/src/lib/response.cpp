#include <cstring>

#include <Poco/ByteOrder.h>

#include "lib/response.hpp"

namespace lib {
Response::Response(std::uint32_t result, std::string_view message)
  : m_header{
    Poco::ByteOrder::toNetwork(result),
    Poco::ByteOrder::toNetwork(static_cast<std::uint64_t>(message.size()))},
    m_message{std::make_unique<char[]>(message.size())}
{
  std::memcpy(m_message.get(), message.data(), message.size());
}

const void* Response::header() const
{
  return &m_header;
}

const void* Response::message() const
{
  return m_message.get();
}

std::size_t Response::messageSize() const
{
  return static_cast<std::size_t>(
    Poco::ByteOrder::fromNetwork(m_header.messageLength));
}
} // namespace lib
