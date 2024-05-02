#include <gtest/gtest.h>
#include "example1.h"
#include "example2.h"
#include "example3.h"
// #include "example4.h"
#include "example5.h"
#include "example6.h"
// #include "example7.h"
#include "example8.h"
// #include "example9.h"
#include "example10.h"
#include "measure_time.h"
#include "test_protobuf.h"
#include "coroutine.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  // 运行所有测试用例
  return RUN_ALL_TESTS();
}