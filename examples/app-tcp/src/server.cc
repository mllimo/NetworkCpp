#include "server.h"

Server::Server(const SocketAddr& addr) {
  listener_.Bind(addr);
  listener_.Listen();
}

Server::~Server() {}

void Server::Receive() {
  SocketTcp client;
  Buffer<> buffer;
  listener_.Accept(client);
  clients_.insert(std::move(client));
  Propagate(buffer);
}

void Server::Propagate(const Buffer<>& buffer) {
  for (auto& client : clients_) {
    client.Send(buffer);
  }
}