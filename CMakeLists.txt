cmake_minimum_required(VERSION 3.0.0)
project(demo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()


add_executable(demo main.cpp )  # 添加 ${PROTO_SRCS} 和 ${PROTO_HDRS} 到源文件列表
target_link_libraries(demo )


# add_subdirectory(export_library)
add_subdirectory(use_expot_library)