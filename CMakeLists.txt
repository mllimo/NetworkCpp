cmake_minimum_required(VERSION 3.1)

project(cmake-medium)

add_subdirectory(lib)
add_subdirectory(examples)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)