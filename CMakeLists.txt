cmake_minimum_required(VERSION 2.8) # Could be even lower. Works with 3.0
project(symbolic_integers)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "-Wall -Werror=return-type -Wno-unknown-pragmas -Wno-sign-compare")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif ()

include_directories(${PROJECT_SOURCE_DIR}/include)
set(SYMBOLIC_INTEGERS_SOURCES
        ${PROJECT_SOURCE_DIR}/src/base.cpp
        ${PROJECT_SOURCE_DIR}/src/monomial_ops.cpp
        ${PROJECT_SOURCE_DIR}/src/polynomial_ops.cpp
        ${PROJECT_SOURCE_DIR}/src/extra_ops.cpp)
# Add gmock only if it has not been added by a parental project
#message(WARNING "${BUILD_GMOCK} *********x*****************************")
#if ((NOT DEFINED BUILD_GMOCK) OR (NOT BUILD_GMOCK))
#    message(WARNING "${BUILD_GMOCK} **************************************")
    add_subdirectory(external/googletest)
#    set(BUILD_GMOCK OFF)
#    message(WARNING "${BUILD_GMOCK} *x*************************************")
#endif()

# Build tests
add_subdirectory(tests)
add_executable(example examples/example.cpp )

# Static registry example
add_executable(example_static_registry examples/example.cpp ${SYMBOLIC_INTEGERS_SOURCES})

# Dynamic registry example
add_executable(example_dynamic_registry examples/example.cpp ${SYMBOLIC_INTEGERS_SOURCES})
target_compile_definitions(example_dynamic_registry PRIVATE METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY)

## --- Google test stuff
#set(GOOGLETEST_ROOT ${PROJECT_SOURCE_DIR}/external/googletest/googletest CACHE STRING "Google Test source root")
#set(GOOGLEMOCK_ROOT ${PROJECT_SOURCE_DIR}/external/googletest/googlemock CACHE STRING "Google Mock source root")
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
