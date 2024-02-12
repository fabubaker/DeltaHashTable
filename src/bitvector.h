#pragma once

#include <cstdint>
#include "entries.h"

/*
 * Bitvector positions go from left to right. Eg:
 * bits: 1 1 0 0 1
 *      <--------->
 * idx:  0 1 2 3 4
*/

typedef uint32_t position_t;
typedef uint32_t count_t;

#define popcount __builtin_popcountll

struct BitVector {
  uint64_t words[BUCKET_SIZE / 64] = { 0 };

  /* Returns the number of occurrences upto 'end' (not inclusive) */
  count_t rank_1(position_t start, position_t end);
  count_t rank_0(position_t start, position_t end);

  /* Returns the position of the i-th occurrence (not inclusive) */
  position_t select_1(position_t start, count_t i);
  position_t select_0(position_t start, count_t i);

  count_t parse_unary(position_t start);

  /*
   * Returns position immediately after indices field
   */
  position_t skip_indices_field(position_t start, count_t num_nodes);
};
