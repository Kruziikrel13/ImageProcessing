function(add_slang_shader TARGET)
  cmake_parse_arguments("SHADER" "" "" "ENTRIES" ${ARGN})
  set(sources ${SHADER_UNPARSED_ARGUMENTS})
  set(entries)
  foreach(entry ${SHADER_ENTRIES})
    list(APPEND entries -entry ${entry})
  endforeach()
  
  set(SHADERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/shaders)
  add_custom_command (
    OUTPUT ${SHADERS_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADERS_DIR}
  )
  set(output ${SHADERS_DIR}/${TARGET}.spv)
  add_custom_command (
    OUTPUT ${output}
    COMMAND slangc ${sources} -o ${output} -target spirv -profile spirv_1_4 -emit-spirv-directly -fvk-use-entrypoint-name ${entries}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    DEPENDS ${SHADERS_DIR} ${sources}
    COMMENT "Compiling slang shader(s) to ${output}"
    VERBATIM
  )

  add_custom_target(${TARGET} DEPENDS ${output})
endfunction()
