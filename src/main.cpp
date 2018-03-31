///
/// \file
/// \brief Main file. Entry point program.
///
/// This file contain main function.
///

#include "print_ip.h"

///
/// \mainpage IP address printer
///
/// \section intro_sec Introduction
///
/// This is program is sample for use Doxygen documentation generator.
///
/// \see print_ip()
///

/// \brief Main function.
/// \details Here start program from this function.
/// \return Error code
int main(int, char* []) {
  print_ip(static_cast<char>(-1));
  print_ip(static_cast<short>(0));
  print_ip(2130706433);
  print_ip(8875824491850138409L);
  print_ip(std::string{"192.168.10.52"});
  print_ip(std::vector<int>{2130706433, 2130706532, 2130706433});
  print_ip(std::list<char>{-10, 42, 127});

  return 0;
}