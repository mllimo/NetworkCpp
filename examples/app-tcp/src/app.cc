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

void ClientF() {
  SocketAddr host = { "127.0.0.12", 3030, AF_INET };
  Client client({ "127.0.0.11", 0, AF_INET }, host);
  Buffer<> buffer;
  Buffer<> response;
  std::string msg;

  while (!end) {
    std::cin.ignore();
    std::getline(std::cin, msg);

    buffer = msg;

    client.Send(buffer);

    response = client.Receive();
    if (response != "") {
      std::cout << "Client receiving: " << "|" << response.Data() << "|" << std::endl;
    }
  }

}

void ServerF() {
  Server server({ "127.0.0.12", 3030, AF_INET });
  while (!end) {
    server.Receive();
  }
}

int main() {
  signal(SIGINT, SignalHandler);
  int Option = 0;
  std::cout << "1. Client" << std::endl;
  std::cout << "2. Server" << std::endl;
  std::cout << "Option: ";
  std::cin >> Option;

  try {
    if (Option == 1) {
      ClientF();
    }
    else {
      ServerF();
    }
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "errno: " << errno << std::endl;
  }

  return 0;
}