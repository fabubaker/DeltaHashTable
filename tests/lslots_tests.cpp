#include <gtest/gtest.h>
#include "entries.h"
#include "lslots.h"

TEST(test_get_lslot_offset, lslot_in_paper) {
  GTEST_SKIP();

  // Left shift the lslot bits all the way to the left
  // NOTE: There's no interleaving here like its described in the paper
  uint64_t lslot_in_paper = 0b111110'110100'00011110 << (64 - 20);

  // Left shift the fp bits all the way to the left
  __uint128_t fingerprint_in_paper = 0b101101 << (128 - 6);

  Lslots lslots;
  lslots.bits.words[0] = lslot_in_paper;

  EXPECT_EQ(lslots.get_lslot_offset(fingerprint_in_paper, 0), 4);
}
