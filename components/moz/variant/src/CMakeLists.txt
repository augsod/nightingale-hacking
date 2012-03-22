include(SbLibrary)

add_subdirectory(static)

project(sbMozVariant)

sb_library(SHARED
  sbVariant.cpp
  sbVariantUtilsModule.cpp)
