#include <core/socket_addr.h>

SocketAddr::SocketAddr(const std::string& ip, int port, int domain) {
  family_ = domain;
  port_ = port;
  ip_ = ip;
}

SocketAddr::SocketAddr(const sockaddr_in& addr) {
  family_ = addr.sin_family;
  port_ = ntohs(addr.sin_port);
  ip_ = inet_ntoa(addr.sin_addr);
}

const std::string& SocketAddr::Ip() const {
  return ip_;
}

int SocketAddr::Port() const {
  return port_;
}

int SocketAddr::Domain() const {
  return family_;
}

void SocketAddr::Ip(const std::string& ip) {
  ip_ = ip;
}

void SocketAddr::Port(int port) {
  port_ = port;
}

void SocketAddr::Domain(int domain) {
  family_ = domain;
}

void SocketAddr::CSockAddr(struct sockaddr_in& addr) {
  family_ = addr.sin_family;
  port_ = ntohs(addr.sin_port);
  ip_ = inet_ntoa(addr.sin_addr);
}

sockaddr_in SocketAddr::CSockaddr() const {
  sockaddr_in addr;
  addr.sin_family = family_;
  addr.sin_port = htons(port_);
  addr.sin_addr.s_addr = inet_addr(ip_.c_str());
  return addr;
}

std::ostream& operator<<(std::ostream& os, const SocketAddr& addr) {
  os << "Ip: " << addr.Ip() << " Port: " << addr.Port() << " Domain: " << addr.Domain();
  return os;
}

bool operator<(const SocketAddr& lhs, const SocketAddr& rhs) {
  if (lhs.Ip() < rhs.Ip()) {
    return true;
  }
  else if (lhs.Ip() == rhs.Ip()) {
    return lhs.Port() < rhs.Port();
  }
  return false;
}