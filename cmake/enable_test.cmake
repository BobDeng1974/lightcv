# if BUILD_TESTS then 
#    1. download and build googletest and benchmark
#    2. find Halcon
#    3. enable_testing() if success, otherwise disable BUILD_TESTS

#---------------------------------------------------------------------------
# googletest
# Download and unpack googletest at configure time
configure_file(cmake/googletest.cmake.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

if(MSVC)
  set_property(TARGET gtest PROPERTY FOLDER "utils")
  set_property(TARGET gtest_main PROPERTY FOLDER "utils")
endif(MSVC)

#---------------------------------------------------------------------------
# benchmark
# Download and unpack benchmark at configure time
configure_file(cmake/benchmark.cmake.in benchmark-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/benchmark-download )
if(result)
  message(FATAL_ERROR "CMake step for benchmark failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/benchmark-download )
if(result)
  message(FATAL_ERROR "Build step for benchmark failed: ${result}")
endif()

set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)

# Add benchmark directly to our build. This defines
# the benchmark target.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/benchmark-src
                 ${CMAKE_CURRENT_BINARY_DIR}/benchmark-build
                 EXCLUDE_FROM_ALL)
if(MSVC)
  set_property(TARGET benchmark PROPERTY FOLDER "utils")
endif(MSVC)

#---------------------------------------------------------------------------
# Find halcon for test and benchmark


enable_testing()

