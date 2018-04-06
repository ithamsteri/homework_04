cmake_minimum_required(VERSION 3.2)

# check environment variable TRAVIS_BUILD_NUMBER
if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION_BUILD 0)
endif()

project(print_ip VERSION 0.0.${VERSION_BUILD})

# configure directories
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")

# make executable file for application
add_executable(print_ip
        ${SOURCE_PATH}/main.cpp
        ${SOURCE_PATH}/print_ip.h
)

set_target_properties(print_ip PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT alex.aspirine@gmail.com)

include(CPack)

enable_testing()

add_subdirectory(tests)

