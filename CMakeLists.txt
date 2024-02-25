cmake_minimum_required(VERSION 3.0.0)
project(demo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

find_package(Protobuf REQUIRED PATHS /home/gsk/pro/CyberRT/install/lib/cmake/protobuf)
# find_package(Boost REQUIRED PATHS /home/gsk/pro/CyberRT/install/lib/cmake/boost)
find_package(yalantinglibs REQUIRED PATHS ./install_dir/lib/cmake/yalantinglibs)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/proto)

# # 获取 proto 文件夹下的所有 .proto 文件
# file(GLOB PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto)

# # 生成 C++ 文件
# # PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
# protobuf_generate(
#     LANGUAGE cpp  # 生成的语言，这里是 C++
#     OUT_VAR PROTO_SRCS  # 生成的 .pb.cc 文件会存放在该变量中
#     OUT_VAR PROTO_HDRS  # 生成的 .pb.h 文件会存放在该变量中
#     PROTOC_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}  # 生成文件的输出目录
#     PROTOS ${PROTO_FILES}  # 指定需要处理的 .proto 文件列表
# )

# # 包含生成的源码文件
# include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(demo main.cpp )  # 添加 ${PROTO_SRCS} 和 ${PROTO_HDRS} 到源文件列表
target_link_libraries(demo )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
