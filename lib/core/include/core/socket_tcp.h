#pragma once 

#include <core/socket.h>

class SocketTcp : public Socket { 
  public:
    SocketTcp();
    size_t Send(const Buffer<>& buffer);
    size_t Receive(Buffer<>& buffer);

    Type GetType() const override;

    void Connect(const SocketAddr& addr);

    SocketTcp(const SocketTcp&) = delete;
    SocketTcp& operator=(const SocketTcp&) = delete;
};