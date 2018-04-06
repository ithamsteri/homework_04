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

using std::enable_if_t;

// For C++14 helper functions
template <class T, class U> constexpr bool is_same_v = std::is_same<T, U>::value;
template <class T> constexpr bool is_integral_v = std::is_integral<T>::value;

/// \brief Print IP address.
/// \details Print IP address in stdout.
/// \param value IP address for by byte print.
/// \callergraph
template <typename T> void print_ip(const T &value, enable_if_t<is_integral_v<T>, T> * = nullptr) {
  auto pbegin = reinterpret_cast<const unsigned char *>(&value);
  auto pend = reinterpret_cast<const unsigned char *>(&value) + sizeof(value);

  std::reverse_copy(pbegin + 1, pend, std::ostream_iterator<int>(std::cout, "."));
  std::cout << static_cast<int>(*pbegin) << std::endl;
}

/// \brief Print IP address.
/// \details Print IP address in stdout from std::string.
/// \param str String as IP address for print.
template <typename T>
void print_ip(const T &value, enable_if_t<is_same_v<std::string, T>, T> * = nullptr) {
  std::cout << value << std::endl;
}

/// \brief Print IP address.
/// \details Print IP address in stdout from std::vector or std::list container.
/// \param vec Container std::vector or std::list with values for print.
template <typename T>
void print_ip(const T &value, enable_if_t<is_same_v<std::vector<typename T::value_type>, T> ||
                                              is_same_v<std::list<typename T::value_type>, T>,
                                          T> * = nullptr) {
  for (const auto &ip : value)
    print_ip(ip);
}

#endif // PRINT_IP_H