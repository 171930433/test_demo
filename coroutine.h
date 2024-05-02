#include <iostream>
#include <boost/coroutine/all.hpp>

using namespace std;

void coro_func(boost::coroutines::coroutine<int>::push_type& yield) {
  for (int i = 0; i < 5; ++i) {
    cout << "Coroutine yielding: " << i << endl;
    yield(i);  // 挂起协程并传递当前值给调用方
  }
}

int Test1() {
  boost::coroutines::coroutine<int>::pull_type coro(coro_func);  // 创建协程

  while (coro) {
    int value = coro.get();  // 获取协程产生的值
    cout << "Main receiving: " << value << endl;
    coro();  // 继续执行协程
  }

  cout << "Coroutine finished" << endl;

  return 0;
}

TEST(coroutine, TEST1) {
  EXPECT_EQ(Test1(), 0);  //
}