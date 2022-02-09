#pragma once

#include <string>

#include <core/tcp_listener.h>

class Server {
public:
  Server(const SocketAddr& addr);
  ~Server();

  void Receive();

private:
  TcpListener listener_;
};