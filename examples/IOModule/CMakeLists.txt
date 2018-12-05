cmake_minimum_required (VERSION 3.5)
project (io-examples)

set (CMAKE_CXX_FLAGS "-g -std=c++11")
include_directories(
    ../../include
    ../../third_party/wfdb-10.6.0 # WFDB
    ../../third_party/armadillo-9.200.4/include # Armadillo
)

# Armadillo
find_package(BLAS)
find_package(LAPACK)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DARMA_DONT_USE_WRAPPER")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${BLAS_LINKER_FLAGS} ${LAPACK_LINKER_FLAGS}")

# WFDB
add_subdirectory(../../third_party/wfdb-10.6.0 build)

add_executable(
    io-example
    ioExample.cpp
    ../../src/IOModule.cpp
)

# WFDB & Armadillo
target_link_libraries(io-examples wfdb ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})