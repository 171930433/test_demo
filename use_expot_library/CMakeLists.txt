cmake_minimum_required(VERSION 3.0)

project(MyProject)


# 寻找 MyLibrary
find_package(lm REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)


# 创建可执行文件
add_executable(my_executable main.cpp)

# 链接 MyLibrary
target_link_libraries(my_executable PRIVATE lm::core lm::common)

add_executable(direct_load direct_load_so.cpp)

target_link_libraries(direct_load
  ${Boost_LIBRARIES}
)


