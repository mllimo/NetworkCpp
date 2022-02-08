#include "server.h"

Server::Server(const SocketAddr& addr) : socket_() {
  socket_.Open();
  socket_.Bind(addr);
  socket_.Listen();
}

Server::~Server() {}

void Server::Receive() {
  Buffer<> buffer;
  Buffer<> buffer_propagate;
  SocketAddr addr;
  size_t n = socket_.Receive(buffer);
  if (n == 0) return;
  buffer_propagate = buffer.Data();
  clients_.insert(addr);
  Propagate(buffer_propagate);
}

void Server::Propagate(const Buffer<>& buffer) {
  for (auto& client : clients_) {
    socket_.Send(buffer);
  }
}