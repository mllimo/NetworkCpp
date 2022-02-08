#include "client.h"

Client::Client(const SocketAddr& addr_client, const SocketAddr& addr_host) : socket_(), host_(addr_host) {
  socket_.Open();
  socket_.Bind(addr_client);
  socket_.Connect(host_);
}

void Client::Send(const Buffer<>& buffer) {
  socket_.Send(buffer);
}

Buffer<> Client::Receive() {
  Buffer<> buffer;
  SocketAddr addr;
  socket_.Receive(buffer);
  return buffer;
}