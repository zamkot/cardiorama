cmake_minimum_required(VERSION 2.8)

project (wfdb)
set(CMAKE_BUILD_TYPE Release)

set(wfdb_SOURCES ${wfdb_SOURCES}
annot.c
calib.c
signal.c
wfdbinit.c
wfdbio.c
)

add_library(wfdb STATIC ${wfdb_SOURCES})
target_link_libraries(wfdb curl)