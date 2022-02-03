cmake_minimum_required(VERSION 3.1)

project(app)

add_executable(app src/app.cc)

target_link_libraries(app core)