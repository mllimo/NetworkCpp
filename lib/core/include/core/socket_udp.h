#pragma once 

#include <core/socket.h>

class SocketUdp : public Socket { 
  public:
    SocketUdp();
    size_t Send(const Buffer<>& buffer, const SocketAddr& addr);
    size_t Receive(Buffer<>& buffer, SocketAddr& addr);

    Type GetType() const override;

    SocketUdp(const SocketUdp&) = delete;
    SocketUdp& operator=(const SocketUdp&) = delete;
};
