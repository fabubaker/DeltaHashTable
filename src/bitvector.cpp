#include <immintrin.h>
#include "bitvector.h"
#include <iostream>

count_t BitVector::rank_1(position_t start, position_t end) {
  count_t rank = 0;

  position_t start_index = start / 64;
  position_t start_offset = start % 64;
  position_t end_index = end / 64;
  position_t end_offset = end % 64;

  // We might have to traverse multiple words
  for (position_t cur_index = start_index; cur_index <= end_index; cur_index++) {
    uint64_t word = words[cur_index];

    if (cur_index == start_index) {
      // Remove bits before 'start_offset'
      word = word << start_offset >> start_offset;
    }

    if (cur_index == end_index) {
      // Edge case: if end_offset is zero, ignore word
      if (end_offset == 0) {
        word = 0;
      } else {
        // Remove bits after 'end_offset'
        word >>= (64 - end_offset);
      }
    }

    rank += popcount(word);
  }

  return rank;
}

/* Parse unary encoded bitstring located at 'start' */
uint32_t BitVector::parse_unary(position_t start) {
  count_t count = 0;

  position_t start_index = start / 64;
  position_t start_offset = start % 64;

  uint64_t word = words[start_index];

  // Remove bits before 'start_offset'
  word = word << start_offset;

  // Flip bits
  word = ~word;

  // Count leading zeroes
  count = __builtin_clzl(word);

  /* Edge case: The unary string can extend along multiple words */
  if (count == (64 - start_offset)) {
    /* Continue iterating through words until fully parsed */
    position_t new_start = start + (64 - start_offset);
    count += parse_unary(new_start);
  }

  return count;
};
