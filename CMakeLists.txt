cmake_minimum_required(VERSION 2.6)

project(nightingale)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules/)

find_package(XUL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_subdirectory(app)
add_subdirectory(bindings)
add_subdirectory(branding)
add_subdirectory(components)
add_subdirectory(extensions)
add_subdirectory(feathers)
add_subdirectory(locales)
