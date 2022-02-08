#include <core/socket_tcp.h>

class TcpListener : public SocketTcp {
public:
  TcpListener();

  void Listen();
  void Accept(SocketTcp& socket);

  TcpListener(const TcpListener&) = delete;
  TcpListener& operator=(const TcpListener&) = delete;

protected:
  bool is_listening_;
};