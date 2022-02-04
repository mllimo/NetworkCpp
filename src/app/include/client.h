#pragma once

#include <core/socket.h>
#include <core/socket_addr.h>

#include <iostream>

class Client {
public:
  Client(const SocketAddr& addr_client, const SocketAddr& addr_host);

  void Connect();
  void Send(const Buffer<>& buffer);
  Buffer<> Receive();

private:
  Socket socket_;
  SocketAddr host_;
};