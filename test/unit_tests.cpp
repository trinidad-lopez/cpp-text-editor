#include "gtest/gtest.h"
#include "mock.h"

TEST(MockTest, alwaysPass) {
    mock_fn();
    EXPECT_EQ(1,1);
}