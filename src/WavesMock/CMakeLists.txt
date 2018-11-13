cmake_minimum_required (VERSION 3.1)
project (Cardiorama-WavesMock-Testbench)

set (CMAKE_CXX_FLAGS "-g -std=c++11")
add_executable(wavesmock-bench testbench.cpp WavesModuleMock.cpp ../../src/ModuleBase.cpp)
include_directories(../../include)