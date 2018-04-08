///
/// \file
/// \brief Unit test file for print_ip function.
///

#define BOOST_TEST_MODULE PrintIpTest
#include <boost/test/unit_test.hpp>

#include "print_ip.h"
#include <sstream>

/// \brief Function for interception from stdout to string.
/// \param f function where intercept output to stdout
/// \return string with intercepted data
static std::string
outputSpy(const std::function<void()>& f)
{
  std::ostringstream oss;
  std::streambuf* cout_streambuf = std::cout.rdbuf();

  std::cout.rdbuf(oss.rdbuf());
  f();
  std::cout.rdbuf(cout_streambuf);

  return oss.str();
}

#define TEST_STDOUT(f, r) BOOST_CHECK_EQUAL(outputSpy([]() { f; }), r)

BOOST_AUTO_TEST_CASE(PrintBool)
{
  TEST_STDOUT(print_ip(true), "1\n");
  TEST_STDOUT(print_ip(false), "0\n");
}

BOOST_AUTO_TEST_CASE(PrintChar)
{
  TEST_STDOUT(print_ip(static_cast<char>(-1)), "255\n");
  TEST_STDOUT(print_ip(static_cast<char>(0)), "0\n");
  TEST_STDOUT(print_ip(static_cast<char>(1)), "1\n");
}

BOOST_AUTO_TEST_CASE(PrintShort)
{
  TEST_STDOUT(print_ip(static_cast<short>(-1)), "255.255\n");
  TEST_STDOUT(print_ip(static_cast<short>(0)), "0.0\n");
  TEST_STDOUT(print_ip(static_cast<short>(1)), "0.1\n");
  TEST_STDOUT(print_ip(static_cast<short>(256)), "1.0\n");
  TEST_STDOUT(print_ip(static_cast<short>(257)), "1.1\n");
}

BOOST_AUTO_TEST_CASE(PrintInt)
{
  TEST_STDOUT(print_ip(0x7F000001), "127.0.0.1\n");
  TEST_STDOUT(print_ip(0x00000000), "0.0.0.0\n");
  TEST_STDOUT(print_ip(0xFFFFFFFF), "255.255.255.255\n");
}

BOOST_AUTO_TEST_CASE(PrintLong)
{
  TEST_STDOUT(print_ip(0x7B2D435965708329L), "123.45.67.89.101.112.131.41\n");
  TEST_STDOUT(print_ip(0UL), "0.0.0.0.0.0.0.0\n");
  TEST_STDOUT(print_ip(0xFFFFFFFFFFFFFFFFL), "255.255.255.255.255.255.255.255\n");
}

BOOST_AUTO_TEST_CASE(PrintString)
{
  TEST_STDOUT(print_ip(std::string{ "192.168.10.52" }), "192.168.10.52\n");
  TEST_STDOUT(print_ip(std::string{ "print string as is" }), "print string as is\n");
}

BOOST_AUTO_TEST_CASE(PrintVector)
{
  TEST_STDOUT(print_ip(std::vector<char>{}), "");
  TEST_STDOUT(print_ip(std::vector<unsigned>{ 0x7F000001, 0x4D498ED3, 0xFFFFFFFF }),
              "127.0.0.1\n"
              "77.73.142.211\n"
              "255.255.255.255\n");
}

BOOST_AUTO_TEST_CASE(PrintList)
{
  TEST_STDOUT(print_ip(std::list<bool>{}), "");
  TEST_STDOUT(print_ip(std::list<char>{ -10, 42, 127 }), "246\n42\n127\n");
}

BOOST_AUTO_TEST_CASE(PrintNestContainer)
{
  TEST_STDOUT(print_ip(std::vector<std::vector<std::string>>{ { "192.168.1.1" } }), "192.168.1.1\n");
  TEST_STDOUT(print_ip(std::list<std::vector<unsigned>>{ { 0x7F000001 }, { 0x4D498ED3, 0xFFFFFFFF } }),
              "127.0.0.1\n"
              "77.73.142.211\n"
              "255.255.255.255\n");
  TEST_STDOUT(print_ip(std::vector<std::list<bool>>{ { true }, { false }, { true } }), "1\n0\n1\n");
}

BOOST_AUTO_TEST_CASE(PrintTuple)
{
  TEST_STDOUT(print_ip(std::tuple<unsigned, unsigned>(0x7F000001, 0xFFFFFFFF)),
              "127.0.0.1\n"
              "255.255.255.255\n");
}
