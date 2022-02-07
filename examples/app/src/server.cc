#include "server.h"

Server::Server(const SocketAddr& addr) : socket_(AF_INET, SOCK_DGRAM, 0) {
  socket_.Bind(addr);
}

Server::~Server() {}

void Server::Receive() {
  Buffer<> buffer;
  Buffer<> buffer_propagate;
  SocketAddr addr;
  size_t n = socket_.Receive(buffer, addr);
  if (n == 0) return;
  buffer_propagate = buffer.Data();
  clients_.insert(addr);
  Propagate(buffer_propagate);
}

void Server::Propagate(const Buffer<>& buffer) {
  for (auto& client : clients_) {
    socket_.Send(buffer, client);
  }
}