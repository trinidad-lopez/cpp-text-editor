#include <src/gtest_main.cc>
#include "mock.h"

TEST(Test, always_pass) {
    mock_fn();
    EXPECT_EQ(1,1);
}