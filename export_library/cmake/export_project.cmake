function(install_headers)

  file(GLOB_RECURSE headers ${PROJECT_SOURCE_DIR}/*.h ${PROJECT_SOURCE_DIR}/*.hpp)
  foreach(header ${headers})
      file(RELATIVE_PATH relative_header ${CMAKE_SOURCE_DIR} ${header})
      get_filename_component(header_dir ${relative_header} DIRECTORY)
      install(FILES ${header} DESTINATION include/${PROJECT_NAME}/${header_dir})
  endforeach()

endfunction()


function(export_project)
  # 解析命名参数
  cmake_parse_arguments(EXPORT_PROJECT "" "" "PROJECT_TARGETS" ${ARGN})
  
  # 获取目标名称
  set(project_targets ${EXPORT_PROJECT_PROJECT_TARGETS})


  # 安装目录去除源码部分
  foreach(single_target ${project_targets})
    target_include_directories(${single_target} INTERFACE
      $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    )
  endforeach()


  # 设置库的版本属性
  foreach(single_target ${project_targets})
    set_target_properties(${single_target} PROPERTIES
      VERSION ${PROJECT_VERSION}
      SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
      OUTPUT_NAME ${PROJECT_NAME}_${single_target}
    )  
  endforeach()
  
  # 安装库和头文件
  install(TARGETS ${project_targets}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include/${PROJECT_NAME}
    RUNTIME DESTINATION bin
  )

  include(CMakePackageConfigHelpers)
  configure_package_config_file(cmake/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake 
    INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
  )

  write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
  )

  install(FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Version.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
  )

  export(TARGETS ${project_targets} FILE ${PROJECT_NAME}Targets.cmake)
  install(EXPORT ${PROJECT_NAME}Targets
    NAMESPACE ${PROJECT_NAME}::
    FILE ${PROJECT_NAME}Targets.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
  )

  # 安装PROJECT_SOURCE_DIR下所有*.h *.hpp目录
  install_headers()

endfunction()
