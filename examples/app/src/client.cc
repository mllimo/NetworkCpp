#include "client.h"

Client::Client(const SocketAddr& addr_client, const SocketAddr& addr_host) : socket_(AF_INET, SOCK_DGRAM, 0), host_(addr_host) {
  socket_.Bind(addr_client);
}
  
void Client::Connect() {
  socket_.Connect(host_);
} 

void Client::Send(const Buffer<>& buffer) {
  socket_.Send(buffer);
}

Buffer<> Client::Receive() {
  Buffer<> buffer;
  socket_.Receive(buffer);
  return buffer;
}