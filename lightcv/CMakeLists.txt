
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

if(MSVC)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_subdirectory(type)
add_subdirectory(lib)
add_subdirectory(operators)
add_subdirectory(c)
add_subdirectory(cc)

