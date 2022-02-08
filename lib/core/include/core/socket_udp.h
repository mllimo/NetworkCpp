#pragma once 

#include <core/socket.h>

class SocketUdp : public Socket {
public:
  SocketUdp();
  SocketUdp(SocketUdp&& socket);
  
  size_t Send(const Buffer<>& buffer, const SocketAddr& addr) const;
  size_t Receive(Buffer<>& buffer, SocketAddr& addr) const;

  Type GetType() const override;

  SocketUdp(const SocketUdp&) = delete;
  SocketUdp& operator=(const SocketUdp&) = delete;

  friend bool operator<(const SocketUdp& lhs, const SocketUdp& rhs);
};
