cmake_minimum_required(VERSION 2.8)

# Project name and versions
project(SymbolicIntegersSRNT)
set(SYMBOLIC_INTEGERS_MAJOR_VERSION 1)
set(SYMBOLIC_INTEGERS_VERSION 0)
set(SYMBOLIC_INTEGERS_VERSION 0)
set(SYMBOLIC_INTEGERS_VERSION
        ${SYMBOLIC_INTEGERS_MAJOR_VERSION}.${SYMBOLIC_INTEGERS_MINOR_VERSION}.${SYMBOLIC_INTEGERS_PATCH_VERSION})

# Build flags
if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
    # Standalone build
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
    if(NOT DEFINED BUILD_EXAMPLES)
        set(BUILD_EXAMPLES 1)
    endif()
    if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
        set(CMAKE_CXX_FLAGS "-Wall -Werror=return-type -Wno-unknown-pragmas -Wno-sign-compare")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Wwrite-strings -Wno-unused")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
        set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    endif()
else()
    # Build under another project umbrealla
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/symints")
endif()

# Include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SYMBOLIC_INTEGERS_SOURCES
        ${PROJECT_SOURCE_DIR}/src/base_monomial.cpp
        ${PROJECT_SOURCE_DIR}/src/base_polynomial.cpp
        ${PROJECT_SOURCE_DIR}/src/base_registry.cpp
        ${PROJECT_SOURCE_DIR}/src/monomial_ops.cpp
        ${PROJECT_SOURCE_DIR}/src/polynomial_ops.cpp
        ${PROJECT_SOURCE_DIR}/src/extra_ops.cpp)

# Append them to ALL_SOURCES
list(APPEND ALL_SOURCES ${SYMBOLIC_INTEGERS_SOURCES})

if( NOT CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
    # Build under another project umbrealla
    set (ALL_SOURCES ${ALL_SOURCES} PARENT_SCOPE)
endif()

# Build libs (static by default)
if(SYMINT_SHARED)
    # Create shared libs
    add_library(symints_srnt SHARED ${SYMBOLIC_INTEGERS_SOURCES})
else()
    # Create static library
    add_library(symints_srnt STATIC ${SYMBOLIC_INTEGERS_SOURCES})
endif()

# Build tests
add_subdirectory(tests)

# Build examples
if(BUILD_EXAMPLES)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples")
    add_executable(symints_srnt_example examples/example.cpp)
    target_link_libraries(symints_srnt_example symints_srnt)
endif()
