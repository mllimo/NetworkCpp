#pragma once

#include <set>

#include <core/tcp_listener.h>

class Server {
public:
  Server(const SocketAddr& addr);
  ~Server();

  void Receive();

private:
  TcpListener listener_;
  std::set<SocketTcp> clients_;

  void Propagate(const Buffer<>& buffer);
};