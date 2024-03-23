cmake_minimum_required(VERSION 3.0)

project(MyProject)

set(CMAKE_PREFIX_PATH "/home/gsk/pro/test_demo/install")

# 寻找 MyLibrary
find_package(MyLibrary REQUIRED)

# 创建可执行文件
add_executable(my_executable main.cpp)

MyDemo()

message(status 2!!!!!!${MyLibrary_DIRS})
message(status 3!!!!!!${MyLibrary_INCLUDE_DIRS})
message(status 3!!!!!!${MyLibrary_LIBRARY_DIRS})

# target_include_directories(my_executable PRIVATE ${MyLibrary_INCLUDE_DIRS})

# 链接 MyLibrary
target_link_libraries(my_executable PRIVATE MyLibrary)
