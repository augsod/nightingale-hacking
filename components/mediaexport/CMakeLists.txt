if(WIN32 OR APPLE)
  add_subdirectory(agent)
endif()

add_subdirectory(playlist)
add_subdirectory(public)
add_subdirectory(src)
