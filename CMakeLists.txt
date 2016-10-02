cmake_minimum_required(VERSION 2.8) # Could be even lower. Works with 3.0
project(symbolic_integers)

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
    # Standalone build
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
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
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/symints")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
set(SYMBOLIC_INTEGERS_SOURCES
        ${PROJECT_SOURCE_DIR}/src/base.cpp
        ${PROJECT_SOURCE_DIR}/src/monomial_ops.cpp
        ${PROJECT_SOURCE_DIR}/src/polynomial_ops.cpp
        ${PROJECT_SOURCE_DIR}/src/extra_ops.cpp)

# Build libs (static by default)
if(SYMINT_SHARED)
    # Create shared libs
    add_library(symints_s SHARED ${SYMBOLIC_INTEGERS_SOURCES})
    add_library(symints_d SHARED ${SYMBOLIC_INTEGERS_SOURCES})
    target_compile_definitions(symints_d PUBLIC METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY)
else()
    # Create static library
    add_library(symints_s STATIC ${SYMBOLIC_INTEGERS_SOURCES})
    add_library(symints_d STATIC ${SYMBOLIC_INTEGERS_SOURCES})
    target_compile_definitions(symints_d PUBLIC METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY)
endif()

# Build tests
add_subdirectory(tests)

# Build examples
if(BUILD_EXAMPLES)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples")
    # Static registry example
    add_executable(example_static_registry examples/example.cpp)
    target_link_libraries(example_static_registry symints_s)
    # Dynamic registry example
    add_executable(example_dynamic_registry examples/example.cpp)
    target_link_libraries(example_dynamic_registry symints_d)
endif()
