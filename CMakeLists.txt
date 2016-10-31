cmake_minimum_required(VERSION 2.8)

project(SymbolicIntegers)
set(SYMBOLIC_INTEGERS_MAJOR_VERSION 0)
set(SYMBOLIC_INTEGERS_VERSION 9)
set(SYMBOLIC_INTEGERS_VERSION 1)
set(SYMBOLIC_INTEGERS_VERSION
        ${SYMBOLIC_INTEGERS_MAJOR_VERSION}.${SYMBOLIC_INTEGERS_MINOR_VERSION}.${SYMBOLIC_INTEGERS_PATCH_VERSION})

## Offer the user the choice of overriding the installation directories
#set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
#set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
#set(INSTALL_INCLUDE_DIR include CACHE PATH
#        "Installation directory for header files")
#if(WIN32 AND NOT CYGWIN)
#    set(DEF_INSTALL_CMAKE_DIR CMake)
#else()
#    set(DEF_INSTALL_CMAKE_DIR lib/CMake/FooBar)
#endif()
#set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
#        "Installation directory for CMake files")
#
## Make relative paths absolute (needed later on)
#foreach(p LIB BIN INCLUDE CMAKE)
#    set(var INSTALL_${p}_DIR)
#    if(NOT IS_ABSOLUTE "${${var}}")
#        set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
#    endif()
#endforeach()

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
