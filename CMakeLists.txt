cmake_minimum_required(VERSION 3.10)
project(lightcv)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# compiler
set(CMAKE_CXX_STANDARD 11)
option(enable_openmp "Use OpenMP" ON)
if(enable_openmp)
  include(enable_openmp)
endif(enable_openmp)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
  set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /MP")
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")
elseif(XCODE)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")
endif()

# build
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/Debug/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/Debug/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/Release/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/Release/lib)
option(build_tests "Builds tests and benchmarks" ON)
set(libname_prefix "lightcv_")
if(build_tests)
  include(enable_test)
endif(build_tests)

# install
set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)

# project
include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(third_party)
add_subdirectory(lightcv)
add_subdirectory(tools)

