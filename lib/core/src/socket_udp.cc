#include <core/socket_udp.h>

SocketUdp::SocketUdp() : Socket(AF_INET, SOCK_DGRAM, 0) {}

SocketUdp::SocketUdp(SocketUdp&& socket) : Socket(std::move(socket)) {}

size_t SocketUdp::Send(const Buffer<>& buffer, const SocketAddr& addr) const {
  sockaddr_in ip = addr.CSockaddr();
  size_t n = sendto(fd_, &buffer, sizeof(buffer), 0, (sockaddr*)&ip, sizeof(ip));
  if (n < 0) throw std::runtime_error("sendto error");
  return n;
}

size_t SocketUdp::Receive(Buffer<>& buffer, SocketAddr& addr) const {
  sockaddr_in ip = addr.CSockaddr();
  socklen_t len = sizeof(ip);
  ssize_t n = recvfrom(fd_, &buffer, sizeof(buffer), blocking_mode_, (sockaddr*)&ip, &len);

  if (n < 0)
    if (errno == EAGAIN) return 0;
    else throw std::runtime_error("recvfrom error");

  addr.CSockAddr(ip);
  return n;
}

Type SocketUdp::GetType() const {
  return Type::UDP;
}

bool operator<(const SocketUdp& lhs, const SocketUdp& rhs) {
  return lhs.fd_ < rhs.fd_;
}