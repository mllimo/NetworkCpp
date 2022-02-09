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

void Client() {
  SocketAddr host = { "127.0.0.12", 3030, AF_INET };
  Client client({ "127.0.0.11", 0, AF_INET }, host);
  Buffer<> buffer;
  std::string msg;

  std::thread receive_thread([&]() {
    while (!end) {
      Buffer<> response;
      response = client.Receive();
      if (response != "") {
        std::cout << "Client receiving: " << "|" << response.Data() << "|" << std::endl;
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

void Server() {
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
      Client();
    }
    else {
      Server();
    }
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "errno: " << errno << std::endl;
  }

  return 0;
}