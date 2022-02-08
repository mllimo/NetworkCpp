#pragma once

#include <set>

#include <core/socket_tcp.h>
#include <core/socket_addr.h>

class Server {
public:
  Server(const SocketAddr& addr);
  ~Server();

  void Receive();

private:
  SocketTcp socket_;
  std::set<SocketAddr> clients_;

  void Propagate(const Buffer<>& buffer);
};