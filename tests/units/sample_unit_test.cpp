#include <gtest/gtest.h>

TEST(sample_tests, test1)
{
    ASSERT_EQ(1, 1);
    ASSERT_NE(1, -1);
    ASSERT_FLOAT_EQ(1.f, 1.f);
    ASSERT_DOUBLE_EQ(1., 1.);
}

TEST(sample_tests, test2)
{
    ASSERT_EQ(1, 1);
    ASSERT_NE(1, -1);
    ASSERT_FLOAT_EQ(1.f, 1.f);
    ASSERT_DOUBLE_EQ(1., 1.);
}
