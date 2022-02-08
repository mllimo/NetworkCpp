#include <core/tcp_listener.h>

TcpListener::TcpListener() {
  is_listening_ = false;
}

void TcpListener::Listen() {
  int result = listen(fd_, SOMAXCONN);
  if (result == -1) throw std::runtime_error("listen error");
  is_listening_ = true;
}

void TcpListener::Accept(SocketTcp& socket) {
  if (!is_listening_) throw std::runtime_error("listener is not listening");
  sockaddr_in addr;
  socklen_t addr_len = sizeof(addr);
  int fd = accept(fd_, (sockaddr*)&addr, &addr_len);
  if (fd == -1) throw std::runtime_error("accept error");
  socket.Create(fd, SocketAddr(addr));
}