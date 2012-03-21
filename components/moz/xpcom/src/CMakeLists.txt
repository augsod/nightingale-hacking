project(sbXPCOM)

include_directories(
  ${CMAKE_BINARY_DIR}/components/moz/xpcom/public
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/include
  ${XUL_INCLUDE_DIRS})

add_definitions(${XUL_CFLAGS})

add_library(${PROJECT_NAME} SHARED
  sbCOMArray.cpp
  sbArray.cpp
  sbPropertyBag.cpp
  sbServiceManager.cpp
  sbWeakReference.cpp
  sbXPCOMModule.cpp)

add_dependencies(${PROJECT_NAME}
  sbIXPCOM)

target_link_libraries(${PROJECT_NAME}
  sbMozThreads
  ${XUL_LIBRARIES})
