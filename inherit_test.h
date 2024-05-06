#pragma once
#include <gtest/gtest.h>

class SA;

class Base {
 private:
  int a = 1;
  friend SA;    // 是base开口子给子类访问，无法在子类内部说明
};

class SA : public Base {
 public:

  int fun() { return a + 1; }

 private:
};

TEST(inherit_test, demo) {
  SA a;
  EXPECT_EQ(2, a.fun());
}
