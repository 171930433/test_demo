cmake_minimum_required(VERSION 3.0)

project(MyLibrary VERSION 1.2.3)

# 添加库的源文件
add_library(MyLibrary SHARED my_library.cpp)

# 添加包含目录
target_include_directories(MyLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 安装库和头文件
install(TARGETS MyLibrary
        EXPORT MyLibraryTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

install(FILES my_library.h DESTINATION include)

# 生成 MyLibraryConfig.cmake 文件
include(CMakePackageConfigHelpers)
configure_package_config_file(MyLibraryConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MyLibraryConfig.cmake
    INSTALL_DESTINATION lib/cmake/MyLibrary
)

# 安装 MyLibraryConfig.cmake 文件
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MyLibraryConfig.cmake
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
