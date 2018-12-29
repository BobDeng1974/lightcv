# c++ API interface
file(GLOB srcs *.cc)
file(GLOB hdrs *.h)

if(hdrs)
  # split srcs and hdrs into folders per operator
  foreach(hdr ${hdrs})
    get_filename_component(operator ${hdr} NAME_WE)
    list(APPEND operator_files ${operator}.h ${operator}.cc)
    message(STATUS ${operator_files})
    source_group("${operator}" FILES ${operator_files})
  endforeach()

  add_library(${libname_prefix}cc ${srcs} ${hdrs})
  target_link_libraries(${libname_prefix}cc ${libname_prefix}operator
                                             ${libname_prefix}type
    )
endif(hdrs)


