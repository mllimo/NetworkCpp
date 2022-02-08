#pragma once 

#include <core/socket.h>

class SocketTcp : public Socket {
public:
  SocketTcp();
  SocketTcp(SocketTcp&& socket);

  size_t Send(const Buffer<>& buffer) const;
  size_t Receive(Buffer<>& buffer) const;

  Type GetType() const override;

  void Connect(const SocketAddr& addr);
  void Disconect();

  SocketTcp(const SocketTcp&) = delete;
  SocketTcp& operator=(const SocketTcp&) = delete;

  friend bool operator<(const SocketTcp& lhs, const SocketTcp& rhs);
};