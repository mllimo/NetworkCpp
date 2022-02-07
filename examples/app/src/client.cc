#include "client.h"

Client::Client(const SocketAddr& addr_client, const SocketAddr& addr_host) : socket_(AF_INET, SOCK_DGRAM, 0), host_(addr_host) {
  socket_.Bind(addr_client);
}

void Client::Send(const Buffer<>& buffer) {
  socket_.Send(buffer, host_);
}

Buffer<> Client::Receive() {
  Buffer<> buffer;
  socket_.Receive(buffer);
  return buffer;
}