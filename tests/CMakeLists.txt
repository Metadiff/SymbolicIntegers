cmake_minimum_required(VERSION 2.8) # Could be even lower. Works with 3.0

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests")

# Add GTest and GMock
add_subdirectory(external/googletest)

set(test_sources run_all.cpp monomial_test.cpp polynomial_test.cpp variable_deduction.cpp)

# Static registry tests
add_executable(static_registry_tests ${test_sources})
add_dependencies(static_registry_tests gtest gmock)
target_link_libraries(static_registry_tests symints_s gtest gmock pthread)

# Dynamic registry tests
add_executable(dynamic_registry_tests ${test_sources})
add_dependencies(dynamic_registry_tests gtest gmock)
target_link_libraries(dynamic_registry_tests symints_d gtest gmock pthread)