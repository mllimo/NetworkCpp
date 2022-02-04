#pragma once

#include <core/socket.h>
#include <core/socket_addr.h>

#include <set>

class Server {
public:
  Server(const SocketAddr& addr);
  ~Server();

  void Receive();

private:
  Socket socket_;
  std::set<SocketAddr> clients_;

  void Propagate(const Buffer<>& buffer);
};