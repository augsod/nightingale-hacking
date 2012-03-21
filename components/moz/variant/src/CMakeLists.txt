add_subdirectory(static)

project(sbMozVariant)

include_directories(
  ${CMAKE_SOURCE_DIR}/components/include
  ${XUL_INCLUDE_DIRS})

add_definitions(${XUL_CFLAGS})

add_library(${PROJECT_NAME} SHARED
  sbVariant.cpp
  sbVariantUtilsModule.cpp)

target_link_libraries(${PROJECT_NAME}
  ${XUL_LIBRARIES})
