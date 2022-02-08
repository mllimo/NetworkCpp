#include "client.h"

Client::Client(const SocketAddr& addr_client, const SocketAddr& addr_host) : socket_(), host_(addr_host) {
  socket_.Open();
  socket_.Bind(addr_client);
}

void Client::Send(const Buffer<>& buffer) {
  socket_.Send(buffer, host_);
}

Buffer<> Client::Receive() {
  Buffer<> buffer;
  SocketAddr addr;
  socket_.Receive(buffer, addr);
  return buffer;
}