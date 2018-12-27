# core types and infrastructures

set(type_SRCS basic.h
              var.h
              var.cc
              tuple.h
              tuple.cc
              object.h
              object.cc
              data.h
              data.cc
)

add_library(lightcv_type SHARED ${type_SRCS})
target_link_libraries(lightcv_type ${OpenCV_LIBS})

if(BUILD_TESTS)
  add_executable(tuple_test tuple_test.cc)
  target_link_libraries(tuple_test lightcv_type gtest_main)
  add_test(tuple_test tuple_test)

  add_executable(object_test object_test.cc)
  target_link_libraries(object_test lightcv_type gtest_main)
  add_test(object_test object_test)
endif(BUILD_TESTS)

if(MSVC OR XCODE)
  set_property(TARGET lightcv_type PROPERTY FOLDER "type") 
  if(BUILD_TESTS)
    set_property(TARGET tuple_test PROPERTY FOLDER "type") 
    set_property(TARGET object_test PROPERTY FOLDER "type") 
  endif(BUILD_TESTS)
endif(MSVC OR XCODE)

if(WIN32)
  install(TARGETS lightcv_type RUNTIME DESTINATION bin)
endif()

