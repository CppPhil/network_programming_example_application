#pragma once
#include <cstdint>

#include <pl/packed.hpp>

namespace lib {
PL_PACKED_START
struct ResponseHeader {
  std::uint32_t result;
  std::uint64_t messageLength;

  ResponseHeader asHostByteOrder() const;
};
PL_PACKED_END
} // namespace lib
