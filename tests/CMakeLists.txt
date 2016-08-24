cmake_minimum_required(VERSION 2.8) # Could be even lower. Works with 3.0

# --- Google test stuff
set(GOOGLETEST_ROOT googletest/googletest CACHE STRING "Google Test source root")
set(GOOGLEMOCK_ROOT googletest/googlemock CACHE STRING "Google Mock source root")

include_directories(
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
        ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}
        ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}/include
)

set(GOOGLETEST_SOURCES
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
        ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}/src/gmock-all.cc
        ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}/src/gmock_main.cc
        )

foreach (_source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach ()

add_library(googletest ${GOOGLETEST_SOURCES})
add_library(googlemock ${GOOGLETEST_SOURCES})
# --- Google test stuff

set(test_sources monomial_test.cpp)

#add_executable(base_tests tests/base_tests.cpp)
add_executable(monomial_test ${test_sources})
add_dependencies(monomial_test googletest googlemock)
target_link_libraries(monomial_test googletest googlemock pthread)