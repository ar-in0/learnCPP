#include <gtest/gtest.h>

int factorial(int n) {
    if (!n) return 1;
    if (n < 0) return 0; // not defined
    return n * factorial(n - 1);
}

TEST(FactorialTest, HandlesZeroInput) {
    EXPECT_EQ(factorial(0), 1);
}

TEST(FactorialTest, HandlesPositiveInput) {
    EXPECT_EQ(factorial(2), 2);
    EXPECT_EQ(factorial(3), 3 * 2);
    EXPECT_EQ(factorial(8), 40320);
}

