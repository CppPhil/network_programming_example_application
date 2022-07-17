#pragma once
#include <cstdint>

#include <pl/packed.hpp>

namespace lib {
PL_PACKED_START
struct RequestHeader {
  std::uint16_t number1;
  std::uint16_t number2;
  std::uint64_t nameLength;

  RequestHeader asHostByteOrder() const;
};
PL_PACKED_END
} // namespace lib
