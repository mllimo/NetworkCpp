#include <core/socket.h>
#include <signal.h>

void SignalHandler(int signum) {
  if (signum == SIGINT) {
    std::cerr << "Ctr + C" << std::endl;
  }
}

void Cliente() {
  Buffer<> buffer;
  Socket cliente(AF_INET, SOCK_DGRAM, 0);
  cliente.Bind({ "127.0.0.10", 3031, AF_INET });
  while (true) {
    std::cin >> buffer;
    if (buffer == "exit") break;
    cliente.Send(buffer, { "127.0.0.1", 3030, AF_INET });
  }
}

void Servidor() {
  Buffer<> buffer;
  Socket servidor(AF_INET, SOCK_DGRAM, 0);
  SocketAddr addr;
  servidor.Bind({ "127.0.0.1", 3030, AF_INET });
  while (true) {
    try {
      servidor.Receive(buffer, addr);
      std::cout << buffer << std::endl;
    }
    catch (std::exception& e) {
    }
  }
}

int main() {
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