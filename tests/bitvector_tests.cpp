#include <gtest/gtest.h>
#include "entries.h"
#include "bitvector.h"
#include <iostream>

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

TEST(test_parse_unary, one_word) {
  BitVector bits;
  bits.words[0] = 0x2;
  position_t start = 62;

  EXPECT_EQ(bits.parse_unary(start), 1);

  bits.words[0] = 0xFE;
  start = 56;

  EXPECT_EQ(bits.parse_unary(start), 7);
}

TEST(test_parse_unary, two_words) {
  BitVector bits;
  bits.words[0] = 0xF;
  bits.words[1] = (uint64_t) 0x3 << 62;
  position_t start = 60;

  EXPECT_EQ(bits.parse_unary(start), 6);

  bits.words[0] = 0xF;
  bits.words[1] = (uint64_t) 0xFF << 56;
  start = 60;

  EXPECT_EQ(bits.parse_unary(start), 12);
}

TEST(test_skip_indices_field, one_word) {
  BitVector bits;
  uint64_t lslot_in_paper = (uint64_t) 0b111110'110100'00011110 << (64 - 20);

  bits.words[0] = lslot_in_paper;

  position_t start = 12;
  position_t num_nodes = 4;

  EXPECT_EQ(bits.skip_indices_field(start, num_nodes), 20);
}

TEST(test_skip_indices_field, two_words) {
  BitVector bits;

  bits.words[0] = 0b000;
  bits.words[1] = (uint64_t) 0b11110 << (64 - 5);

  position_t start = 61;
  position_t num_nodes = 4;

  EXPECT_EQ(bits.skip_indices_field(start, num_nodes), 69);
}

TEST(test_skip_indices_field, unary_value_spans_two_words) {
  BitVector bits;

  bits.words[0] = 0b00011;
  bits.words[1] = (uint64_t) 0b110 << (64 - 3);

  position_t start = 59;
  position_t num_nodes = 4;

  EXPECT_EQ(bits.skip_indices_field(start, num_nodes), 67);
}
