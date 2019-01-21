cmake_minimum_required(VERSION 2.8)

project (wavelet2)
set(CMAKE_BUILD_TYPE Release)

set(wavelet2_SOURCES ${wavelet2_SOURCES}
wavelet2s.cpp
)

add_library(wavelet2 STATIC ${wavelet2_SOURCES})
target_link_libraries(wavelet2 fftw3)