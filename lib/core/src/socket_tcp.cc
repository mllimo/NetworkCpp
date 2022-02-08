#include <core/socket_tcp.h>

SocketTcp::SocketTcp() : Socket(AF_INET, SOCK_STREAM, 0) {
}

SocketTcp::SocketTcp(SocketTcp&& socket) : Socket(std::move(socket)) {}

size_t SocketTcp::Send(const Buffer<>& buffer) const {
  size_t n = send(fd_, &buffer, sizeof(buffer), 0);
  if (n < 0) throw std::runtime_error("send error");
  return n;
}

size_t SocketTcp::Receive(Buffer<>& buffer) const {
  ssize_t n = recv(fd_, &buffer, sizeof(buffer), blocking_mode_);
  if (n < 0)
    if (errno == EAGAIN)return 0;
    else throw std::runtime_error("recvfrom error");
  return n;
}

Type SocketTcp::GetType() const {
  return Type::TCP;
}

void SocketTcp::Disconect() {
  Close();
}

bool operator<(const SocketTcp& lhs, const SocketTcp& rhs) {
  return lhs.fd_ < rhs.fd_;
}

void SocketTcp::Connect(const SocketAddr& addr) {
  sockaddr_in ip = addr.CSockaddr();
  if (connect(fd_, (sockaddr*)&ip, sizeof(ip)) < 0) {
    throw std::runtime_error("connect error");
  }
}