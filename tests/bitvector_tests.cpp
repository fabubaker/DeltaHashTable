#include <gtest/gtest.h>
#include "entries.h"
#include "bitvector.h"

TEST(test_rank_1, all_ones_in_one_word) {
  BitVector bits;
  bits.words[0] = -1;

  position_t start = 0;
  position_t end = 32;
  EXPECT_EQ(bits.rank_1(start, end), 32);

  start = 0;
  end = 64;
  EXPECT_EQ(bits.rank_1(start, end), 64);

  start = 32;
  end = 64;
  EXPECT_EQ(bits.rank_1(start, end), 32);

  start = 10;
  end = 50;
  EXPECT_EQ(bits.rank_1(start, end), 40);
}
