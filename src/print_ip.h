///
/// \file
/// \brief Header file with IP address print functions.
///
/// This file contain some function for printing IP addresses from many types.
///

#ifndef PRINT_IP_H
#define PRINT_IP_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <type_traits>
#include <vector>

/// \brief Print IP address.
/// \details Print IP address in stdout.
/// \param value IP address for by byte print.
/// \callergraph
template <typename T>
void print_ip(const T &value,
              typename std::enable_if<std::is_integral<T>::value, T>::type * = nullptr) {
  auto pbegin = reinterpret_cast<const unsigned char *>(&value);
  auto pend = reinterpret_cast<const unsigned char *>(&value) + sizeof(value);

  std::reverse_copy(pbegin + 1, pend, std::ostream_iterator<int>(std::cout, "."));
  std::cout << static_cast<int>(*pbegin) << std::endl;
}

/// \brief Print IP address.
/// \details Print IP address in stdout from std::string.
/// \param str String as IP address for print.
template <typename T>
void print_ip(const T &value,
              typename std::enable_if<std::is_same<T, std::string>::value, T>::type * = nullptr) {
  std::cout << value << std::endl;
}

/// \brief Print IP address.
/// \details Print IP address in stdout from std::vector or std::list container.
/// \param vec Container std::vector or std::list with values for print.
template <typename T>
void print_ip(const T &value,
              typename std::enable_if<std::is_same<T, std::vector<typename T::value_type>>::value ||
                                          std::is_same<T, std::list<typename T::value_type>>::value,
                                      T>::type * = nullptr) {
  for (const auto ip : value)
    print_ip(ip);
}

#endif // PRINT_IP_H