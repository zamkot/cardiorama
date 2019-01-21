cmake_minimum_required (VERSION 3.5)
project (example-example)

set (CMAKE_CXX_FLAGS "-g -std=c++14")
include_directories(
    ../../include
    ../../third_party/armadillo-9.200.4/include # Armadillo
    ../../third_party/wavelib/src/static
)

# Armadillo
find_package(BLAS)
find_package(LAPACK)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DARMA_DONT_USE_WRAPPER")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${BLAS_LINKER_FLAGS} ${LAPACK_LINKER_FLAGS}")

# waveletlib
add_subdirectory(../../third_party/wavelib/src/static build)

add_executable(
    example-example 
    wavelib-example.cpp
)

target_link_libraries(example-example wavelet2)