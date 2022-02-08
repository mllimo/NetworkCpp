#include <core/socket.h>

Socket::Socket(int domain, int type, int protocol) {
  fd_ = socket(domain, type, protocol);
  if (fd_ < 0) throw std::runtime_error("socket error");
}

Socket::~Socket() {
  try {
    close(fd_);
    if (fd_ < 0) throw std::runtime_error("socket close error");
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

void Socket::Bind(const SocketAddr& addr) {
  addr_ = addr;
  sockaddr_in ip = addr_.CSockaddr();
  if (bind(fd_, (sockaddr*)&ip, sizeof(ip)) < 0) {
    throw std::runtime_error("bind error");
  }
}

void Socket::SetTimeout(int microseconds) {
  timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = microseconds;
  if (setsockopt(fd_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
    throw std::runtime_error("setsockopt error");
  }
}