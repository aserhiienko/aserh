#include <gtest/gtest.h>

extern int TestReturnOne();

namespace {
TEST(TestReturnOneFunction, TestReturnOneReturnsOne) {
    EXPECT_EQ(TestReturnOne(), 1);

}
}