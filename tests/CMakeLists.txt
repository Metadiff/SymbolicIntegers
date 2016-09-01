cmake_minimum_required(VERSION 2.8) # Could be even lower. Works with 3.0

set(test_sources run_all.cpp monomial_test.cpp polynomial_test.cpp variable_deduction.cpp ${SYMBOLIC_INTEGERS_SOURCES})

# Static registry tests
add_executable(static_registry_tests ${test_sources})
add_dependencies(static_registry_tests gtest gmock)
target_link_libraries(static_registry_tests gtest gmock pthread)

# Dynamic registry tests
add_executable(dynamic_registry_tests ${test_sources})
target_compile_definitions(dynamic_registry_tests PRIVATE METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY)
add_dependencies(dynamic_registry_tests gtest gmock)
target_link_libraries(dynamic_registry_tests gtest gmock pthread)