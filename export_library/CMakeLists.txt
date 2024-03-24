cmake_minimum_required(VERSION 3.0)

project(MyLibrary VERSION 1.2.3)

# 添加库的源文件
add_library(common SHARED my_library.cpp)
add_library(core SHARED my_core.cpp)


# 设置库的版本属性
set_target_properties(common PROPERTIES
    VERSION ${MyLibrary_VERSION}
    SOVERSION ${MyLibrary_VERSION_MAJOR}.${MyLibrary_VERSION_MINOR}
    OUTPUT_NAME ${PROJECT_NAME}_common
)
set_target_properties(core PROPERTIES
    VERSION ${MyLibrary_VERSION}
    SOVERSION ${MyLibrary_VERSION_MAJOR}.${MyLibrary_VERSION_MINOR}
    OUTPUT_NAME ${PROJECT_NAME}_core
)

target_include_directories(common INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/MyLibrary>
)

target_include_directories(core INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/MyLibrary>
)

# 安装部分
install(FILES cmake/MyLibraryHelper.cmake DESTINATION lib/cmake/MyLibrary)

# 安装库和头文件
install(TARGETS core common
  EXPORT MyLibraryTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION include/MyLibrary
  RUNTIME DESTINATION bin
)

install(FILES my_library.h my_core.h  DESTINATION include/MyLibrary)

include(CMakePackageConfigHelpers) # 生成 MyLibraryConfig.cmake 文件
configure_package_config_file(MyLibraryConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/MyLibraryConfig.cmake
  INSTALL_DESTINATION lib/cmake/MyLibrary
)

# 生成 MyLibraryVersion.cmake 文件
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/MyLibraryVersion.cmake
  VERSION ${MyLibrary_VERSION}
  COMPATIBILITY AnyNewerVersion
)

# 安装 MyLibraryConfig.cmake 文件
install(FILES 
  ${CMAKE_CURRENT_BINARY_DIR}/MyLibraryConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/MyLibraryVersion.cmake
  DESTINATION lib/cmake/MyLibrary
)

# 导出库的导出目标
export(TARGETS core common FILE MyLibraryTargets.cmake)

# 获取 MyLibrary 目标的 INTERFACE_INCLUDE_DIRECTORIES 属性值
# get_target_property(include_dirs common INTERFACE_INCLUDE_DIRECTORIES)
# list(FILTER include_dirs EXCLUDE REGEX "^${CMAKE_CURRENT_SOURCE_DIR}")
# set_target_properties(common PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${include_dirs}")



# core
get_target_property(include_dirs core INTERFACE_INCLUDE_DIRECTORIES)
list(FILTER include_dirs EXCLUDE REGEX "^${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(core PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${include_dirs}")





# 设置修正后的 INTERFACE_INCLUDE_DIRECTORIES 属性值
install(EXPORT MyLibraryTargets
        NAMESPACE MyLibrary::
        FILE MyLibraryTargets.cmake
        DESTINATION lib/cmake/MyLibrary
)