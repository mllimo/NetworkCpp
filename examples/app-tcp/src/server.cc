#include "server.h"

Server::Server(const SocketAddr& addr) {
  listener_.Open();
  listener_.Bind(addr);
  std::cout << "Server escuchando en " << addr << std::endl;
  listener_.Listen();
}

Server::~Server() {}

void Server::Receive() {
  Buffer<> buffer;
  SocketTcp client;
  listener_.Accept(client);
  while (true) {
    int bytes = client.Receive(buffer);
    if (bytes == 0) break;
    std::cout << "Server receiving: " << "|" << buffer.Data() << "|" << std::endl;
    client.Send(buffer);
  }
  client.Close();
}