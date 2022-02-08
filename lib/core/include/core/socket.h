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
  Socket(Socket&& socket);
  
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

  /**
   * @brief Create a socket from the given fd and address.
   * @param fd
   * @param addr
   */
  virtual void Create(int fd, const SocketAddr& addr);

  Socket(const Socket&) = delete;
  Socket& operator=(const Socket&) = delete;

  friend bool operator<(const Socket& lhs, const Socket& rhs);

protected:
  SocketAddr addr_;
  bool is_blocking_;
  int blocking_mode_;
  int protocol_;
  int domain_;
  int type_;
  int fd_;
};