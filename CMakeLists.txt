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
# add_definitions(-DMEMTRACE)
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

set(PROG serial)
set(SOURCES
    src/image/image.cpp
    src/image/format/TIFFimage.cpp
    src/image/format/JPEGimage.cpp
    src/image/format/PNGimage.cpp
    src/image/imageRaster.cpp
    src/processing/serialImageProcessing.cpp
    src/utils/timer.cpp
    src/utils/MemCheck.cpp)
add_executable(${PROG} src/serial.cpp ${SOURCES})
target_link_libraries(${PROG} PRIVATE tiff jpeg png z)
target_compile_definitions(${PROG} PUBLIC -DSERIAL)

if(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES DEBUG)
  add_compile_options(-fno-pie -fno-builtin)
  add_link_options(-no-pie -fno-builtin)
else()
  add_compile_options(-O3)
  message(STATUS "Configuring ${PROJECT_NAME} in Release with CMake")
endif()

# find_package(spdlog REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
