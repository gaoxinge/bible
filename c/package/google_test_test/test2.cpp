#include "gtest/gtest.h"

TEST(HelloTest, BasicAssertions1) {
    EXPECT_STRNE("world", "world");
    EXPECT_EQ(41, 7 * 6);
}
