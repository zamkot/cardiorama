cmake_minimum_required (VERSION 3.1)

project (cardiorama)
set (CMAKE_CXX_FLAGS "-g -std=c++11")

include_directories(include third_party/wfdb-10.6.0)
add_subdirectory(third_party/wfdb-10.6.0)
add_executable(cardiorama src/main.cpp src/ModuleBase.cpp )
target_link_libraries(cardiorama wfdb)