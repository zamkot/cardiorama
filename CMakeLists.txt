cmake_minimum_required (VERSION 3.1)
project (Cardiorama)

set (CMAKE_CXX_FLAGS "-g -std=c++11")
add_executable(cardiorama src/main.cpp src/ModuleBase.cpp)
include_directories(include)