#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <cstring>
#include <array>

template <size_t SIZE = 256>
class Buffer {
public:
  Buffer();
  Buffer(const std::string& data);

  ~Buffer();

  void Append(const char* data, size_t len);
  void Append(const std::string& data);

  const char* Data() const;
  size_t Size() const;

  Buffer& operator=(const Buffer& rhs);
  Buffer& operator=(const std::string& rhs);

  template <size_t N>
  friend bool operator==(const Buffer<N>& lhs, const Buffer<N>& rhs);

  template <size_t N>
  friend bool operator==(const Buffer<N>& lhs, const std::string& rhs);

  template <size_t N>
  friend bool operator!=(const Buffer<N>& lhs, const Buffer<N>& rhs);

  template <size_t N>
  friend bool operator!=(const Buffer<N>& lhs, const std::string& rhs);

  template<size_t N>
  friend std::ostream& operator<<(std::ostream& os, const Buffer<N>& buffer);
  template<size_t N>
  friend std::istream& operator>>(std::istream& is, Buffer<N>& buffer);

private:
  std::array<char, SIZE> data_;
  size_t last_index_;
};

template <size_t SIZE>
Buffer<SIZE>::Buffer() {
  last_index_ = 0;
  data_.fill('\0');
}

template <size_t SIZE>
Buffer<SIZE>::Buffer(const std::string& data) {
  last_index_ = 0;
  data_.fill('\0');
  Append(data);
}

template <size_t SIZE>
Buffer<SIZE>::~Buffer() {}

template <size_t SIZE>
void Buffer<SIZE>::Append(const char* data, size_t len) {
  if (last_index_ + len > SIZE) {
    throw std::runtime_error("Buffer overflow");
  }
  std::copy(data, data + len, data_.begin() + last_index_);
  last_index_ += len;
}

template <size_t SIZE>
void Buffer<SIZE>::Append(const std::string& data) {
  Append(data.c_str(), data.size());
}

template <size_t SIZE>
const char* Buffer<SIZE>::Data() const {
  return data_.data();
}

template <size_t SIZE>
size_t Buffer<SIZE>::Size() const {
  return data_.size();
}

template <size_t SIZE>
Buffer<SIZE>& Buffer<SIZE>::operator=(const Buffer<SIZE>& rhs) {
  data_ = rhs.data_;
  last_index_ = rhs.last_index_;
  return *this;
}

template <size_t SIZE>
Buffer<SIZE>& Buffer<SIZE>::operator=(const std::string& rhs) {
  strcpy(data_.data(), rhs.c_str());
  last_index_ = rhs.size();
  return *this;
}

template <size_t SIZE>
std::ostream& operator<<(std::ostream& os, const Buffer<SIZE>& buffer) {
  os << "Data: " << buffer.Data() << " Size: " << buffer.Size();
  return os;
}

template <size_t SIZE>
std::istream& operator>>(std::istream& is, Buffer<SIZE>& buffer) {
  std::string data;
  is >> data;
  buffer = data;
  return is;
}

template <size_t N>
bool operator==(const Buffer<N>& lhs, const Buffer<N>& rhs) {
  return strcpy(lhs.data_.data(), rhs.data_.data()) == 0;
}

template <size_t N>
bool operator!=(const Buffer<N>& lhs, const Buffer<N>& rhs) {
  return !(lhs == rhs);
}

template <size_t N>
bool operator==(const Buffer<N>& lhs, const std::string& rhs) {
  return strcmp(lhs.data_.data(), rhs.c_str()) == 0;
}

template <size_t N>
bool operator!=(const Buffer<N>& lhs, const std::string& rhs) {
  return !(lhs == rhs);
}