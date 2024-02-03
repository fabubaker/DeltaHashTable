#pragma once

#include <vector>
#include <cstdint>

/*
 * IMPORTANT: bit at index N-1 is left-most and bit at index 0 is right-most.
 */
template<uint32_t numBits> struct BitVector {
public:
  /*
   * Returns bits from a given range.
   * Note that 'end' is not inclusive.
   */
  std::vector<uint8_t> get_bits_in_range(uint32_t start, uint32_t end);

  /* Returns size in bytes */
  constexpr static uint32_t size() {
    return bits_to_bytes(numBits);
  }

private:
  // This fancy expression is simply a fast ceiling division of x / 8.
  constexpr static uint32_t bits_to_bytes(uint32_t x)  {
    return x / 8 + (x % 8 != 0);
  }

  uint8_t data[size()];
};
