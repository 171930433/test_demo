function(install_headers _HEADER_DIR)
  # message(install_headers called, _HEADER_DIR=${_HEADER_DIR})

  file(GLOB_RECURSE headers ${_HEADER_DIR}/*.h ${_HEADER_DIR}/*.hpp)
  foreach(header ${headers})
      if (${header} MATCHES "^${CMAKE_BINARY_DIR}")
        # message(header=${header})
        # message(relative_header=${relative_header})
        file(RELATIVE_PATH relative_header ${CMAKE_BINARY_DIR} ${header})
      else()
        # message(1111header=${header})
        # message(1111relative_header=${relative_header})
        file(RELATIVE_PATH relative_header ${CMAKE_SOURCE_DIR} ${header})
      endif()
      
      get_filename_component(header_dir ${relative_header} DIRECTORY)
      install(FILES ${header} DESTINATION include/${PROJECT_NAME}/${header_dir})
  endforeach()

endfunction()

function(install_deb)
  # 创建DEBIAN目录
  file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/DEBIAN)
  # 创建控制文件
  configure_file(control.in ${CMAKE_INSTALL_PREFIX}/DEBIAN/control @ONLY)
  # 打包
  add_custom_target(deb
    COMMAND dpkg-deb --build ${CMAKE_INSTALL_PREFIX} ${CMAKE_SOURCE_DIR} 
    WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}
    COMMENT "Packaging Debian package..."
  )
  # add_dependencies(deb install)
endfunction()



function(export_project)
  # 解析命名参数
  cmake_parse_arguments(EXPORT_PROJECT "" "" "PROJECT_TARGETS;INSTALL_HEADER_DIRS" ${ARGN})
  
  # 获取目标名称
  set(project_targets ${EXPORT_PROJECT_PROJECT_TARGETS})
  set(install_header_dirs ${EXPORT_PROJECT_INSTALL_HEADER_DIRS})


  # 安装目录去除源码部分
  foreach(single_target ${project_targets})
    target_include_directories(${single_target} INTERFACE
      # $<INSTALL_INTERFACE:include/${PROJECT_NAME}> # 默认包含,不需要重复添加
    )
    target_link_directories(${single_target} INTERFACE
      $<INSTALL_INTERFACE:lib>
    )

    # 设置库的版本属性
    set_target_properties(${single_target} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    OUTPUT_NAME ${PROJECT_NAME}_${single_target}
  )  
  endforeach()

  
  # 安装库和头文件
  install(TARGETS ${project_targets}
    EXPORT ${PROJECT_NAME}-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include/${PROJECT_NAME}
    RUNTIME DESTINATION bin
  )

  include(CMakePackageConfigHelpers)
  configure_package_config_file(cmake/config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake 
    INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
  )

  write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
  )

  install(FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-version.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
  )

  export(TARGETS ${project_targets} FILE ${PROJECT_NAME}Targets.cmake)
  install(EXPORT ${PROJECT_NAME}-targets
    NAMESPACE ${PROJECT_NAME}::
    FILE ${PROJECT_NAME}-targets.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
  )

  # 安装PROJECT_SOURCE_DIR下所有*.h *.hpp目录
  foreach(single_dir ${install_header_dirs})
    install_headers(${single_dir})
  endforeach()
  
  # 打包deb
  install_deb()



endfunction()

