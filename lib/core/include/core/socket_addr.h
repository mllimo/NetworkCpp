#pragma once

#include <string>
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class SocketAddr {
public:
  SocketAddr(const std::string& ip = "", int port = 0, int domain = AF_INET);
  SocketAddr(const struct sockaddr_in& addr);
  SocketAddr(const SocketAddr& addr);

  const std::string& Ip() const;
  sockaddr_in CSockaddr() const;
  int Domain() const;
  int Port() const;

  void CSockAddr(sockaddr_in& addr);
  void Ip(const std::string& ip);
  void Domain(int domain);
  void Port(int port);

  friend std::ostream& operator<<(std::ostream& os, const SocketAddr& addr);
  friend bool operator<(const SocketAddr& lhs, const SocketAddr& rhs);

private:
  int family_;
  int port_;
  std::string ip_;
};