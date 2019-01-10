# scan headers to build all operators, their tests and benchmarks

get_filename_component(top_folder ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
file(GLOB operators_hdrs RELATIVE "${top_folder}" "${top_folder}/*.h")
set(operators )
set(operators_srcs )
if(operators_hdrs)
  foreach(hdr ${operators_hdrs})
    get_filename_component(operator ${hdr} NAME_WE)
    source_group("${operator}" FILES "${operator}.h")
    list(APPEND operators ${operator})
    if(EXISTS "${top_folder}/${operator}.cc")
      list(APPEND operators_srcs ${operator}.cc)
      source_group("${operator}" FILES "${operator}.cc")
    endif()
  endforeach()
endif(operators_hdrs)

if(operators)
  add_library(${libname_prefix}operator SHARED ${operators_hdrs} ${operators_srcs})
  target_link_libraries(${libname_prefix}operator ${OpenCV_LIBS}
                                                  ${libname_prefix}core
    )
endif(operators)

if(WIN32)
  install(TARGETS ${libname_prefix}operator RUNTIME DESTINATION bin)
endif()

if(build_tests)
  foreach(operator ${operators})
    if(EXISTS "${top_folder}/${operator}_test.cc")
      add_executable(${operator}_test ${operator}_test.cc)
      target_link_libraries(${operator}_test ${libname_prefix}core
                                             ${libname_prefix}operator
                                             ${libname_prefix}cc
                                             ${OpenCV_LIBS}
                                             gtest_main
        )
      add_test(${operator}_test ${operator}_test)

      if(MSVC OR XCODE)
        set_property(TARGET ${operator}_test PROPERTY FOLDER "test")
      endif()
    endif()
    if(EXISTS "${top_folder}/${operator}_perf.cc")
      add_executable(${operator}_perf ${operator}_perf.cc)
      target_link_libraries(${operator}_perf ${libname_prefix}core
                                             ${libname_prefix}operator
                                             ${libname_prefix}cc
                                             ${OpenCV_LIBS}
                                             benchmark
        )

      if(MSVC OR XCODE)
        set_property(TARGET ${operator}_perf PROPERTY FOLDER "perf")
      endif()
    endif()
  endforeach()
endif(build_tests)

