if (BUILD_TESTING)
  find_package (Boost COMPONENTS unit_test_framework REQUIRED)

  add_executable(printip_test
          print_ip.test.cpp
          ${SOURCE_PATH}/print_ip.h
  )

  set_target_properties(printip_test PROPERTIES
          CXX_STANDARD 14
          CXX_STANDARD_REQUIRED ON
          COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
          INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS}
          INCLUDE_DIRECTORIES ${SOURCE_PATH}
          LINK_LIBRARIES ${Boost_LIBRARIES}
  )

  add_test(PrintIpTest printip_test)
endif()
