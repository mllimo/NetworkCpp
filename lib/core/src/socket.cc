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

void Socket::SetTimeout(int seconds, int microseconds) {
  timeval tv;
  tv.tv_sec = seconds;
  tv.tv_usec = microseconds;
  if (setsockopt(fd_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
    throw std::runtime_error("setsockopt error");
  }
}

size_t Socket::Send(const Buffer<>& buffer, const SocketAddr& addr) {
  sockaddr_in ip = addr.CSockaddr();
  size_t n = sendto(fd_, &buffer, sizeof(buffer), 0, (sockaddr*)&ip, sizeof(ip));
  if (n < 0) throw std::runtime_error("sendto error");
  return n;
}

size_t Socket::Send(const Buffer<>& buffer) {
  size_t n = send(fd_, &buffer, sizeof(buffer), 0);
  if (n < 0) throw std::runtime_error("send error");
  return n;
}

size_t Socket::Receive(Buffer<>& buffer, SocketAddr& addr) {
  sockaddr_in ip = addr.CSockaddr();
  socklen_t len = sizeof(ip);
  ssize_t n = recvfrom(fd_, &buffer, sizeof(buffer), MSG_DONTWAIT, (sockaddr*)&ip, &len);

  if (n < 0)
    if (errno == EAGAIN) return 0;
    else throw std::runtime_error("recvfrom error");

  addr.CSockAddr(ip);
  return n;
}

size_t Socket::Receive(Buffer<>& buffer) {
  ssize_t n = recv(fd_, &buffer, sizeof(buffer), MSG_DONTWAIT);
  if (n < 0)
    if (errno == EAGAIN)return 0;
    else throw std::runtime_error("recvfrom error");
  return n;
}

void Socket::Connect(const SocketAddr& addr) {
  sockaddr_in ip = addr.CSockaddr();
  if (connect(fd_, (sockaddr*)&ip, sizeof(ip)) < 0) {
    throw std::runtime_error("connect error");
  }
}