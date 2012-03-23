cmake_minimum_required(VERSION 2.6)

project(nightingale)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules/)

find_package(XUL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/dist/jsmodules)

add_subdirectory(bindings)
add_subdirectory(components)