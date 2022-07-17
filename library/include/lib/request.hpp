#pragma once
#include <cstddef>

#include <memory>
#include <string_view>

#include "lib/request_header.hpp"

namespace lib {
class Request {
public:
  static constexpr std::size_t headerSize()
  {
    return sizeof(RequestHeader);
  }

  Request(std::uint16_t number1, std::uint16_t number2, std::string_view name);

  const void* header() const;

  const void* name() const;

  std::size_t nameSize() const;

private:
  RequestHeader           m_header;
  std::unique_ptr<char[]> m_name;
};
} // namespace lib
