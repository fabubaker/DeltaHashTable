#include "bitvector.h"

template <uint32_t NBITS>
uint32_t BitVector<NBITS>::parse_unary(position_t start) {

};


template <uint32_t NBITS>
count_t BitVector<NBITS>::rank_1(position_t start, position_t end) {
  position_t cur = start;
  position_t start_index = start / 64;
  position_t start_offset = start % 64;
  position_t end_index = end / 64;
  position_t end_offset = end % 64;

  count_t count = 0;

  // Everything's in the same word
  if (start_index == end_index) {
    // Mask out the lower end
    uint64_t mask = (1 << (64 - end_offset)) - 1;
    mask = ~mask;
    uint64_t word = (words[start_index] & mask);

    // Get rid of the upper end
    word <<= start_offset;

    return popcount(word);
  }

  // We have to traverse multiple words
}
