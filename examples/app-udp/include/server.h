#pragma once

#include <set>

#include <core/socket_udp.h>
#include <core/socket_addr.h>

class Server {
public:
  Server(const SocketAddr& addr);
  ~Server();

  void Receive();

private:
  SocketUdp socket_;
  std::set<SocketAddr> clients_;

  void Propagate(const Buffer<>& buffer);
};