cmake_minimum_required(VERSION 3.0)

project(dynamic_load)


# 寻找 MyLibrary
find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(protobuf REQUIRED)

add_library(project1 SHARED project1.cpp)
target_include_directories(project1 PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(project1 PUBLIC protobuf::libprotobuf)

add_library(project2 SHARED project2.cpp)
target_include_directories(project2 PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(project2 PUBLIC protobuf::libprotobuf)


add_executable(main main.cpp)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(main ${Boost_LIBRARIES} )






