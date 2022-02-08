add_library(core STATIC
  "include/core/socket.h"
  "include/core/socket_udp.h"
  "include/core/socket_tcp.h"
  "include/core/socket_addr.h"
  "include/core/buffer.h"
  "src/socket_udp.cc"
  "src/socket_tcp.cc"
  "src/socket_addr.cc"
  "src/socket.cc"
)

target_include_directories(core
  PUBLIC "include"
)