cmake_minimum_required(VERSION 3.0)

project(lm VERSION 1.2.3)

# 添加库的源文件
add_library(common SHARED my_library.cpp)
add_library(core SHARED my_core.cpp)

add_library(lm SHARED main.cpp )
target_include_directories(lm PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(lm PUBLIC common core)

target_include_directories(common PRIVATE   ${CMAKE_SOURCE_DIR} )
target_include_directories(core PRIVATE    ${CMAKE_SOURCE_DIR} )

# 安装部分
install(FILES cmake/helper.cmake DESTINATION lib/cmake/${PROJECT_NAME} RENAME ${PROJECT_NAME}-helper.cmake)

#!!!!!!!!!!! 导出 cmakelist,使得findpackage可以使用
include(cmake/export_project.cmake)
export_project(
  PROJECT_TARGETS core common lm
  INSTALL_HEADER_DIRS ${CMAKE_CURRENT_LIST_DIR}
)


