cmake_minimum_required(VERSION 3.1)

project(app-tcp)

add_executable(app-tcp src/app.cc src/client.cc src/server.cc)

target_include_directories(app-tcp PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(app-tcp core pthread)