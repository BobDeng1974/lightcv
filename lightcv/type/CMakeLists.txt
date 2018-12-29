# core types and infrastructures

set(type_srcs basic.h
              var.h
              var.cc
              tuple.h
              tuple.cc
              object.h
              object.cc
              data.h
              data.cc
              operator.h
              operator.cc
              error.h
)

add_library(${libname_prefix}type SHARED ${type_srcs})
target_link_libraries(${libname_prefix}type ${OpenCV_LIBS})

if(build_tests)
  add_executable(tuple_test tuple_test.cc)
  target_link_libraries(tuple_test ${libname_prefix}type gtest_main)
  add_test(tuple_test tuple_test)

  add_executable(object_test object_test.cc)
  target_link_libraries(object_test ${libname_prefix}type gtest_main)
  add_test(object_test object_test)
endif(build_tests)

if(MSVC OR XCODE)
  set_property(TARGET ${libname_prefix}type PROPERTY FOLDER "type") 
  if(build_tests)
    set_property(TARGET tuple_test PROPERTY FOLDER "type") 
    set_property(TARGET object_test PROPERTY FOLDER "type") 
  endif(build_tests)
endif(MSVC OR XCODE)

if(WIN32)
  install(TARGETS ${libname_prefix}type RUNTIME DESTINATION bin)
endif()

