#include <cstring>

#include <Poco/ByteOrder.h>

#include "lib/request.hpp"

namespace lib {
Request::Request(std::uint16_t number1, std::uint16_t number2, std::string_view name)
  : m_header{
    Poco::ByteOrder::toNetwork(number1),
    Poco::ByteOrder::toNetwork(number2),
    Poco::ByteOrder::toNetwork(static_cast<std::uint64_t>(name.size()))
  }, 
  m_name{std::make_unique<char[]>(name.size())}
{
  std::memcpy(m_name.get(), name.data(), name.size());
}

const void* Request::header() const
{
  return &m_header;
}

const void* Request::name() const
{
  return m_name.get();
}

std::size_t Request::nameSize() const
{
  return static_cast<std::size_t>(
    Poco::ByteOrder::fromNetwork(m_header.nameLength));
}
} // namespace lib
