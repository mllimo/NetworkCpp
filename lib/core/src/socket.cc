#include <core/socket.h>

Socket::Socket(int domain, int type, int protocol) {
  fd_ = -1;
  is_blocking_ = false;
  blocking_mode_ = 0;
  domain_ = domain;
  type_ = type;
  protocol_ = protocol;
}

Socket::~Socket() {
  try {
    Close();
  }
  catch (std::exception& e) {
    std::cerr << "Socket::~Socket() - " << e.what() << std::endl;
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

void Socket::SetBlocking(bool blocking) {
  is_blocking_ = blocking;
  blocking_mode_ = (blocking ? 0 : MSG_DONTWAIT);
}

bool Socket::IsBlocking() const {
  return is_blocking_;
}

void Socket::Close() {
  close(fd_);
  if (fd_ < 0) throw std::runtime_error("socket close error");
}

void Socket::Open() {
  fd_ = socket(domain_, type_, protocol_);
  if (fd_ < 0) throw std::runtime_error("socket error");
}