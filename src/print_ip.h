///
/// \file
/// \brief Header file with IP address print functions.
///
/// This file contain some function for printing IP addresses from many types.
///

#ifndef PRINT_IP_H
#define PRINT_IP_H

#include "check_tuple.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <type_traits>
#include <vector>

/// \brief Print IP address.
/// \details Print IP address in stdout.
/// \param value IP address for by byte print.
/// \callergraph
template<typename T>
typename std::enable_if_t<std::is_integral_v<T>, void>
print_ip(const T& value)
{
  auto pLow = reinterpret_cast<const unsigned char*>(&value);
  auto pHigh = reinterpret_cast<const unsigned char*>(&value) + sizeof(value);

  // print value from high byte to low byte
  std::reverse_copy(pLow + 1, pHigh, std::ostream_iterator<int>(std::cout, "."));
  std::cout << static_cast<int>(*pLow) << std::endl;
}

/// \brief Print IP address.
/// \details Print IP address in stdout from std::string.
/// \param str String as IP address for print.
void
print_ip(const std::string& str)
{
  std::cout << str << std::endl;
}

/// \brief Print IP address.
/// \details Print IP address in stdout from std::vector or std::list container.
/// \param vec Container std::vector or std::list with values for print.
template<typename T>
typename std::enable_if_t<std::is_same_v<std::vector<typename T::value_type, typename T::allocator_type>, T> ||
                            std::is_same_v<std::list<typename T::value_type, typename T::allocator_type>, T>,
                          void>
print_ip(const T& value)
{
  for (const auto& ip : value)
    print_ip(ip);
}

template<int index, typename... Ts>
struct print_tuple
{
  void operator()(const std::tuple<Ts...>& t)
  {
    print_tuple<index - 1, Ts...>{}(t);
    print_ip(std::get<index>(t));
  }
};

template<typename... Ts>
struct print_tuple<0, Ts...>
{
  void operator()(const std::tuple<Ts...>& t) { print_ip(std::get<0>(t)); }
};

template<typename... Ts>
void
print(const std::tuple<Ts...>& t)
{
  const auto size = std::tuple_size<std::tuple<Ts...>>::value;
  print_tuple<size - 1, Ts...>{}(t);
}

/// \brief Print IP address.
/// \details Print IP address in stdout from std::tuple if all types is equal.
/// \param tuple Tuple with values for print.
template<typename T, typename... Ts>
typename std::enable_if_t<is_onetype_tuple<T>::value, void>
print_ip(const T& tuple)
{
  print(tuple);
};

#endif // PRINT_IP_H