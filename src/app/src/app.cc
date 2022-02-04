#include <string>

#include <signal.h>

#include <core/socket.h>

#include "client.h"
#include "server.h"

bool end = false;

void SignalHandler(int signum) {
  if (signum == SIGINT) {
    std::cerr << "Ctr + C" << std::endl;
    end = true;
  }
}

void Cliente() {
  Client client({"127.0.0.1", 8080, AF_INET}, {"127.0.0.0", 3030, AF_INET});
  client.Connect();
  Buffer<> buffer;
  std::string msg;
  while (!end) {
    std::getline(std::cin, msg);
    buffer = msg;
    client.Send(buffer);
    buffer = client.Receive();
    std::cout << buffer.Data() << std::endl;
  }
}

void Servidor() {
  Server server({"127.0.0.0", 3030, AF_INET});
  while (!end) {
    server.Receive();
  }
}

int main() {
  signal(SIGINT, SignalHandler);
  int opcion = 0;
  std::cout << "1. Cliente" << std::endl;
  std::cout << "2. Servidor" << std::endl;
  std::cout << "Opcion: ";
  std::cin >> opcion;

  if (opcion == 1) {
    Cliente();
  }
  else {
    Servidor();
  }
  return 0;
}