#pragma once

#include <cstdint>

/*
 * Bitvector positions go from left to right. Eg:
 * bits: 1 1 0 0 1
 *      <--------->
 * idx:  0 1 2 3 4
*/

typedef uint32_t position_t;
typedef uint32_t count_t;

#define popcount __builtin_popcount

template <uint32_t NBITS>
struct BitVector {
  uint64_t words[NBITS / 64];

  /* Returns the number of occurrences upto 'end' (not inclusive) */
  count_t rank_1(position_t start, position_t end);
  count_t rank_0(position_t start, position_t end);

  /* Returns the position of the i-th occurrence (not inclusive) */
  position_t select_1(position_t start, count_t i);
  position_t select_0(position_t start, count_t i);

  uint32_t parse_unary(position_t start);
};
