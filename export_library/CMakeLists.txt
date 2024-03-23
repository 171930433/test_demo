cmake_minimum_required(VERSION 3.0)

project(MyLibrary VERSION 1.2.3)

# 添加库的源文件
add_library(MyLibrary SHARED my_library.cpp)

# 设置库的版本属性
set_target_properties(MyLibrary PROPERTIES
    VERSION ${MyLibrary_VERSION}
    SOVERSION ${MyLibrary_VERSION_MAJOR}.${MyLibrary_VERSION_MINOR}
)

# 添加包含目录
target_include_directories(MyLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# 安装部分
install(FILES cmake/MyLibraryHelper.cmake DESTINATION lib/cmake/MyLibrary)

# 安装库和头文件
install(TARGETS MyLibrary
  EXPORT MyLibraryTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION include/MyLibrary
  RUNTIME DESTINATION bin
)

# install(FILES my_library.h DESTINATION include/MyLibrary)
install(FILES my_library.h DESTINATION include/MyLibrary)

include(GNUInstallDirs)  # 导入 GNUInstallDirs 模块，包含了这些变量的默认值
set(MyLibrary_DIRS ${CMAKE_INSTALL_PREFIX}/lib/cmake/MyLibrary)
set(MyLibrary_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include/MyLibrary)
set(MyLibrary_LIBRARY_DIRS ${CMAKE_INSTALL_PREFIX}/lib/)


include(CMakePackageConfigHelpers) # 生成 MyLibraryConfig.cmake 文件
configure_package_config_file(MyLibraryConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/MyLibraryConfig.cmake
  INSTALL_DESTINATION lib/cmake/MyLibrary
  # PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR
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
export(TARGETS MyLibrary FILE MyLibraryTargets.cmake)

# 获取 MyLibrary 目标的 INTERFACE_INCLUDE_DIRECTORIES 属性值
get_target_property(include_dirs MyLibrary INTERFACE_INCLUDE_DIRECTORIES)

# 从属性值中过滤掉源代码目录中的路径
list(FILTER include_dirs EXCLUDE REGEX "^${CMAKE_CURRENT_SOURCE_DIR}")

# 设置修正后的 INTERFACE_INCLUDE_DIRECTORIES 属性值
set_target_properties(MyLibrary PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${include_dirs}")
install(EXPORT MyLibraryTargets
        FILE MyLibraryTargets.cmake
        DESTINATION lib/cmake/MyLibrary
)
