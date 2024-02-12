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
count_t BitVector::parse_unary(position_t start) {
  count_t count = 0;
  position_t start_index = start / 64;
  position_t start_offset = start % 64;
  uint64_t word = words[start_index];

  // Remove bits before 'start_offset'
  word = word << start_offset;

  // Flip bits
  word = ~word;

  // Count leading zeroes
  count = __builtin_clzll(word);

  /* Edge case: The unary string can extend along multiple words */
  if (count == (64 - start_offset)) {
    /* Continue iterating through words until fully parsed */
    position_t new_start = start + (64 - start_offset);
    count += parse_unary(new_start);
  }

  return count;
};

position_t BitVector::skip_indices_field(position_t start, count_t num_nodes) {
  position_t start_index = start / 64;
  position_t cur_index = start_index;
  position_t start_offset = start % 64;
  position_t cur_offset = start_offset;
  uint64_t word = words[cur_index];

  // Remove bits before 'start_offset'
  word = word << start_offset;

  // Flip bits
  word = ~word;

  count_t lz;
  count_t len;

  for (count_t cur_node = 0; cur_node < num_nodes; cur_node++) {
    // Parse a single unary-encoded index value
    lz = __builtin_clzll(word);
    len = lz + 1; // Length of unary value is one + the number of leading zeroes

    /* Edge case: We need to parse the next word */
    if (cur_offset + len >= 64) {
      /* The current value extends over to the next word */
      if (cur_offset + len == 65) {
        // We're still going to be parsing cur_node in the next iteration
        cur_node--;
      }

      cur_index++;
      cur_offset = 0;
      word = words[cur_index];
      word = ~word;

      // assert(cur_index < bitvector.size());
    } else {
      word = word << len;
      cur_offset += len;
    }
  }

  return cur_index * 64 + cur_offset;
}
