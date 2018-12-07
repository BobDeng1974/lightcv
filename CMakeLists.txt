cmake_minimum_required(VERSION 3.0)
project(lightcv)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# compiler
option(ENABLE_OPENMP "Use OpenMP" ON)
if(ENABLE_OPENMP)
  include(enable_openmp)
endif(ENABLE_OPENMP)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
  set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /MP")
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")
endif(MSVC)

# build
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/Debug/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/Debug/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/Release/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/Release/lib)
option(BUILD_TESTS "Builds tests and benchmarks" OFF)
if(BUILD_TESTS)
  include(enable_test)
endif(BUILD_TESTS)

# install
set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)

# project
include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(third_party)
add_subdirectory(lightcv)
add_subdirectory(tools)

