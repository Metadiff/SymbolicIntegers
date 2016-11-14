cmake_minimum_required(VERSION 2.8) # Could be even lower. Works with 3.0

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests")

# Add GTest and GMock
add_subdirectory(external/googletest)

set(test_sources run_all.cpp monomial_test.cpp polynomial_test.cpp variable_deduction.cpp)

# Tests
add_executable(symints_srnt_tests ${test_sources})
add_dependencies(symints_srnt_tests gtest gmock)
target_link_libraries(symints_srnt_tests symints_srnt gtest gmock pthread)
