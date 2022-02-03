#pragma once 

#include <exception>

#include <sys/socket.h>
#include <unistd.h>

#include <core/socket_addr.h>
#include <core/buffer.h>


class Socket {
public:
  Socket(int domain, int type, int protocol);
  ~Socket();

  void Bind(const SocketAddr& addr);

  size_t Send(const Buffer<>& buffer, const SocketAddr& addr);
  size_t Receive(Buffer<>& buffer, SocketAddr& addr);

private:
  int fd_;
  SocketAddr addr_;
};