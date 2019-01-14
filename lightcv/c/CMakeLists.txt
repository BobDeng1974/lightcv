# c api interface for operators
file(GLOB c_hdrs *.h)
file(GLOB c_srcs *.c)
file(GLOB cc_hdrs *.hpp)
file(GLOB cc_srcs *.cc)

if(c_hdrs)
  # split srcs and hdrs into folders per operator
  foreach(hdr ${c_hdrs})
    get_filename_component(operator ${hdr} NAME_WE)
    list(APPEND operator_files ${operator}.h ${operator}.cc ${operator}.c ${operator}.hpp)
    source_group("${operator}" FILES ${operator_files})
  endforeach()

  add_library(${libname_prefix}c ${cc_srcs} ${cc_hdrs} ${c_hdrs} ${c_srcs})
  target_link_libraries(${libname_prefix}c ${libname_prefix}cc
                                             ${libname_prefix}core
    )
endif(c_hdrs)


