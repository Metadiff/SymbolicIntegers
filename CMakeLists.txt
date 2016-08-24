cmake_minimum_required(VERSION 2.8) # Could be even lower. Works with 3.0
project(symbolic_integers)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "-Wall -Werror=return-type -Wno-unknown-pragmas -Wno-sign-compare")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif ()

include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(tests)
## --- Google test stuff
#set(GOOGLETEST_ROOT external/googletest/googletest CACHE STRING "Google Test source root")
#set(GOOGLEMOCK_ROOT external/googletest/googlemock CACHE STRING "Google Mock source root")
#
#include_directories(
#        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
#        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
#        ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}
#        ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}/include
#)
#
#set(GOOGLETEST_SOURCES
#        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
#        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
#        ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}/src/gmock-all.cc
#        ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}/src/gmock_main.cc
#        )
#
#foreach (_source ${GOOGLETEST_SOURCES})
#    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
#endforeach ()
#
#add_library(googletest ${GOOGLETEST_SOURCES})
#add_library(googlemock ${GOOGLETEST_SOURCES})
## --- Google test stuff
#
#set(test_sources tests/monomial_test.cpp)
#
##add_executable(base_tests tests/base_tests.cpp)
#add_executable(monomial_test ${test_sources})
#add_dependencies(monomial_test googletest googlemock)
#target_link_libraries(monomial_test googletest googlemock pthread)
#
#enable_testing()
#add_test(monomial_)
