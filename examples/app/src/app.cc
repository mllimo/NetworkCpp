#include <string>
#include <iostream>
#include <thread>

#include <signal.h>
#include <errno.h>

#include <core/socket.h>

#include "client.h"
#include "server.h"

bool end = false;

void SignalHandler(int signum) {
  if (signum == SIGINT) {
    end = true;
    throw std::runtime_error("SIGINT");
  }
}

void Cliente() {
  SocketAddr host = { "127.0.0.12", 3030, AF_INET };
  Client client({ "127.0.0.11", 8080, AF_INET }, host);
  Buffer<> buffer;
  std::string msg;

  std::thread receive_thread([&]() {
    while (!end) {
      Buffer<> response;
      response = client.Receive();
      if (response != "") {
        std::cout << "Cliente recibe: " << "|" << response.Data() << "|" << std::endl;
      }
    }
  });

  while (!end) {
    std::getline(std::cin, msg);
    buffer = msg;
    client.Send(buffer);
  }

  receive_thread.join();
}

void Servidor() {
  Server server({ "127.0.0.12", 3030, AF_INET });
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

  try {
    if (opcion == 1) {
      Cliente();
    }
    else {
      Servidor();
    }
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "errno: " << errno << std::endl;
  }

  return 0;
}