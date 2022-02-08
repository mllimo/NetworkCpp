cmake_minimum_required(VERSION 3.1)

project(app-udp)

add_executable(app-udp src/app.cc src/client.cc src/server.cc)

target_include_directories(app-udp PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(app-udp core pthread)