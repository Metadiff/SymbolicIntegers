cmake_minimum_required(VERSION 2.8) # Could be even lower. Works with 3.0

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests")

# Add GTest and GMock
add_subdirectory(external/googletest)
include_directories(external/googletest/googletest/include/)
include_directories(external/googletest/googlemock/include/)

set(test_sources run_all.cpp monomial_test.cpp polynomial_test.cpp variable_deduction.cpp)

# Tests
add_executable(symbolic_integer_tests ${test_sources})
add_dependencies(gtest gmock)
target_link_libraries(symbolic_integer_tests gtest gmock pthread)
