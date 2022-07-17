#pragma once
#include <cstddef>

#include <memory>
#include <string_view>

#include "lib/response_header.hpp"

namespace lib {
class Response {
public:
  static constexpr std::size_t headerSize()
  {
    return sizeof(ResponseHeader);
  }

  Response(std::uint32_t result, std::string_view message);

  const void* header() const;

  const void* message() const;

  std::size_t messageSize() const;

private:
  ResponseHeader          m_header;
  std::unique_ptr<char[]> m_message;
};
} // namespace lib
