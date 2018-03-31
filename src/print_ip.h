///
/// \file
/// \brief Header file with IP address print functions.
///
/// This file contain some function for printing IP addresses from many types.
///

#ifndef PRINT_IP_H
#define PRINT_IP_H

#include <array>
#include <iostream>
#include <list>
#include <vector>

/// \brief Print IP address.
/// \details Print IP address in stdout.
/// \param value IP address for by byte print.
/// \callergraph
template <typename T> void print_ip(const T &value) {
  std::array<unsigned char, sizeof value> bytes;
  std::copy(
      static_cast<const unsigned char *>(static_cast<const void *>(&value)),
      static_cast<const unsigned char *>(static_cast<const void *>(&value)) +
          sizeof value,
      bytes.data());

  for (auto iter = bytes.rbegin(); iter != bytes.rend(); ++iter) {
    if (iter != bytes.rbegin())
      std::cout << '.';
    std::cout << static_cast<int>(*iter);
  }
  std::cout << std::endl;
}

/// \brief Print IP address.
/// \details Print IP address in stdout from std::string.
/// \param str String as IP address for print.
template <>
void print_ip<std::string>(std::string const& str) {
  std::cout << str << std::endl;
}

/// \brief Print IP address.
/// \details Print IP address in stdout from std::vector container.
/// \param vec Container std::vector with values for print.
template <typename T>
void print_ip(const std::vector<T> &vec) {
  for (const auto ip : vec)
    print_ip(ip);
}

/// \brief Print IP address.
/// \details Print IP address in stdout from std::list container.
/// \param list Container std::list with values for print.
template <typename T>
void print_ip(const std::list<T> &list) {
  for (const auto ip : list)
    print_ip(ip);
}

#endif // PRINT_IP_H