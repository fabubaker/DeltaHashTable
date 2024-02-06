#include <gtest/gtest.h>
#include "entries.h"

TEST(test_get_lslot_id, only_lslot_bits) {
  __uint128_t hkey_128 = 0x00AF000000000000;

  hkey hkey;
  hkey.hkey = (hkey_128 << 64) + 0;

  uint32_t lslot_id = hkey.get_lslot_id();
  EXPECT_EQ(lslot_id, 175); // 0xAF = 175
}

TEST(test_get_lslot_id, bucket_and_lslot_bits) {
  __uint128_t hkey_128 = 0xFBD1000000000000;

  hkey hkey;
  hkey.hkey = (hkey_128 << 64) + 0;

  uint32_t lslot_id = hkey.get_lslot_id();
  EXPECT_EQ(lslot_id, 209); // 0xD1 = 209
}

TEST(test_get_lslot_id, bucket_and_lslot_and_fp_bits) {
  __uint128_t hkey_128 = 0xDEADBEEF1DAB0000;

  hkey hkey;
  hkey.hkey = (hkey_128 << 64) + 0;

  uint32_t lslot_id = hkey.get_lslot_id();
  EXPECT_EQ(lslot_id, 173); // 0xAD = 173
}
