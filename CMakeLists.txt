cmake_minimum_required(VERSION 3.30)

# Get version
file(READ "${CMAKE_SOURCE_DIR}/VERSION" VER_RAW)
string(STRIP ${VER_RAW} VER)

project(
  ImageProcessing
  DESCRIPTION "Image processing in C++: serial and parallel implementations using Vulkan API, with speedup comparison. For CAB401 Course at QUT"
  VERSION ${VER}
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
  -Wno-unused-parameter
  -Wno-unused-value
  -Wno-missing-field-initializers
  -Wno-narrowing
  -Wno-pointer-arith
  -Wno-clobbered
  -fmacro-prefix-map=${CMAKE_SOURCE_DIR}/=)

set(CMAKE_EXECUTABLE_ENABLE_EXPORTS TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(include)
include(cmake/shaders.cmake)

if(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES DEBUG)
  add_compile_options(-g -fno-pie -fno-builtin)
  add_link_options(-g -no-pie -fno-builtin)
  add_definitions(-DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)

  if (TRACE)
    add_compile_options(-O0)
    add_link_options(-O0)
    add_definitions(-DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)
  endif()

else()
  add_compile_options(-O3)
  add_link_options(-O3)
  message(STATUS "Configuring ${PROJECT_NAME} in Release with CMake")
endif()

if (PROFILE)
  add_compile_options(-pg)
  add_link_options(-pg)
endif()

if (ASAN)
  add_compile_options(-fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -O0)
  add_link_options(-fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -O0)
endif()

add_slang_shader(processors shaders/processors.slang ENTRIES blurCompute)

## Serial
set(PROG serial)
set(SOURCES
    src/shared.cpp
    src/image/image.cpp
    src/image/format/TIFFimage.cpp
    src/image/format/JPEGimage.cpp
    src/image/format/PNGimage.cpp
    src/image/imageRaster.cpp
    src/processing/serialImageProcessing.cpp
    src/utils/timer.cpp)
add_executable(${PROG} src/serial.cpp)
target_sources(${PROG} PRIVATE ${SOURCES})
target_link_libraries(${PROG} PRIVATE tiff jpeg png z)
target_precompile_headers(${PROG} PRIVATE include/pch/pch.hpp)

find_package(spdlog REQUIRED)
target_link_libraries(${PROG} PRIVATE spdlog::spdlog)

## Parallel
set(PROG parallel)
list(APPEND SOURCES
      src/vlk/VulkanContext.cpp)
add_executable(${PROG} src/parallel.cpp)
target_sources(${PROG} PRIVATE ${SOURCES})
target_link_libraries(${PROG} PRIVATE tiff jpeg png z)

find_package(OpenMP REQUIRED)
target_link_libraries(${PROG} PRIVATE OpenMP::OpenMP_CXX)

find_package(Vulkan REQUIRED)
target_include_directories(${PROG} PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROG} PRIVATE ${Vulkan_LIBRARIES} spdlog::spdlog)
target_compile_definitions(${PROG} PRIVATE
        VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1
        VULKAN_HPP_NO_STRUCT_CONSTRUCTORS=1)
add_dependencies(${PROG} processors)
target_precompile_headers(${PROG} PRIVATE include/pch/pch.hpp)
