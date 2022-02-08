#pragma once 

#include <exception>

#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#include <core/socket_addr.h>
#include <core/buffer.h>


enum Type {
  TCP, UDP
};
  

class Socket {
public:

  Socket(int domain, int type, int protocol);
  virtual ~Socket();

  /**
   * @brief Set the Timeout object for the socket if the socket is in blocking mode.
   * @param microseconds
   */
  void SetTimeout(int microseconds);

  /**
   * @brief Bind the socket to the given address.
   * @param addr
   */
  void Bind(const SocketAddr& addr);

  /**
   * @brief Set the socket blocking mode.
   * @param blocking
   */
  void SetBlocking(bool blocking);

  /**
   * @brief Return the socket blocking mode.
   * @return true if the socket is blocking
   * @return false
   */
  bool IsBlocking() const;

  /**
   * @brief Close the socket.
   */
  void Close();

  /**
   * @brief Open the socket
   */
  void Open();

  /**
   * @brief Return the type of the socket.
   * @return Type
   */
  virtual Type GetType() const = 0;

  Socket(const Socket&) = delete;
  Socket& operator=(const Socket&) = delete;

protected:
  int fd_;
  SocketAddr addr_;
};