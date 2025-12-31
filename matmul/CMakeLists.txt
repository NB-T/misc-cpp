cmake_minimum_required(VERSION 3.20)

project(matmul LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "ccache found, using ${CCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
else()
    message(STATUS "ccache not found, using default compiler")
endif()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../nbtlog ${CMAKE_CURRENT_BINARY_DIR}/nbtlog)

add_executable(matmul matmul.cpp)

target_compile_features(matmul PRIVATE cxx_std_20)

target_link_libraries(matmul PRIVATE logging::nbtlog)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(matmul PRIVATE -Wall -Wextra -Wpedantic)
endif()

