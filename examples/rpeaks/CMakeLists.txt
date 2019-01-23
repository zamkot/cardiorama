cmake_minimum_required (VERSION 3.5)
project (rpeaks-example)

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

# WFDB
add_subdirectory(../../third_party/wfdb-10.6.0 build-wfdb)
# waveletlib
add_subdirectory(../../third_party/wavelib/src/static build-wavelet)

add_executable(
        rpeaks-example
        ../../src/DataFrame.cpp
        ../../src/ModuleBase.cpp
        ../../src/EcgBaselineModule.cpp
        ../../src/RPeaksModule.cpp
        main.cpp
)

target_link_libraries(rpeaks-example wfdb wavelet2 ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})