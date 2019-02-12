# core cores and infrastructures

set(core_srcs basic.h
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

add_library(${libname_prefix}core SHARED ${core_srcs})
target_link_libraries(${libname_prefix}core ${OpenCV_LIBS})

if(build_tests)
  add_executable(tuple_test tuple_test.cc)
  target_link_libraries(tuple_test ${libname_prefix}core gtest_main)
  add_test(tuple_test tuple_test)

  add_executable(object_test object_test.cc)
  target_link_libraries(object_test ${libname_prefix}core gtest_main)
  add_test(object_test object_test)
endif(build_tests)

if(MSVC OR XCODE)
  if(build_tests)
    set_property(TARGET tuple_test PROPERTY FOLDER "test") 
    set_property(TARGET object_test PROPERTY FOLDER "test") 
  endif(build_tests)
endif(MSVC OR XCODE)

if(WIN32)
  install(TARGETS ${libname_prefix}core RUNTIME DESTINATION bin)
endif()

