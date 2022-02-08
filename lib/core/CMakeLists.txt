add_library(core STATIC
  "include/core/socket.h"
  "include/core/socket_udp.h"
  "include/core/socket_tcp.h"
  "include/core/socket_addr.h"
  "include/core/buffer.h"
  "include/core/tcp_listener.h"
  "src/tcp_listener.cc"
  "src/socket_udp.cc"
  "src/socket_tcp.cc"
  "src/socket_addr.cc"
  "src/socket.cc"
)

target_include_directories(core
  PUBLIC "include"
)