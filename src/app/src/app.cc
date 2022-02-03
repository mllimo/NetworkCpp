#include <core/socket.h>

void Cliente() {
  Buffer<> buffer;
  buffer = "Hola mundo";
  Socket cliente(AF_INET, SOCK_DGRAM, 0);
  cliente.Bind({ "127.0.0.10", 3031, AF_INET });
  cliente.Send(buffer, { "127.0.0.1", 3030, AF_INET });
}

void Servidor() {
  Buffer<> buffer;
  Socket servidor(AF_INET, SOCK_DGRAM, 0);
  SocketAddr addr;
  servidor.Bind({ "127.0.0.1", 3030, AF_INET });
  servidor.Receive(buffer, addr);
  std::cout << buffer << std::endl;
}

int main() {
  int opcion = 0;
  std::cout << "1. Cliente" << std::endl;
  std::cout << "2. Servidor" << std::endl;
  std::cout << "Opcion: " << std::endl;
  std::cin >> opcion;
  if (opcion == 1) {
    Cliente();
  } else {
    Servidor();
  }
  return 0;
}