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
template<typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
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
typename std::enable_if<std::is_same<std::vector<typename T::value_type>, T>::value ||
                          std::is_same<std::list<typename T::value_type>, T>::value,
                        void>::type
print_ip(const T& value)
{
  for (const auto& ip : value)
    print_ip(ip);
}

#endif // PRINT_IP_H