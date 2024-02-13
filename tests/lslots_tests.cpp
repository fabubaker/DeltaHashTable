#include <gtest/gtest.h>
#include "entries.h"
#include "lslots.h"

TEST(test_skip_lslot, lslot_in_paper) {
  uint64_t lslot_in_paper = (uint64_t) 0b111110'110100'00011110 << (64 - 20);

  Lslots lslots;
  lslots.bits.words[0] = lslot_in_paper;

  EXPECT_EQ(lslots.skip_lslot(0), 20);
}

TEST(get_lslot_start, lslot_in_paper) {
  uint64_t lslot_in_paper = (uint64_t) 0b111110'110100'00011110;

  Lslots lslots;
  lslots.bits.words[0] = lslot_in_paper << (64 - 20); // lslot_id = 0
  lslots.bits.words[0] |= lslot_in_paper << (64 - 40); // lslot_id = 1
  lslots.bits.words[0] |= lslot_in_paper << (64 - 60); // lslot_id = 2

  // lslot_id = 3
  lslots.bits.words[0] |= 0b1111;
  lslots.bits.words[1] |= (uint64_t) 0b1011010000011110 << (64 - 16);

  EXPECT_EQ(lslots.get_lslot_start(0), 0);
  EXPECT_EQ(lslots.get_lslot_start(1), 20);
  EXPECT_EQ(lslots.get_lslot_start(2), 40);
  EXPECT_EQ(lslots.get_lslot_start(3), 60);
  EXPECT_EQ(lslots.get_lslot_start(4), 80);
}

TEST(test_get_lslot_offset, lslot_in_paper) {
  // Left shift the lslot bits all the way to the left
  // NOTE: There's no interleaving here like its described in the paper
  uint64_t lslot_in_paper = (uint64_t) 0b111110'110100'00011110 << (64 - 20);

  // Left shift the fp bits all the way to the left
  __uint128_t fingerprint_in_paper = (__uint128_t) 0b101101 << (128 - 6);

  Lslots lslots;
  lslots.bits.words[0] = lslot_in_paper;

  position_t start = 0;
  EXPECT_EQ(lslots.get_lslot_offset(fingerprint_in_paper, start), 4);
}
