cmake_minimum_required (VERSION 3.1)

project (cardiorama)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

include_directories(
    include
    third_party/wfdb-10.6.0 # WFDB
    third_party/armadillo-9.200.4/include # Armadillo
    third_party/wavelib/src/static # Wavelib
)

# Armadillo
find_package(BLAS)
find_package(LAPACK)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DARMA_DONT_USE_WRAPPER")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${BLAS_LINKER_FLAGS} ${LAPACK_LINKER_FLAGS}")

# WFDB
add_subdirectory(third_party/wfdb-10.6.0)
# waveletlib
add_subdirectory(third_party/wavelib/src/static build)

add_definitions(-DDATA_DIR="${PROJECT_SOURCE_DIR}/data")
add_executable(cardiorama src/main.cpp src/ModuleBase.cpp src/IOModule.cpp src/RPeaksModule.cpp src/EcgBaselineModule.cpp)

# WFDB & Armadillo & waveletlib
target_link_libraries(cardiorama wfdb wavelet2 ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})