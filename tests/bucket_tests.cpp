#include <gtest/gtest.h>
#include "bucket.h"

TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "worldssz");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
