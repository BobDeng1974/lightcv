# core types and infrastructures

set(type_SRCS basic.h
              var.h
              var.cc
              tuple.h
              tuple.cc
)

add_library(lightcv_type SHARED ${type_SRCS})
target_link_libraries(lightcv_type ${OpenCV_LIBS})

add_executable(tuple_test tuple_test.cc)
target_link_libraries(tuple_test lightcv_type gtest_main)

add_executable(tuple_perf tuple_perf.cc)
target_link_libraries(tuple_perf lightcv_type benchmark)

if(MSVC)
  set_property(TARGET lightcv_type PROPERTY FOLDER "type") 
  set_property(TARGET tuple_test PROPERTY FOLDER "type") 
  set_property(TARGET tuple_perf PROPERTY FOLDER "type") 
endif(MSVC)

install(TARGETS lightcv_type RUNTIME DESTINATION bin)

