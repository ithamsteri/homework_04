if (BUILD_TESTING)
    find_package (Boost COMPONENTS unit_test_framework REQUIRED)

    add_executable(printip_test
        print_ip.test.cpp
        ${SOURCE_PATH}/print_ip.h
    )

    set_target_properties(printip_test PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES "${Boost_INCLUDE_DIRS};${SOURCE_PATH}"
        LINK_LIBRARIES Boost::unit_test_framework
    )

    add_test(PrintIpTest printip_test)
endif()
