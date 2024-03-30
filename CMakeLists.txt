cmake_minimum_required(VERSION 3.0.0)
project(demo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "CMAKE_INSTALL_PREFIX" FORCE)
set(CMAKE_BUILD_TYPE Release CACHE STRING "CMAKE_BUILD_TYPE" FORCE)
set(CMAKE_INSTALL_PREFIX "/home/gsk/pro/test_demo/install" CACHE PATH "CMAKE_INSTALL_PREFIX" FORCE)
set(CMAKE_PREFIX_PATH "/home/gsk/pro/ubuntu2204_docker/install;/home/gsk/pro/test_demo/install" CACHE PATH "CMAKE_PREFIX_PATH" FORCE)

include(CTest)
enable_testing()


add_executable(demo main.cpp )  # 添加 ${PROTO_SRCS} 和 ${PROTO_HDRS} 到源文件列表
target_link_libraries(demo )


add_subdirectory(export_library)
# add_subdirectory(use_expot_library)
# add_subdirectory(dynamic_load)