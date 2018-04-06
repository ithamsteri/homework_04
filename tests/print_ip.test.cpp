///
/// \file
/// \brief Unit test file for print_ip function.
///

#define BOOST_TEST_MODULE PrintIpTest
#include <boost/test/unit_test.hpp>

#include "print_ip.h"
#include <sstream>

/// \brief Test Fixture
/// \details Test Fixture for interception console output from stdout.
struct SpyOutput
{
  /// \brief Constuctor
  SpyOutput()
  {
    _cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(_oss.rdbuf());
  }

  /// \brief Destructor
  ~SpyOutput() { std::cout.rdbuf(_cout_streambuf); }

  /// \brief Get output string from interception std::cout buffer.
  /// \return String with output data
  std::string getOutput() { return _oss.str(); }

private:
  std::ostringstream _oss;
  std::streambuf* _cout_streambuf;
};

/// \test Check print char type
BOOST_FIXTURE_TEST_CASE(PrintChar, SpyOutput)
{
  print_ip(static_cast<char>(-1));
  BOOST_CHECK_EQUAL(getOutput(), "255\n");
}

/// \test Check print short type
BOOST_FIXTURE_TEST_CASE(PrintShort, SpyOutput)
{
  print_ip(static_cast<short>(0));
  BOOST_CHECK_EQUAL(getOutput(), "0.0\n");
}

/// \test Check print int type
BOOST_FIXTURE_TEST_CASE(PrintInt, SpyOutput)
{
  print_ip(2130706433);
  BOOST_CHECK_EQUAL(getOutput(), "127.0.0.1\n");
}

/// \test Check print long type
BOOST_FIXTURE_TEST_CASE(PrintLong, SpyOutput)
{
  print_ip(8875824491850138409L);
  BOOST_CHECK_EQUAL(getOutput(), "123.45.67.89.101.112.131.41\n");
}

/// \test Check print std::string type
BOOST_FIXTURE_TEST_CASE(PrintString, SpyOutput)
{
  print_ip(std::string{ "192.168.10.52" });
  BOOST_CHECK_EQUAL(getOutput(), "192.168.10.52\n");
}

/// \test Check print values from std::vector container
BOOST_FIXTURE_TEST_CASE(PrintVector, SpyOutput)
{
  print_ip(std::vector<int>{ 2130706433, 2130706532, 2130706434 });
  BOOST_CHECK_EQUAL(getOutput(), "127.0.0.1\n127.0.0.100\n127.0.0.2\n");
}

/// \test Check print values from std::list container
BOOST_FIXTURE_TEST_CASE(PrintList, SpyOutput)
{
  print_ip(std::list<char>{ -10, 42, 127 });
  BOOST_CHECK_EQUAL(getOutput(), "246\n42\n127\n");
}

/// \test Check nested container in container
BOOST_FIXTURE_TEST_CASE(PrintNestContainer, SpyOutput)
{
  print_ip(std::list<std::vector<int>>{ { 2130706433 }, { 2130706532 }, { 2130706434 } });
  print_ip(std::vector<std::list<int>>{ { 2130706433 }, { 2130706532 }, { 2130706434 } });
  print_ip(std::list<std::list<int>>{ { 2130706433 }, { 2130706532 }, { 2130706434 } });
  print_ip(std::vector<std::vector<int>>{ { 2130706433 }, { 2130706532 }, { 2130706434 } });
  BOOST_CHECK_EQUAL(getOutput(),
                    "127.0.0.1\n127.0.0.100\n127.0.0.2\n"
                    "127.0.0.1\n127.0.0.100\n127.0.0.2\n"
                    "127.0.0.1\n127.0.0.100\n127.0.0.2\n"
                    "127.0.0.1\n127.0.0.100\n127.0.0.2\n");
}