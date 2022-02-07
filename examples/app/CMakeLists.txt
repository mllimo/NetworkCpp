cmake_minimum_required(VERSION 3.1)

project(app)
set(THREAD_LIB "")

add_executable(app src/app.cc src/client.cc src/server.cc)

target_include_directories(app PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(app core pthread)