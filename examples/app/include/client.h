#pragma once

#include <iostream>

#include <core/socket_addr.h>
#include <core/socket_udp.h>

class Client {
public:
  Client(const SocketAddr& addr_client, const SocketAddr& addr_host);
  void Send(const Buffer<>& buffer);
  Buffer<> Receive();

private:
  SocketUdp socket_;
  SocketAddr host_;
};