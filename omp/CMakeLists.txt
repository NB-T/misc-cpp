cmake_minimum_required(VERSION 3.14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(nbtlog)

project(OMP)
find_package(OpenMP REQUIRED)
add_executable(omp omp.cpp)
target_link_libraries(omp PRIVATE nbtlog OpenMP::OpenMP_CXX)
