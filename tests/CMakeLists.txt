cmake_minimum_required(VERSION 2.8) # Could be even lower. Works with 3.0

set(test_sources run_all.cpp monomial_test.cpp polynomial_test.cpp)
add_executable(run_tests ${test_sources})
add_dependencies(run_tests gtest gmock)
target_link_libraries(run_tests gtest gmock pthread)